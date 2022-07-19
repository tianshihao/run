/**
 * @file blob_ptr.h
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief Ex 16.12
 * @version 0.2
 * @date 2022-10-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "blob.h"

template <typename T>
class Blob;
template <typename>
class BlobPtr;

template <typename T>
bool operator==(BlobPtr<T> const &, BlobPtr<T> const &);
template <typename T>
bool operator!=(BlobPtr<T> const &, BlobPtr<T> const &);
template <typename T>
bool operator<(BlobPtr<T> const &, BlobPtr<T> const &);
template <typename T>
bool operator>(BlobPtr<T> const &, BlobPtr<T> const &);
template <typename T>
bool operator<=(BlobPtr<T> const &, BlobPtr<T> const &);
template <typename T>
bool operator>=(BlobPtr<T> const &, BlobPtr<T> const &);

template <typename T>
class BlobPtr {
 public:
  using size_type = typename Blob<T>::size_type;

  BlobPtr() noexcept;
  BlobPtr(Blob<T> &blob, size_type sz = 0) noexcept;

  /********************************* Friends *********************************/

  friend bool operator==<T>(const BlobPtr<T> &, const BlobPtr<T> &);
  friend bool operator!=<T>(const BlobPtr<T> &, const BlobPtr<T> &);
  // clang-format off
  friend bool operator< <T>(const BlobPtr<T> &, const BlobPtr<T> &);
  // clang-format on
  friend bool operator><T>(const BlobPtr<T> &, const BlobPtr<T> &);
  friend bool operator<=<T>(const BlobPtr<T> &, const BlobPtr<T> &);
  friend bool operator>=<T>(const BlobPtr<T> &, const BlobPtr<T> &);

  /******************************* Data members *******************************/

  T &operator*() const;

  BlobPtr &operator++();
  BlobPtr &operator--();

  BlobPtr operator++(int);
  BlobPtr operator--(int);

  BlobPtr &operator+=(size_type);
  BlobPtr &operator-=(size_type);

 private:
  std::weak_ptr<std::vector<T>> wptr;
  size_type curr;
  std::shared_ptr<std::vector<T>> Check(size_type, std::string const &) const;
};

template <typename T>
BlobPtr<T>::BlobPtr() noexcept : curr{0} {}

template <typename T>
BlobPtr<T>::BlobPtr(Blob<T> &blob, size_type sz) noexcept
    : wptr(blob.GetData()), curr(sz) {}

template <typename T>
inline bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
  if (lhs.wptr.lock() != rhs.wptr.lock()) {
    throw std::runtime_error("pointers to same Blobs!");
  }
  return lhs.curr == rhs.curr;
}

template <typename T>
inline bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
  if (lhs.wptr.lock() != rhs.wptr.lock()) {
    throw std::runtime_error("pointers to same Blobs!");
  }
  return !(lhs.curr == rhs.curr);
}

template <typename T>
inline bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
  if (lhs.wptr.lock() != rhs.wptr.lock()) {
    throw std::runtime_error("pointers to same Blobs!");
  }
  return lhs.curr < rhs.curr;
}

template <typename T>
inline bool operator>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
  if (lhs.wptr.lock() != rhs.wptr.lock()) {
    throw std::runtime_error("pointers to same Blobs!");
  }
  return !(lhs.curr < rhs.curr);
}

template <typename T>
inline bool operator<=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
  if (lhs.wptr.lock() != rhs.wptr.lock()) {
    throw std::runtime_error("pointers to same Blobs!");
  }
  return !(lhs.curr > rhs.curr);
}

template <typename T>
inline bool operator>=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
  if (lhs.wptr.lock() != rhs.wptr.lock()) {
    throw std::runtime_error("pointers to same Blobs!");
  }
  return !(lhs.curr < rhs.curr);
}

template <typename T>
inline T &BlobPtr<T>::operator*() const {
  auto p{Check(curr, "dereference past end.")};
  return (*p)[curr];
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::operator++() {
  Check(curr, "increment past end of BlobPtr");
  ++curr;
  return *this;
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::operator--() {
  --curr;
  Check(curr, "Decrement past begin of BlobPtr");

  return *this;
}

template <typename T>
inline BlobPtr<T> BlobPtr<T>::operator++(int) {
  BlobPtr<T> ret{*this};
  ++(*this);
  return ret;
}

template <typename T>
inline BlobPtr<T> BlobPtr<T>::operator--(int) {
  BlobPtr<T> ret{*this};
  --(*this);
  return ret;
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::operator+=(size_type i) {
  curr += i;
  Check(curr, "increment past end of BlobPtr");
  return *this;
}

template <typename T>
inline BlobPtr<T> &BlobPtr<T>::operator-=(size_type i) {
  curr -= i;
  Check(curr, "decrement past end of BlobPtr");
  return *this;
}

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::Check(
    size_type i, std::string const &msg) const {
  auto ret{wptr.lock()};
  if (nullptr == ret) {
    throw std::runtime_error("unbound BlobPtr.");
  }
  if (i >= ret->size()) {
    throw std::out_of_range(msg);
  }
  return ret;
}
