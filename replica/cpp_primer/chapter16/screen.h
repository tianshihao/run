/**
 * @file screen.h
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief Ex 16.14
 * @version 0.2
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <iostream>
#include <ostream>
#include <string>

using pos = std::string::size_type;

template <pos W, pos H>
class Screen;

template <pos W, pos H>
std::ostream& operator<<(std::ostream& os, Screen<W, H>& scrn);
template <pos W, pos H>
std::istream& operator>>(std::istream& os, Screen<W, H>& scrn);

template <pos W, pos H>
class Screen {
 public:
  /****************** CONSTRUCTORS AND ASSIGNMENT OPERATORS ******************/
  Screen() noexcept = default;
  Screen(char c) noexcept;

  /******************** OTHER MEMBER FUNCTIONS AND FRIENDS ********************/

  friend std::ostream& operator<<<W, H>(std::ostream&, Screen&);
  friend std::istream& operator>><W, H>(std::istream&, Screen&);

  char Get() const;
  Screen& Set(char);
  Screen& Set(pos, pos, char);
  Screen& Move(pos, pos);
  pos GetCursor() const;

 private:
  pos cursor{0};
  pos width{W}, height{H};
  std::string contents;
};

template <pos W, pos H>
Screen<W, H>::Screen(char c) noexcept : contents(W * H, c){};

template <pos W, pos H>
std::ostream& operator<<(std::ostream& os, Screen<W, H>& scrn) {
  std::cout << std::endl;

  for (int i{0}; i < scrn.height; ++i) {
    os << scrn.contents.substr(i * scrn.width, scrn.width) << std::endl;
  }

  std::cout << "width: " << scrn.width << ", height: " << scrn.height
            << std::endl;
  std::cout << "cursor is in the row: " << scrn.cursor / scrn.width
            << ", column: " << scrn.cursor % scrn.width << std::endl;

  std::cout << std::endl;

  return os;
}

template <pos W, pos H>
std::istream& operator>>(std::istream& os, Screen<W, H>& scrn) {
  char c;
  os >> c;
  std::string temp(W * H, c);
  scrn.contents = temp;

  return os;
}

template <pos W, pos H>
char Screen<W, H>::Get() const {
  return contents[cursor];
}

template <pos W, pos H>
inline Screen<W, H>& Screen<W, H>::Set(char ch) {
  contents[cursor++] = ch;
  cursor = std::min(cursor, H * W);

  return *this;
}

template <pos W, pos H>
inline Screen<W, H>& Screen<W, H>::Set(pos r, pos c, char ch) {
  contents[r * W + c] = ch;
  return *this;
}

template <pos W, pos H>
inline Screen<W, H>& Screen<W, H>::Move(pos row, pos column) {
  pos r{row * width};
  cursor = r + column;

  return *this;
}

template <pos W, pos H>
inline pos Screen<W, H>::GetCursor() const {
  return cursor;
}
