#include <iostream>

namespace playground::overloading_override_overwrite {
namespace overloading {
void example(int a) { std::cout << "example(int a): " << a << std::endl; }

// Not a valid overload.
// Attention: the top-level const will be ignored.
// void example(int const a) {
//   std::cout << "example(int const a): " << a << std::endl;
// }

void example(int* a) { std::cout << "example(int *a): " << a << std::endl; }

// Not a valid overload.
// Attention: the top-level const will be ignored.
// void example(int* const a) {
//   std::cout << "example(int * const a): " << a << std::endl;
// }

// But the low-level const will not be ignored.
void example(int const* a) {
  std::cout << "example(int const *a): " << a << std::endl;
}

void example(int& a) { std::cout << "example(int &a): " << a << std::endl; }

// void example(int const& a) {
//   std::cout << "example(int const &a): " << a << std::endl;
// }

void example(int a, int b) {
  std::cout << "example(int a, int b): " << a << ", " << b << std::endl;
}

void example(double a) { std::cout << "example(double a): " << a << std::endl; }
}  // namespace overloading

namespace override {
class Base {
 public:
  virtual void example() { std::cout << "Base::example()" << std::endl; }
};

class Derived : public Base {
 public:
  void example() override { std::cout << "Derived::example()" << std::endl; }
};

void example() {
  Base base;
  Derived derived;
  base.example();
  derived.example();

  Base* base_ptr{&derived};
  base_ptr->example();
}
}  // namespace override

namespace overwrite {
class Base {
 public:
  // Without virtual, the function will be overwritten.
  void example() { std::cout << "Base::example()" << std::endl; }
};

class Derived : public Base {
 public:
  // the function will overwrite the function in Base.
  void example() { std::cout << "Derived::example()" << std::endl; }
};

void example() {
  Base base;
  Derived derived;
  base.example();
  derived.example();

  Base* base_ptr{&derived};
  base_ptr->example();
}
}  // namespace overwrite

}  // namespace playground::overloading_override_overwrite

int main(int argc, char** argv) {
  using namespace playground::overloading_override_overwrite;

  int a{1};
  overloading::example(1);
  overloading::example(&a);
  overloading::example(1, 2);
  overloading::example(1.0);

  // override::example();
  // overwrite::example();

  return 0;
}
