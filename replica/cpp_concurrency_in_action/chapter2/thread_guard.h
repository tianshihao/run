#pragma once

#include <thread>

// Using RAII to wait for a thread to complete.
class ThreadGuard {
 private:
  // Reference to a thread.
  std::thread& t;

 public:
  explicit ThreadGuard(std::thread& t_) : t{t_} {}
  ~ThreadGuard() {
    if (t.joinable()) {
      t.join();
    }
  }

  // Copying or passing such an object would be dangerous, because it might then
  // outlive the scope if the thread it was joining.
  ThreadGuard(ThreadGuard const&) = delete;
  ThreadGuard& operator=(ThreadGuard const&) = delete;
};
