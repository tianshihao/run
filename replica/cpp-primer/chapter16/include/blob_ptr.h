/**
 * @file blob_ptr.h
 * @author Tian Shihao (shihao.tian@outlook.com)
 * @brief Ex 16.12
 * @version 0.1
 * @date 2022-09-21
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

template<typename Type>
class Blob;

template <typename>
class BlobPtr;

template <typename Type>
bool operator==(BlobPtr<Type> const &, BlobPtr<Type> const &);

template <typename Type>
bool operator<(BlobPtr<Type> const &, BlobPtr<Type> const &);

template <typename Type>
class BlobPtr {
  using size_type = typename Blob<Type>::size_type;

  // Oprators overloaded and class BlobPtr are one-to-one friend.
  friend bool operator==<Type>(const BlobPtr<Type> &, const BlobPtr<Type> &);
  friend bool operator< <Type>(const BlobPtr<Type> &, const BlobPtr<Type> &);

 public:
  BlobPtr() noexcept : curr{0} {}
  BlobPtr(Blob<Type> &blob, size_type sz = 0) noexcept
      : wptr{blob.GetData()}, curr{sz} {}

  Type &operator*() const {
    auto p{Check(curr, "Dereference past end.")};
    return (*p)[curr];
  }

  BlobPtr &operator++();
  BlobPtr &operator--();

  BlobPtr operator++(int);
  BlobPtr operator--(int);

 private:
  std::weak_ptr<std::vector<Type>> wptr;
  size_type curr;
  std::shared_ptr<std::vector<Type>> Check(size_type,
                                           std::string const &) const;
};

template <typename Type>
inline BlobPtr<Type> &BlobPtr<Type>::operator++() {
  Check(curr, "Increment past end of BlobPtr");
  ++curr;
  return *this;
}

template <typename Type>
inline BlobPtr<Type> &BlobPtr<Type>::operator--() {
  --curr;
  Check(curr, "Decrement past begin of BlobPtr");

  return *this;
}

template <typename Type>
inline BlobPtr<Type> BlobPtr<Type>::operator++(int) {
  BlobPtr<Type> ret{*this};
  ++(*this);
  return ret;
}

template <typename Type>
inline BlobPtr<Type> BlobPtr<Type>::operator--(int) {
  BlobPtr<Type> ret{*this};
  --(*this);
  return ret;
}

template <typename Type>
inline bool operator==(const BlobPtr<Type> &lhs, const BlobPtr<Type> &rhs) {
  if (lhs.wptr.lock() != rhs.wptr.lock()) {
    throw std::runtime_error("Pointers to difference Blobs!");
  }
  return lhs.curr == rhs.curr;
}

template <typename Type>
inline bool operator<(const BlobPtr<Type> &lhs, const BlobPtr<Type> &rhs) {
  if (lhs.wptr.lock() != rhs.wptr.lock()) {
    throw std::runtime_error("Pointers to difference Blobs!");
  }
  return lhs.curr < rhs.curr;
}

template <typename Type>
std::shared_ptr<std::vector<Type>> BlobPtr<Type>::Check(
    size_type i, std::string const &msg) const {
  auto ret{wptr.lock()};
  if (nullptr == ret) {
    throw std::runtime_error("Unbound Blob<Type>Ptr.");
  }
  if (i >= ret->size()) {
    throw std::out_of_range(msg);
  }
  return ret;
}
