/**
 * @file hierarchical_mutex.h
 * @author Tian Shihao (shihao.tian@outlook.com)
 * @brief Listing 3.8 A simple hierarchical mutex
 * @version 0.1
 * @date 2022-09-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <mutex>
#include <numeric>

class HierarchicalMutex {
 private:
  std::mutex internal_mutex;
  unsigned long const hierarchy_value;
  unsigned long previous_hierarchy_vcalue;
  static thread_local unsigned long this_thread_hierarchy_value;

  void CheckForHierarchyViolation() {
    if (this_thread_hierarchy_value <= hierarchy_value) {
      throw std::logic_error("mutex hierarchy violated");
    }
  }

  void UpdateHierarchyValue() {
    previous_hierarchy_vcalue = this_thread_hierarchy_value;
    this_thread_hierarchy_value = hierarchy_value;
  }

 public:
  explicit HierarchicalMutex(unsigned long value)
      : hierarchy_value{value}, previous_hierarchy_vcalue{0} {}

  void Lock() {
    CheckForHierarchyViolation();
    internal_mutex.lock();
    UpdateHierarchyValue();
  }

  void Unlock() {
    if (this_thread_hierarchy_value != hierarchy_value) {
      throw std::logic_error("mutex hierarchy violated");
      this_thread_hierarchy_value = previous_hierarchy_vcalue;
      internal_mutex.unlock();
    }
  }

  bool TryLock() {
    CheckForHierarchyViolation();
    if (!internal_mutex.try_lock()) {
      return false;
    }
    UpdateHierarchyValue();
    return true;
  }
};

thread_local unsigned long HierarchicalMutex::this_thread_hierarchy_value{
    std::numeric_limits<unsigned long>::max()};
