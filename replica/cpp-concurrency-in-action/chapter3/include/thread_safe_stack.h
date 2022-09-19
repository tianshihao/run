/**
 * @file thread_safe_stack.h
 * @author Tian Shihao (shihao.tian@outlook.com)
 * @brief Listing 3.5 A fleshed-out class definition for a thread-safe stack
 * @version 0.1
 * @date 2022-09-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct EmptyStack : std::exception {
  const char* what() const throw();
};

template <typename T>
class ThreadSafeStack {
 private:
  std::stack<T> data;
  mutable std::mutex m;

 public:
  ThreadSafeStack();

  // Do copy in the constructor body rather than the member initializer list
  // in order to ensure that the mutex is held across the copy.
  ThreadSafeStack(ThreadSafeStack const& other) {
    // The copy constructor locks the mutex in the source object and then
    // copies the internal stack.
    // ? What is the difference between lock this->m and other.m here?
    // * This stack implementation is copyable ---- the copy constructor locks
    // * the mutex in the source object and then copies the internal stack.
    std::lock_guard<std::mutex> lock{other.m};
    data = other.data;
  }
  // Assignment operator is deleted.
  // And there's no Swap() function.
  ThreadSafeStack& operator=(ThreadSafeStack const&) = delete;

  void Push(T new_value) {
    std::lock_guard<std::mutex> lock{m};
    data.push(std::move(new_value));

    return;
  }

  // Option 1: Returns std::shared_ptr<>.
  std::shared_ptr<T> Pop() {
    std::lock_guard<std::mutex> lock{m};
    if (data.empty()) {
      throw EmptyStack();
    }
    // Allocate return value before modifying stack.
    std::shared_ptr<T> const res{std::make_shared<T>(data.top())};
    data.pop();
    return res;
  }

  // Option 3: Takes a reference to a location in which to store the value.
  void Pop(T& value) {
    std::lock_guard<std::mutex> lock{m};
    if (data.empty()) {
      throw EmptyStack();
    }
    value = data.top();
    data.pop();

    return;
  }

  bool Empty() const {
    std::lock_guard<std::mutex> lock{m};

    return data.empty();
  }
};
