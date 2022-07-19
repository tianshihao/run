/**
 * @file shared_ptr.h
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief Ex 16.28, and moreover a lock-free implementation.
 * @version 0.1
 * @date 2022-11-02
 * @todo 1. Controal Block, done.
          2. Deleter.
          3. make_shared.
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <atomic>
#include <cstddef>
#include <iostream>
#include <type_traits>

struct ControlBlock {
  explicit ControlBlock() noexcept : _rc(1) {}

  std::atomic<std::size_t> _rc;
};

template <typename Type>
class SharedPtr {
 public:
  SharedPtr(Type* ptr = nullptr) noexcept;
  SharedPtr(SharedPtr const&) noexcept;
  SharedPtr& operator=(SharedPtr const&) noexcept;
  SharedPtr(SharedPtr&&) noexcept;
  SharedPtr& operator=(SharedPtr&&) noexcept;
  ~SharedPtr() noexcept;

  Type* Get() noexcept;
  std::size_t RefCnt() noexcept;
  void Release() noexcept;

 private:
  Type* _ptr;
  // Nullptr has no control block.
  ControlBlock* _cb;
};

template <typename Type>
SharedPtr<Type>::SharedPtr(Type* ptr) noexcept : _ptr(ptr) {
  if (nullptr != _ptr) {
    _cb = new ControlBlock();
  }
}

template <typename Type>
SharedPtr<Type>::SharedPtr(SharedPtr const& obj) noexcept
    : _ptr(obj._ptr), _cb(obj._cb) {
  if (nullptr != _ptr) {
    _cb->_rc.fetch_add(1);
  }
}

template <typename Type>
SharedPtr<Type>& SharedPtr<Type>::operator=(SharedPtr const& rhs) noexcept {
  // Self-assignment check.
  if (_ptr != rhs._ptr) {
    // Release the ownership of current source.
    Release();

    // Take over the rhs.
    _ptr = rhs._ptr;
    _cb = rhs._cb;

    // If the new pointer isn't nullptr, then incresement the count.
    if (nullptr != _ptr) {
      _cb->_rc.fetch_add(1);
    }
  }

  return *this;
}

template <typename Type>
SharedPtr<Type>::SharedPtr(SharedPtr&& obj) noexcept
    : _ptr(obj._ptr), _cb(obj._cb) {
  obj._ptr = obj._cb = nullptr;
}

template <typename Type>
SharedPtr<Type>& SharedPtr<Type>::operator=(
    SharedPtr<Type>&& dying_obj) noexcept {
  Release();

  // Stealing.
  _ptr = dying_obj._ptr;
  _cb = dying_obj._cb;
  dying_obj._ptr = dying_obj._rc = nullptr;

  return *this;
}

template <typename Type>
Type* SharedPtr<Type>::Get() noexcept {
  return _ptr;
}

template <typename Type>
std::size_t SharedPtr<Type>::RefCnt() noexcept {
  if (nullptr != _ptr) {
    return _cb->_rc;
  } else {
    return 0;
  }
}

template <typename Type>
SharedPtr<Type>::~SharedPtr<Type>() noexcept {
  Release();
}

template <typename Type>
void SharedPtr<Type>::Release() noexcept {
  // Only release on non-nullptr.
  if (nullptr != _ptr) {
    // Decrement reference count.
    _cb->_rc.fetch_sub(1);

    // If there are no SharedPtr to the resource.
    if (0 == _cb->_rc) {
      delete _cb;
      delete _ptr;
    }

    // Prevent dangling.
    _cb = nullptr;
    _ptr = nullptr;
  } else {
    std::cout << "Could not release a nullptr\n";
  }
}
