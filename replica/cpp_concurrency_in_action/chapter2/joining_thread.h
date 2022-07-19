#pragma once

#include <thread>

class JoiningThread {
  std::thread t;

 public:
  /******************************* Constructor. *******************************/

  JoiningThread() noexcept = default;
  // ? Why there use std::forward? What is it means?
  template <typename Callable, typename... Args>
  explicit JoiningThread(Callable &&func, Args &&...args)
      : t{std::forward<Callable>(func), std::forward<Args>(args)...} {}

  /***************************** Copy Semantics. *****************************/

  // Transfer ownership.
  explicit JoiningThread(std::thread t_) noexcept : t{std::move(t_)} {}

  JoiningThread &operator=(std::thread other) noexcept {
    if (Joinable()) {
      Join();
    }
    t = std::move(other);
    return *this;
  }

  /**************************** Move Semantics. ****************************/

  JoiningThread(JoiningThread &&other) noexcept : t{std::move(other.t)} {}

  JoiningThread &operator=(JoiningThread &&other) noexcept {
    if (Joinable()) {
      Join();
    }
    t = std::move(other.t);
    return *this;
  }

  ~JoiningThread() noexcept {
    if (Joinable()) {
      Join();
    }
  }

  void Swap(JoiningThread &other) noexcept { t.swap(other.t); }
  std::thread::id GetID() const noexcept { return t.get_id(); }
  bool Joinable() const noexcept { return t.joinable(); }
  void Join() { t.join(); }
  void Detach() { t.detach(); }
  std::thread &AsThread() noexcept { return t; }
  std::thread const &AsThread() const noexcept { return t; }
};
