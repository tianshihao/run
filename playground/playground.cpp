#include <iostream>

class A {
 public:
  A() = default;

  void Print(int b) const {
    std::cout << _a << '\n';
    b = 2;
    std::cout << b << '\n';
  }

 private:
  int _a{0};
};

void Test() {
  // [[maybe_unused]] A b;
  [[maybe_unused]] A b;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  A a;
  a.Print(1);

  Test();

  return 0;
}