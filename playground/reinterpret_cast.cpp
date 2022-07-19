#include <iostream>

namespace playground::reinterpret_cast_example {
struct MyStruct {
  int x;
  int y;
  char c;
  bool b;
};

void reinterpret_cast_example() {
  MyStruct s;
  s.x = 1;
  s.y = 2;
  s.c = 'c';
  s.b = true;

  int* p{reinterpret_cast<int*>(&s)};

  std::cout << "integer x: " << *p << ", size of integer: " << sizeof(*p)
            << std::endl;
  p++;

  std::cout << "integer y: " << *p << ", size of integer: " << sizeof(*p)
            << std::endl;
  p++;

  std::cout << *p << std::endl;
  // The operation above will explain the data start from the address of p as
  // integer, however, the data is not integer, so the output is not expected.
  // This is the reason why we need reinterpret_cast.

  char* cp{reinterpret_cast<char*>(p)};
  std::cout << "charactor c: " << *cp << ", size of charactor: " << sizeof(*cp)
            << std::endl;
  cp++;

  bool* bp{reinterpret_cast<bool*>(cp)};
  std::cout << "bool b: " << *bp << ", size of bool: " << sizeof(*bp)
            << std::endl;
}

}  // namespace playground::reinterpret_cast_example

int main(int argc, char** argv) {
  playground::reinterpret_cast_example::reinterpret_cast_example();

  return 0;
}
