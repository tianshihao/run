#include "./insight_service.h"

#include <glog/logging.h>

#include <algorithm>
#include <numeric>
#include <sstream>

namespace run::ex::insight_service {
void InsightService::StartTiming(std::string const& category,
                                 std::string const& subcategory,
                                 FrameId frame_id) {
  std::lock_guard<std::mutex> lock(mutex_timing_);

  timing_map_[category][subcategory][frame_id].start = NowMilliseconds();
}

void InsightService::StopTiming(std::string const& category,
                                std::string const& subcategory,
                                FrameId frame_id) {
  std::lock_guard<std::mutex> lock(mutex_timing_);

  auto stop_time{NowMilliseconds()};
  auto start_time{timing_map_[category][subcategory][frame_id].start};
  auto elapsed_time{stop_time - start_time};

  timing_map_[category][subcategory][frame_id].elapsed = elapsed_time;

  AdjustSize(timing_map_[category][subcategory]);
}

void InsightService::StartTiming(std::string const& category,
                                 std::string const& subcategory,
                                 FrameId frame_id, Milliseconds start) {
  std::lock_guard<std::mutex> lock(mutex_timing_);

  timing_map_[category][subcategory][frame_id].start = start;
}

void InsightService::StopTiming(std::string const& category,
                                std::string const& subcategory,
                                FrameId frame_id, Milliseconds stop) {
  std::lock_guard<std::mutex> lock(mutex_timing_);

  auto stop_time{stop};
  auto start_time{timing_map_[category][subcategory][frame_id].start};
  auto elapsed_time{stop_time - start_time};

  timing_map_[category][subcategory][frame_id].elapsed = elapsed_time;

  AdjustSize(timing_map_[category][subcategory]);
}

void InsightService::LogTiming(std::string const& key,
                               std::vector<std::string> const& nodes,
                               FrameId frame_id) {
  using CallbackTimingRecord = std::map<std::string, TimingRecord>;
  using NodeTimingRecord = std::map<std::string, CallbackTimingRecord>;

  NodeTimingRecord selected_node_timing_record;

  auto specific_frame_timing_selecter{
      [&nodes, &frame_id, &selected_node_timing_record](
          std::string const& cur_node,
          std::map<std::string, std::map<FrameId, TimingRecord>> const&
              callback_timing_record) {
        auto node_timing_record{
            std::find(nodes.begin(), nodes.end(), cur_node)};
        if (node_timing_record == nodes.end()) {
          return;
        }

        std::for_each(
            callback_timing_record.begin(), callback_timing_record.end(),
            [&frame_id, &selected_node_timing_record,
             &cur_node](auto const& callback_record) {
              auto callback{callback_record.first};
              auto frame_timing_data_map{callback_record.second};

              auto timing_record{frame_timing_data_map.find(frame_id)};
              if (timing_record == frame_timing_data_map.end()) {
                return;
              }

              selected_node_timing_record[cur_node][callback] =
                  timing_record->second;
            });
      }};

  TraverseFirstCategory(timing_map_, specific_frame_timing_selecter,
                        mutex_timing_);

  Milliseconds total_elapsed_time{0ll};
  std::stringstream ss;
  ss << "frame: " << frame_id << ", ";

  auto result_formatter{
      [&ss, &total_elapsed_time](
          std::string const& node,
          std::map<std::string, TimingRecord> const& callback_timing) {
        Milliseconds one_node_total_elapsed_time{0ll};

        std::for_each(callback_timing.begin(), callback_timing.end(),
                      [&ss, &node, &one_node_total_elapsed_time](
                          auto const& callback_record) {
                        auto callback{callback_record.first};
                        auto timing_record{callback_record.second};

                        ss << node << "::" << callback << ": "
                           << timing_record.elapsed << " ms, ";

                        one_node_total_elapsed_time += timing_record.elapsed;
                      });

        ss << node << " total elapsed time: " << one_node_total_elapsed_time
           << " ms; ";
        total_elapsed_time += one_node_total_elapsed_time;
      }};

  TraverseFirstCategory(selected_node_timing_record, result_formatter,
                        mutex_timing_);
  ss << key << " elapsed time: " << total_elapsed_time << " ms";

  LOG(INFO) << ss.str();
}

void InsightService::LogFps(std::string const& category,
                            std::string const& subcategory) {
  std::lock_guard<std::mutex> lock(mutex_fps_);

  auto end_time{NowMilliseconds()};
  auto& fps_data{fps_map_[category][subcategory]};
  fps_data.frame_cnt++;

  if (fps_data.frame_cnt > 10) {
    if (fps_data.frame_cnt % fps_step_ == 0) {
      auto elapsed_time{end_time - fps_data.last_fps_time};
      if (fps_data.avg_fps == 0.0) {
        fps_data.avg_fps =
            fps_step_ * 1000.0 / static_cast<double>(elapsed_time);
      } else {
        fps_data.avg_fps =
            fps_data.avg_fps * (fps_data.frame_cnt - 1) / fps_data.frame_cnt +
            fps_step_ * 1000.0 / static_cast<double>(elapsed_time) /
                fps_data.frame_cnt;
      }

      fps_data.last_fps_time = end_time;
      LOG(INFO) << category << "::" << subcategory
                << ", FPS: " << fps_data.avg_fps;
    }
  } else {
    fps_data.last_fps_time = end_time;
  }
}

}  // namespace run::ex::insight_service