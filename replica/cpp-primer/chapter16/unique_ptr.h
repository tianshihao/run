/**
 * @file unique_ptr.h
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief Ex 16.28
 * @version 0.1
 * @date 2022-11-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstddef>
#include <variant>

template <typename Type>
class UniquePtr {
 public:
  UniquePtr<Type>(Type* ptr = nullptr) noexcept : _ptr(ptr) {}
  ~UniquePtr<Type>() noexcept { delete _ptr; }

  // Prohibit copy.
  UniquePtr<Type>(UniquePtr<Type> const&) = delete;
  UniquePtr<Type>& operator=(UniquePtr<Type> const&) = delete;

  UniquePtr<Type>(UniquePtr<Type>&& dying_obj) noexcept : _ptr(dying_obj._ptr) {
    dying_obj._ptr = nullptr;
  }

  UniquePtr<Type>& operator=(UniquePtr<Type>&& rhs) noexcept {
    Reset();
    _ptr = rhs._ptr;
    rhs._ptr = nullptr;
    return *this;
  }

  UniquePtr<Type>& operator=(std::nullptr_t) noexcept {
    Reset();
    return *this;
  }

  void Swap(UniquePtr<Type>& other) noexcept {
    std::swap(_ptr, other._ptr);
    return;
  }

  bool Bool() const noexcept { return _ptr == nullptr ? false : true; }

  Type* Get() const noexcept { return _ptr; }

  // Release the ownship.
  Type* Release() noexcept {
    auto ret{_ptr};
    _ptr = nullptr;
    return ret;
  }

  void Reset(Type* ptr = nullptr) noexcept {
    delete _ptr;
    _ptr = ptr;

    return;
  }

  Type& operator*() const { return *_ptr; }

  Type* operator->() const noexcept { return _ptr; }

 private:
  Type* _ptr{nullptr};
};
