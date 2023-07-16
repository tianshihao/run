/******************************************************************************
  @brief Simple Memory Pool for both CPU and GPU.  usage: reserved memory when
  program is initialized, reset memory after use, 2 interface:
            1. allocate<T>(num);
            2. reset();
      notice: NOT thread safe version
*/
#pragma once

#include <climits>
#include <memory>
#include <vector>

#include "macros.h"
// #include "cuda_runtime.h"

enum class MemoryType { DEVICE_MEMORY = 0, PINNED_MEMORY = 1, HOST_MEMORY = 2 };

const static int MIN_BLOCK_SIZE = 4096;      // 4KB
const static int MAX_BLOCK_SIZE = 64 << 20;  // 64MB

class Arena {
 public:
  Arena(MemoryType type = MemoryType::HOST_MEMORY)
      : type_(type), capacity_(0) {}
  virtual ~Arena() = default;

  template <typename T>
  T* allocate(size_t num);

  void reserve(size_t bytes);

  void reset();

  size_t capacity() const { return capacity_; }

 private:
  // memory management unit
  class Block;
  bool _has_capacity(size_t bytes) const;
  size_t _calculate_allocating_bytes(size_t bytes) const;

  std::vector<std::shared_ptr<Block>> blocks_;
  MemoryType type_;
  size_t capacity_;
  // DISALLOW_COPY_AND_ASSIGN(Arena);
};

class Arena::Block {
 public:
  explicit Block(size_t bytes, MemoryType type = MemoryType::DEVICE_MEMORY);

  virtual ~Block();

  void* allocate(size_t bytes);

  void reset() { cursor_ = 0; }

  size_t size() const { return cursor_; }

  size_t capacity() const { return capacity_; }

  bool has_capacity(size_t bytes) const {
    return capacity_ - cursor_ >= (bytes + _padding_bytes(bytes));
  }

 private:
  size_t _padding_bytes(size_t bytes) const;

  char* p_data_;
  size_t cursor_;
  size_t capacity_;
  MemoryType type_;
};

template <typename T>
T* Arena::allocate(size_t num) {
  size_t bytes = num * sizeof(T);
  if (!_has_capacity(bytes)) {
    reserve(bytes);
  }
  return static_cast<T*>(blocks_.back()->allocate(bytes));
}
