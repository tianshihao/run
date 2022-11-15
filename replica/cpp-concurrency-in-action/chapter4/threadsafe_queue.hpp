/**
 * @file threadsafe_queue.hpp
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief Listing 4.5 Full class definition of a thread-safe queue using
 * condtion variables.
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

template <typename T>
class ThreadsafeQueue {
 public:
  ThreadsafeQueue() noexcept = default;
  ThreadsafeQueue(ThreadsafeQueue const &other) noexcept {
    std::lock_guard<std::mutex> lk{other._mtx};
    _data_queue = other._data_queue;
  }
  ThreadsafeQueue &operator=(ThreadsafeQueue const &) = delete;

  void Push(T new_value) {
    std::lock_guard<std::mutex> lk{_mtx};
    _data_queue.push(new_value);
    _data_cond.notify_one();
    return;
  }

  // Tries to pop the value from the queue but always returns immediately (with
  // an indication of failure) even if there wasn’t a value to retrieve.
  bool TryPop(T &value) {
    std::lock_guard<std::mutex> lk{_mtx};
    if (_data_queue.empty()) {
      return false;
    }
    value = _data_queue.front();
    _data_queue.pop();
    return true;
  }
  std::shared_ptr<T> TryPop() {
    std::lock_guard<std::mutex> lk{_mtx};
    if (_data_queue.empty()) {
      return std::shared_ptr<T>();
    }
    std::shared_ptr<T> res{std::make_shared<T>(_data_queue.front())};
    _data_queue.pop();
    return res;
  }

  // Waits until there’s a value to retrieve.
  void WaitAndPop(T &value) {
    std::unique_lock<std::mutex> lk{_mtx};
    _data_cond.wait(lk, [this] { return !_data_queue.empty(); });
    value = _data_queue.front();
    _data_queue.pop();
  }

  std::shared_ptr<T> WaitAndPop() {
    std::unique_lock<std::mutex> lk{_mtx};
    _data_cond.wait(lk, [this] { return !_data_queue.empty(); });
    std::shared_ptr<T> res{std::make_shared<T>(_data_queue.front())};
    _data_queue.pop();
    return res;
  }

  bool Empty() const noexcept {
    std::lock_guard<std::mutex> lk{_mtx};
    return _data_queue.empty();
  }

 private:
  std::mutex mutable _mtx;
  std::queue<T> _data_queue;
  std::condition_variable _data_cond;
};

template class ThreadsafeQueue<int>;
template class ThreadsafeQueue<std::string>;
