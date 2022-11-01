/**
 * @file find.h
 * @author Tian Shihao (shihao.tian@outlook.com)
 * @brief Ex 16.4
 * @version 0.1
 * @date 2022-10-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

template <typename Itertor, typename Value>
auto Find(Itertor first, Itertor last, Value const &val) {
  for (; first != last && *first != val; ++first) {
  }

  return first;
}
