#include <iostream>

#include "screen.h"

int TestScreen(int argc, char** argv) {
  Screen<10, 5> scrn{'e'};
  std::cout << scrn;
  std::cout << scrn.Get() << std::endl;

  return 0;
}