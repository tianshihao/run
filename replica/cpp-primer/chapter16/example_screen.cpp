#include <iostream>

#include "screen.h"

int TestScreen(int argc, char** argv) {
  int const width{10}, height{5};
  Screen<width, height> scrn{'e'};

  std::cout << "screen initial:\n";
  std::cout << scrn;

  std::cout << "move cursor to row 4 and column 7\n";
  scrn.Move(4, 7);

  std::cout << "set cursor to 'x'\n";
  scrn.Set('x');
  std::cout << scrn;

  std::cout << "set row 2 and column 4 to 'y' directly\n";
  scrn.Set(1, 3, 'y');
  std::cout << scrn;

  return 0;
}
