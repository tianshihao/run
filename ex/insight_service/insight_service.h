#pragma once

#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "utils/macros.h"
#include "utils/time.hpp"

namespace run::ex::insight_service {
using namespace run::time;

class InsightService {
  using FrameId = int;

 public:
  void StartTiming(std::string const& category, std::string const& subcategory,
                   FrameId frame_id);
  void StopTiming(std::string const& category, std::string const& subcategory,
                  FrameId frame_id);

  void StartTiming(std::string const& category, std::string const& subcategory,
                   FrameId frame_id, Milliseconds start);
  void StopTiming(std::string const& category, std::string const& subcategory,
                  FrameId frame_id, Milliseconds stop);

  void LogTiming(std::string const& key,
                 std::vector<std::string> const& categories, FrameId frame_id);

  void LogFps(std::string const& category, std::string const& subcategory);

 private:
  template <typename K, typename V>
  void AdjustSize(std::map<K, V>& data) {
    if (data.size() > history_size_) {
      data.erase(data.begin());
    }
  }

  template <typename MapType, typename Operation>
  void TraverseFirstCategory(MapType const& map, Operation&& operation,
                             std::mutex& mutex) {
    std::lock_guard<std::mutex> lock(mutex);

    for (auto const& category_entry : map) {
      std::string const& category{category_entry.first};
      operation(category, category_entry.second);
    }
  }

  constexpr static std::size_t history_size_ = 30;

  // For timing.
  struct TimingRecord {
    Milliseconds start{0};
    Milliseconds elapsed{0};
  };
  std::mutex mutex_timing_;
  std::map<std::string, std::map<std::string, std::map<FrameId, TimingRecord>>>
      timing_map_;

  // For FPS.
  struct FpsData {
    int frame_cnt{0};
    Milliseconds last_fps_time{0};
    double avg_fps{0.0};
  };
  std::mutex mutex_fps_;
  int fps_step_{5};
  std::map<std::string, std::map<std::string, FpsData>> fps_map_;

  DECLARE_CLASS_SINGLETON(InsightService)
};

}  // namespace run::ex::insight_service