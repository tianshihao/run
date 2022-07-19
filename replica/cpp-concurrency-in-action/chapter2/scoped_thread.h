#pragma once

#include <thread>

/// @brief ScopedThread could take ownership of a thread, thats means no one
/// else can join or detach the thread. It would primarily be aimed at
/// ensuring that thread are completed before a scope is exited.
class ScopedThread {
  std::thread t;

 public:
  explicit ScopedThread(std::thread t_) : t{std::move(t_)} {
    if (!t.joinable()) {
      throw std::logic_error("No thread");
    }
  }

  ~ScopedThread() { t.join(); }

  ScopedThread(ScopedThread const &) = delete;
  ScopedThread &operator=(ScopedThread const &) = delete;
};
