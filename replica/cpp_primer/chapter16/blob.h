/**
 * @file blob.h
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief Ex 16.12 16.24
 * @version 0.3
 * @date 2022-11-01
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "blob_ptr.h"

/// @todo mark on book, explain why here do not need T after typename, cause T
/// is not used in forward declaration.
/// Forward declaration.
template <typename>
class Blob;
template <typename>
class BlobPtr;

template <typename type>
bool operator==(Blob<type> const&, Blob<type> const&);
template <typename type>
bool operator!=(Blob<type> const&, Blob<type> const&);
template <typename type>
bool operator<(Blob<type> const&, Blob<type> const&);
template <typename type>
bool operator>(Blob<type> const&, Blob<type> const&);
template <typename type>
bool operator<=(Blob<type> const&, Blob<type> const&);
template <typename type>
bool operator>=(Blob<type> const&, Blob<type> const&);
template <typename type>
std::ostream& operator<<(std::ostream&, Blob<type> const&);

/// Blob, a Binary Large OBject.
template <typename type>
class Blob {
 public:
  using size_type = typename std::vector<type>::size_type;

  /******************************* Constructors *******************************/
  Blob() noexcept;
  Blob(std::initializer_list<type>) noexcept;

  Blob(Blob<type> const&) noexcept;
  Blob& operator=(Blob<type> const&) noexcept;

  Blob(Blob<type>&&) noexcept;
  Blob& operator=(Blob<type>&&) noexcept;

  // TODO, could move it outside the class definition?
  template <typename It>
  Blob(It b, It e) noexcept : data(std::make_shared<std::vector<type>>(b, e)) {
    return;
  }

  /********************************* Friends *********************************/

  friend bool operator==<type>(Blob<type> const&, Blob<type> const&);
  friend bool operator!=<type>(Blob<type> const&, Blob<type> const&);
  // clang-format off
  friend bool operator< <type>(Blob<type> const&, Blob<type> const&);
  friend bool operator> <type>(Blob<type> const&, Blob<type> const&);
  // clang-format on
  friend bool operator<=<type>(Blob<type> const&, Blob<type> const&);
  friend bool operator>=<type>(Blob<type> const&, Blob<type> const&);
  friend std::ostream& operator<<<type>(std::ostream&, Blob<type> const&);

  /******************************* Data members *******************************/

  size_type Size() const noexcept { return data->size(); }
  bool Empty() const noexcept { return data->empty(); }

  void PushBack(type const& t) noexcept { data->push_back(t); }
  void PushBack(type&& t) noexcept { data->push_back(std::move(t)); }
  void PopBack();

  type& Front();
  type const& Front() const;
  type& Back();
  type const& Back() const;

  type& operator[](size_type);
  type const& operator[](size_type) const;

  BlobPtr<type> Begin();
  BlobPtr<type> End();

  std::shared_ptr<std::vector<type>> GetData() const noexcept { return data; }

 private:
  std::shared_ptr<std::vector<type>> data;

  void Check(size_type, std::string const&) const;
};

template <typename type>
Blob<type>::Blob() noexcept : data{std::make_shared<std::vector<type>>()} {}

template <typename type>
Blob<type>::Blob(std::initializer_list<type> il) noexcept
    : data{std::make_shared<std::vector<type>>(il)} {}

template <typename type>
Blob<type>::Blob(Blob<type> const& lhs) noexcept
    : data{std::make_shared<std::vector<type>>(*lhs.data)} {}

template <typename type>
Blob<type>& Blob<type>::operator=(Blob<type> const& lhs) noexcept {
  data = std::make_shared<std::vector<type>>(*lhs.data);
  return *this;
}

template <typename type>
Blob<type>::Blob(Blob<type>&& rhs) noexcept : data{std::move(rhs.data)} {}

template <typename type>
Blob<type>& Blob<type>::operator=(Blob<type>&& rhs) noexcept {
  if (this != rhs) {
    data = std::move(rhs.data);
    rhs.data = nullptr;
  }
  return *this;
}

template <typename type>
bool operator==(Blob<type> const& lhs, Blob<type> const& rhs) {
  return *lhs.data == *rhs.data;
}

template <typename type>
bool operator!=(Blob<type> const& lhs, Blob<type> const& rhs) {
  return !(lhs == rhs);
}

template <typename type>
bool operator<(Blob<type> const& lhs, Blob<type> const& rhs) {
  return std::lexicographical_compare(lhs.data->begin(), lhs.data->end(),
                                      rhs.data->begin(), rhs.data->end());
}

template <typename type>
bool operator>(Blob<type> const& lhs, Blob<type> const& rhs) {
  return rhs < lhs;
}

template <typename type>
bool operator<=(Blob<type> const& lhs, Blob<type> const& rhs) {
  return !(rhs > lhs);
}

template <typename type>
bool operator>=(Blob<type> const& lhs, Blob<type> const& rhs) {
  return !(lhs < rhs);
}

template <typename type>
std::ostream& operator<<(std::ostream& os, Blob<type> const& blob) {
  os << "[";
  for (int i{0}; i < blob.Size();) {
    os << blob[i++];
    if (i != blob.Size()) {
      os << " ";
    }
  }
  os << "]\n";
  return os;
}

template <typename type>
void Blob<type>::Check(size_type i, std::string const& msg) const {
  if (i >= data->size()) {
    throw std::out_of_range{msg};
  }

  return;
}

template <typename type>
inline type& Blob<type>::Front() {
  Check(0, "Front on empty blob");
  return data->front();
}

template <typename type>
inline type const& Blob<type>::Front() const {
  Check(0, "Front on empty blob");
  return data->front();
}

template <typename type>
inline type& Blob<type>::Back() {
  Check(0, "Back on empty blob");
  return data->back();
}

template <typename type>
inline type const& Blob<type>::Back() const {
  Check(0, "Back on empty blob");
  return data->back();
}

template <typename type>
inline type& Blob<type>::operator[](size_type i) {
  Check(i, "Subscript out of range");
  return (*data)[i];
}

template <typename type>
inline type const& Blob<type>::operator[](size_type i) const {
  Check(i, "Subscript out of range");
  return (*data)[i];
}

template <typename type>
inline BlobPtr<type> Blob<type>::Begin() {
  return BlobPtr<type>{*this};
}

template <typename type>
inline BlobPtr<type> Blob<type>::End() {
  return BlobPtr<type>{*this, data->size() - 1};
}

template <typename type>
inline void Blob<type>::PopBack() {
  Check(0, "Pop back on empty blob");
  data->pop_back();
  return;
}
