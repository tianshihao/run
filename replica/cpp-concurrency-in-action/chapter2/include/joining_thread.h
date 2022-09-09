#pragma once

#include <thread>

class JoiningThread {
  std::thread t;

 public:
  JoiningThread() noexcept = default;
  template <typename Callable, typename... Args>
  explicit JoiningThread(Callable &&func, Args &&...args)
      : t{std::forward<Callable>(func), std::forward<Args>(args)...} {}

  explicit JoiningThread(std::thread t_) noexcept : t{std::move(t_)} {}
  JoiningThread(JoiningThread &&other) noexcept : t{std::move(other.t)} {}

  JoiningThread &operator=(JoiningThread &&other) noexcept {
    if (Joinable()) {
      Join();
    }
    t = std::move(other.t);
    return *this;
  }

  JoiningThread &operator=(std::thread other) noexcept {
    if (Joinable()) {
      Join();
    }
    t = std::move(other);
    return *this;
  }

  ~JoiningThread() noexcept {
    if (Joinable()) {
      Join();
    }
  }

  bool Joinable() const noexcept { return t.joinable(); }
  void Join() { t.join(); }
  void Detach() { t.detach(); }
  std::thread &AsThread() noexcept { return; }
  std::thread const &AsThread() const noexcept { return t; }
};
