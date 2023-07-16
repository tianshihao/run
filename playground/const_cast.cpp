#include <iostream>

// top-level const: indicate that the object itself is const. For example:
// int const a; int* const p.
//
// low-level const: a pointer or reference that points to a const object. For
// example int const* p; or const int* p, the first one is recommended.
// int const* p, reading from right to left, p is a pointer to a const integer.
//
// Trick: const appears at left of *, then it is low-level const, otherwise
// it is top-level const.

namespace playground::const_cast_example {
// E.g. 1 top-level const on original object and low-level const on pointer.
void example1() {
  std::cout << "example 1: \n";

  int const original{10};
  int const* pointer{&original};
  int* const_cast_pointer{const_cast<int*>(pointer)};

  std::cout << "before modify const_cast_pointer: \n";
  std::cout << "original: " << original << std::endl;
  std::cout << "*const_cast_pointer: " << *const_cast_pointer << std::endl;

  *const_cast_pointer = 20;  // invalid, undefined behavior, cause the oringinal
                             // data original is const.

  std::cout << "after modify const_cast_pointer: \n";
  std::cout << "original: " << original << std::endl;
  std::cout << "*const_cast_pointer: " << *const_cast_pointer << std::endl;
}

// E.g. 2 only low-level const on pointer.
// In E.g. 2, the const qualifier of pointer is a low-level const, which means
// the pointer points to a const object. So we can't change the object
// through pointer itself. They only prevent us from changing the data through
// this pointer. But if we use const_cast to remove the const qualifier, we can
// change the object through this pointer. "cast away!"
//
// And also we can access original object through other pointers or references,
// and change the data.
void example2() {
  std::cout << "example 2: \n";

  int original{10};
  int const* pointer{&original};
  int* const_cast_pointer{const_cast<int*>(pointer)};

  std::cout << "before modify const_cast_pointer: \n";
  std::cout << "original: " << original << std::endl;
  std::cout << "*const_cast_pointer: " << *const_cast_pointer << std::endl;

  // valid, cause the oringinal data original is not const.
  *const_cast_pointer = 20;

  std::cout << "after modify const_cast_pointer: \n";
  std::cout << "original: " << original << std::endl;
  std::cout << "*const_cast_pointer: " << *const_cast_pointer << std::endl;
}
}  // namespace playground::const_cast_example

int main(int argc, char** argv) {
  playground::const_cast_example::example1();
  playground::const_cast_example::example2();

  return 0;
}