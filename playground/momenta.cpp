#include <array>
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

namespace run::playground::momenta {}  // namespace run::playground::momenta

int main() {
  constexpr auto kNum{100};
  constexpr auto kThreadNum{5};

  std::array<int, kNum> nums{};
  std::atomic<int> next_index{0};

  std::array<int, kThreadNum> write_count{};
  write_count.fill(0);

  std::vector<std::thread> workers;
  workers.reserve(kThreadNum);

  for (auto tid{0}; tid < kThreadNum; ++tid) {
    workers.emplace_back([tid, &nums, &next_index, &write_count]() {
      while (true) {
        auto i{next_index.fetch_add(1, std::memory_order_relaxed)};
        if (i >= static_cast<int>(nums.size())) {
          break;
        }
        nums[i] = tid;
        ++write_count[tid];
      }
    });
  }

  for (auto& th : workers) {
    th.join();
  }

  auto total{0};
  for (auto tid{0}; tid < kThreadNum; ++tid) {
    std::cout << "thread " << tid << " wrote " << write_count[tid] << "\n";
    total += write_count[tid];
  }
  std::cout << "total writes = " << total << "\n";
  return 0;
}
