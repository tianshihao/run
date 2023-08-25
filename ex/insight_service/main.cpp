#include <iostream>

#include "./insight_service.h"

namespace run::ex::insight_service {

void TestTiming() {
  auto &insight_service{InsightService::Instance()};

  for (int i{0}; i < 100; ++i) {
    {
      insight_service.StartTiming("operation", "step1", i);
      std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
      insight_service.StopTiming("operation", "step1", i);
    }

    {
      insight_service.StartTiming("operation", "step2", i);
      std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 100));
      insight_service.StopTiming("operation", "step2", i);
    }

    insight_service.LogTiming("TestTiming", {"operation"}, i);
    insight_service.LogFps("TestTiming", "operation");
  }
}

}  // namespace run::ex::insight_service

int main() {
  std::cout << "Hello World!" << std::endl;
  run::ex::insight_service::TestTiming();
  return 0;
}
