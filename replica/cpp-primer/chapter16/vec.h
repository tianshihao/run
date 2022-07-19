/**
 * @file vec.h
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief Ex 16.16
 * @version 0.1
 * @date 2022-10-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <memory>

// Forward declaration.
template <typename>
class Vec;

// Forward feclaration for friends.
template <typename T>
bool operator==(const Vec<T>&, const Vec<T>&);
template <typename T>
bool operator!=(const Vec<T>&, const Vec<T>&);
template <typename T>
bool operator<(const Vec<T>&, const Vec<T>&);
template <typename T>
bool operator>(const Vec<T>&, const Vec<T>&);
template <typename T>
bool operator<=(const Vec<T>&, const Vec<T>&);
template <typename T>
bool operator>=(const Vec<T>&, const Vec<T>&);

template <typename T>
class Vec {
 public:
  Vec() noexcept;
  Vec(std::initializer_list<T>) noexcept;
  Vec(Vec<T> const&) noexcept;
  Vec& operator=(Vec<T> const&) noexcept;
  Vec(Vec<T>&&) noexcept;
  Vec& operator=(Vec<T>&&) noexcept;
  ~Vec() noexcept;

  void PushBack(T const&);
  // TODO, emplace back operation if needed here.

  std::size_t Size() const { return rear - head; }
  std::size_t Capacity() const { return boundary - head; }

  T* Begin() const { return head; }
  T* End() const { return rear; }

  T& At(std::size_t pos) { return *(head + pos); }
  T const& At(std::size_t pos) const { return *(head + pos); }

  T& operator[](std::size_t pos) { return head[pos]; }
  T const& operator[](std::size_t pos) const { return head[pos]; }

  void Reserve(std::size_t);

  void Resize(std::size_t);
  void Resize(std::size_t, T const&);

  friend bool operator==<T>(const Vec<T>&, const Vec<T>&);
  friend bool operator!=<T>(const Vec<T>&, const Vec<T>&);
  // clang-format off
  friend bool operator< <T>(const Vec<T>&, const Vec<T>&);
  friend bool operator> <T>(const Vec<T>&, const Vec<T>&);
  // clang-format on
  friend bool operator<=<T>(const Vec<T>&, const Vec<T>&);
  friend bool operator>=<T>(const Vec<T>&, const Vec<T>&);

 private:
  void CheckNAlloc();
  void RangeInitialize(T const*, T const*);
  std::pair<T*, T*> AllocNCopy(T const*, T const*);
  void AllocNMove(std::size_t);
  void Reallocate();
  void Free() noexcept;

 private:
  T* head;
  T* rear;
  T* boundary;
  std::allocator<T> alloc;
};

template <typename T>
Vec<T>::Vec() noexcept : head(nullptr), rear(nullptr), boundary(nullptr) {}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> il) noexcept {
  RangeInitialize(il.begin(), il.end());
}

template <typename T>
Vec<T>::Vec(Vec<T> const& rhs) noexcept {
  RangeInitialize(rhs.Begin(), rhs.End());
}

template <typename T>
Vec<T>& Vec<T>::operator=(Vec<T> const& rhs) noexcept {
  auto new_head{AllocNCopy(rhs.Begin(), rhs.End())};

  // Different from copy constuctor, the copy assignment operator must free its
  // resource first, then take the new data.
  Free();
  head = new_head.first;
  rear = new_head.second;

  return *this;
}

template <typename T>
Vec<T>::Vec(Vec<T>&& rhs) noexcept
    : head(rhs.head), rear(rhs.rear), boundary(rhs.boundary) {
  rhs.head = rhs.rear = rhs.boundary = nullptr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(Vec<T>&& rhs) noexcept {
  if (this != &rhs) {
    // Same with copy assignment operator.
    Free();

    // Steal.
    head = rhs.head;
    rear = rhs.rear;
    boundary = rhs.boundary;

    rhs.head = rhs.rear = rhs.boundary = nullptr;
  }

  return *this;
}

template <typename T>
Vec<T>::~Vec() noexcept {
  Free();
}

template <typename T>
void Vec<T>::PushBack(const T& from) {
  CheckNAlloc();
  alloc.construct(rear++, from);
  return;
}

template <typename T>
void Vec<T>::Reserve(std::size_t new_cap) {
  if (new_cap <= Capacity()) {
    return;
  }
  AllocNMove(new_cap);
  return;
}

template <typename T>
void Vec<T>::Resize(std::size_t sz) {
  Resize(sz, T());
  return;
}

template <typename T>
void Vec<T>::Resize(std::size_t sz, T const& s) {
  if (sz > Size()) {
    // Need to reserve.
    if (sz > Capacity()) {
      Reserve(sz * 2);
      for (std::size_t i{Size()}; i != sz; ++i) {
        // Initial the new memory.
        alloc.construct(rear++, s);
      }
    }
    // Nothing to do.
    else {
    }
  } else if (sz < Size()) {
    // Destory the rear data but do not free memory.
    while (rear != head + sz) {
      alloc.destroy(--rear);
    }
  } else {
  }

  return;
}

template <typename T>
std::pair<T*, T*> Vec<T>::AllocNCopy(T const* b, T const* e) {
  auto result{alloc.allocate(e - b)};
  return {result, std::uninitialized_copy(b, e, result)};
}

template <typename T>
void Vec<T>::Free() noexcept {
  if (head) {
    std::for_each(head, rear, [this](T& rhs) { alloc.destroy(&rhs); });
    alloc.deallocate(head, boundary - head);
  }

  return;
}

template <typename T>
void Vec<T>::CheckNAlloc() {
  if (Size() == Capacity()) {
    Reallocate();
  }

  return;
}

template <typename T>
void Vec<T>::Reallocate() {
  auto new_cap{Size() ? 2 * Size() : 1};
  AllocNMove(new_cap);
  return;
}

template <typename T>
void Vec<T>::AllocNMove(std::size_t new_cap) {
  auto new_head{alloc.allocate(new_cap)};

  auto dest2constuct{new_head};
  auto elem2move{head};
  for (std::size_t i{0}; i != Size(); ++i) {
    // Move.
    alloc.construct(dest2constuct++, std::move(*elem2move++));
  }

  // Free the origin data.
  // TODO, I moved the data above, why do I need free origin data here?
  Free();

  head = new_head;
  rear = dest2constuct;
  boundary = head + new_cap;

  return;
}

template <typename T>
void Vec<T>::RangeInitialize(T const* first, T const* end) {
  auto new_head{AllocNCopy(first, end)};
  head = new_head.first;
  rear = boundary = new_head.second;
  return;
}

template <typename T>
bool operator==(Vec<T> const& lhs, Vec<T> const& rhs) {
  return (lhs.size() == rhs.size() &&
          std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <typename T>
bool operator!=(Vec<T> const& lhs, Vec<T> const& rhs) {
  return !(lhs == rhs);
}

template <typename T>
bool operator<(Vec<T> const& lhs, Vec<T> const& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}

template <typename T>
bool operator>(Vec<T> const& lhs, Vec<T> const& rhs) {
  return rhs < lhs;
}

template <typename T>
bool operator<=(Vec<T> const& lhs, Vec<T> const& rhs) {
  return !(rhs < lhs);
}

template <typename T>
bool operator>=(Vec<T> const& lhs, Vec<T> const& rhs) {
  return !(lhs < rhs);
}