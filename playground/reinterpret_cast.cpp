#include <iostream>

struct MyStruct {
  int x;
  int y;
  char c;
  bool b;
};

int main(int argc, char** argv) {
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

  // std::cout << *p << std::endl;
  char* cp{reinterpret_cast<char*>(p)};
  std::cout << "charactor c: " << *cp << ", size of charactor: " << sizeof(*cp)
            << std::endl;
  cp++;

  bool* bp{reinterpret_cast<bool*>(cp)};
  std::cout << "bool b: " << *bp << ", size of bool: " << sizeof(*bp)
            << std::endl;

  return 0;
}
