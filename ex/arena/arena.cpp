#include "arena.h"
namespace ex::arena {

size_t Arena::_calculate_allocating_bytes(size_t bytes) const {
  // 2^N size near requested bytes
  if (bytes > MAX_BLOCK_SIZE) {
    return ((bytes - 1) & ~(MIN_BLOCK_SIZE - 1)) + MIN_BLOCK_SIZE;
  }
  // 2 times the last block capacity
  int increased_unit =
      blocks_.empty() ? MIN_BLOCK_SIZE : blocks_.back()->capacity() * 2;
  increased_unit = std::min(increased_unit, MAX_BLOCK_SIZE);
  // 2 times growth
  while (increased_unit < (int)bytes) {
    increased_unit <<= 1;
  }
  // CHECK_GT(increased_unit, 0)
  //     << "Too large memory allocation requested!";  // in case overflow
  return increased_unit;
}

void Arena::reserve(size_t bytes) {
  if (!_has_capacity(bytes)) {
    return;
  }
  // pop back empty but small blocks
  while (!blocks_.empty() && blocks_.back()->size() == 0) {
    capacity_ -= blocks_.back()->size();
    blocks_.pop_back();
  }

  size_t reserved_bytes = _calculate_allocating_bytes(bytes);
  blocks_.emplace_back(std::make_shared<Block>(reserved_bytes, type_));
  capacity_ += reserved_bytes;
}

// leave only 1 block
void Arena::reset() {
  if (blocks_.empty()) {
    return;
  }
  while (blocks_.size() > 1) {
    capacity_ -= blocks_.back()->capacity();
    blocks_.pop_back();
  }
  blocks_[0]->reset();
}

bool Arena::_has_capacity(size_t bytes) const {
  return !blocks_.empty() && blocks_.back()->has_capacity(bytes);
}

Arena::Block::Block(size_t bytes, MemoryType type)
    : cursor_(0), capacity_(bytes), type_(type) {
  switch (type) {
    case MemoryType::DEVICE_MEMORY:
      // CUDA_SAFE_CALL(cudaMalloc((void**)&p_data_, bytes));
      break;
    case MemoryType::PINNED_MEMORY:
      // CUDA_SAFE_CALL(cudaMallocHost((void**)&p_data_, bytes));
      break;
    case MemoryType::HOST_MEMORY:
      p_data_ = new char[bytes];
      break;
    default:
      // CHECK(false) << "Unknown type of memory " << (int)type;
      break;
  }
}

Arena::Block::~Block() {
  switch (type_) {
    case MemoryType::DEVICE_MEMORY:
      // CUDA_SAFE_CALL(cudaFree(p_data_));
      break;
    case MemoryType::PINNED_MEMORY:
      // CUDA_SAFE_CALL(cudaFreeHost(p_data_));
      break;
    case MemoryType::HOST_MEMORY:
      delete[] p_data_;
      break;
    default:
      // CHECK(false) << "Unknown type of memory " << (int)type_;
      break;
  }
}

// allocate memory beginning with 8-bytes alignment(memory address is a multiple
// of 8)
void* Arena::Block::allocate(size_t bytes) {
  size_t padding = _padding_bytes(bytes);
  char* p_addr = p_data_ + cursor_ + padding;
  cursor_ +=
      (bytes + padding);  // move cursor to the end of current allocated space
  return p_addr;
}

size_t Arena::Block::_padding_bytes(size_t bytes) const {
  // refers to:
  // https://stackoverflow.com/questions/2846914/what-is-meant-by-memory-is-8-bytes-aligned
  const static int alignment = sizeof(void*) > 8 ? sizeof(void*) : 8;
  const static int mod = alignment - 1;
  char* p_addr = p_data_ + cursor_;
  size_t remainder = reinterpret_cast<uintptr_t>(p_addr) & mod;
  int padding = (remainder == 0 ? 0 : alignment - remainder);
  return padding;
}

}  // namespace ex::arena