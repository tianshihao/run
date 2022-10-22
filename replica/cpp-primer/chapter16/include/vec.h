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

template <typename>
class Vec;

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
  friend bool operator==<T>(const Vec<T>&, const Vec<T>&);
  friend bool operator!=<T>(const Vec<T>&, const Vec<T>&);
  // clang-format off
  friend bool operator< <T>(const Vec<T>&, const Vec<T>&);
  friend bool operator> <T>(const Vec<T>&, const Vec<T>&);
  // clang-format on
  friend bool operator<=<T>(const Vec<T>&, const Vec<T>&);
  friend bool operator>=<T>(const Vec<T>&, const Vec<T>&);

 public:
  Vec() noexcept;
  Vec(std::initializer_list<T>) noexcept;
  Vec(Vec<T> const&) noexcept;
  Vec& operator=(Vec<T> const&) noexcept;
  Vec(Vec<T>&&) noexcept;
  Vec& operator=(Vec<T>&&) noexcept;
  ~Vec();

  void PushBack(T const&);
  size_t Size() const { return first_free - elements; }
  size_t Capacity() const { return cap - elements; }
  T* Begin() const { return elements; }
  T* End() const { return first_free; }

  T& At(size_t pos) { return *(elements + pos); }
  T const& At(size_t pos) const { return *(elements + pos); }
  T& operator[](size_t pos) { return elements[pos]; }
  T const& operator[](size_t pos) const { return elements[pos]; }

  void Reserve(size_t);
  void Resize(size_t);
  void Resize(size_t, T const&);

 private:
  std::pair<T*, T*> AllocNCopy(T const*, T const*);
  void Free();
  void CheckNAlloc();
  void Reallocate();
  void AllocNMove(size_t);
  void RangeInitialize(T const*, T const*);

 private:
  T* elements;
  T* first_free;
  T* cap;
  std::allocator<T> alloc;
};

template <typename T>
Vec<T>::Vec() noexcept : elements(nullptr), first_free(nullptr), cap(nullptr) {}

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
  auto data{AllocNCopy(rhs.Begin(), rhs.End())};
  Free();
  elements = data.first;
  first_free = data.second;
  return *this;
}

template <typename T>
Vec<T>::Vec(Vec<T>&& rhs) noexcept
    : elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap) {
  rhs.elements = rhs.first_free = rhs.cap = nullptr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(Vec<T>&& rhs) noexcept {
  if (this != &rhs) {
    Free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
  return *this;
}

template <typename T>
Vec<T>::~Vec() {
  Free();
}

template <typename T>
void Vec<T>::PushBack(const T& from) {
  CheckNAlloc();
  alloc.construct(first_free++, from);
  return;
}

template <typename T>
void Vec<T>::Reserve(size_t new_cap) {
  if (new_cap <= Capacity()) {
    return;
  }
  AllocNMove(new_cap);
  return;
}

template <typename T>
void Vec<T>::Resize(size_t cnt) {
  Resize(cnt, T());
  return;
}

template <typename T>
void Vec<T>::Resize(size_t cnt, T const& s) {
  if (cnt > Size()) {
    if (cnt > Capacity()) {
      Reserve(cnt * 2);
      for (size_t i{Size()}; i != cnt; ++i) {
        alloc.construct(first_free++, s);
      }
    }
  } else if (cnt < Size()) {
    while (first_free != elements + cnt) {
      alloc.destory(--first_free);
    }
  } else {
  }

  return;
}

template <typename T>
std::pair<T*, T*> Vec<T>::AllocNCopy(T const* b, T const* e) {
  auto data{alloc.allocate(e - b)};
  return {data, std::uninitialized_copy(b, e, data)};
}

template <typename T>
void Vec<T>::Free() {
  if (elements) {
    std::for_each(elements, first_free,
                  [this](T& rhs) { alloc.destory(&rhs); });
    alloc.deallocate(elements, cap - elements);
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
void Vec<T>::AllocNMove(size_t new_cap) {
  auto new_data{alloc.allocate(new_cap)};
  auto dest{new_data};
  auto elem{elements};
  for (size_t i{0}; i != Size(); ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  Free();
  elements = new_data;
  first_free = dest;
  cap = elements + new_cap;

  return;
}

template <typename T>
void Vec<T>::RangeInitialize(T const* first, T const* end) {
  auto new_data{AllocNCopy(first, end)};
  elements = new_data.first;
  first_free = cap = new_data.second;
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