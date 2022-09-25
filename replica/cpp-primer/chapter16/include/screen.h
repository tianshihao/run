/**
 * @file screen.h
 * @author Tian Shihao (shihao.tian@outlook.com)
 * @brief Ex 16.14
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <iostream>
#include <string>

template <unsigned W, unsigned H>
class Screen {
  using size_type = typename std::string::size_type;

 public:
  Screen() noexcept = default;
  Screen(char c) : contents(W * H, c) {}

  char Get() const { return contents[cursor]; }
  // Move cursor.
  Screen& Move(size_type, size_type);

  friend std::ostream& operator<<(std::ostream& os, Screen& scrn) {
    for (int i{0}; i < scrn.height; ++i) {
      os << scrn.contents.substr(0, W) << std::endl;
    }

    return os;
  }

  friend std::istream& operator>>(std::istream& os, Screen& scrn) {
    char c;
    os >> c;
    std::string temp(W * H, c);
    scrn.contents = temp;

    return os;
  }

 private:
  size_type cursor{0};
  size_type width{W}, height{H};
  std::string contents;
};

template <unsigned W, unsigned H>
inline Screen<W, H>& Screen<W, H>::Move(size_type row, size_type column) {
  size_type r{row * width};
  cursor = r + column;

  return *this;
}
