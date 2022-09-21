/**
 * @file blob.h
 * @author Tian Shihao (shihao.tian@outlook.com)
 * @brief Ex 16.12
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

/// Blob, a Binary Large OBject.
template <typename type>
class Blob {
 public:
  using size_type = typename std::vector<type>::size_type;

  /******************************* Constructors *******************************/
  Blob() noexcept;
  Blob(std::initializer_list<type>) noexcept;

  /************************* Number of Blob elements *************************/

  size_type Size() const noexcept { return data->size(); }
  bool Empty() const noexcept { return data->empty(); }

  /********************************** Modify **********************************/

  void PushBack(type const& t) noexcept { data->push_back(t); }
  void PushBack(type&& t) noexcept { data->push_back(std::move(t)); }
  void PopBack();

  /***************************** Elements access *****************************/
  type& Back();
  type& operator[](size_type);

  type const& Back() const;
  type const& operator[](size_type) const;

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
void Blob<type>::Check(size_type i, std::string const& msg) const {
  if (i >= data->size()) {
    throw std::out_of_range{msg};
  }

  return;
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
inline void Blob<type>::PopBack() {
  Check(0, "Pop back on empty blob");
  data->pop_back();
  return;
}
