#include <iostream>
#include <memory>

class CustomDeleter {
 public:
  void operator()(int *ptr) const {
    std::cout << "CustomDeleter called, deleting pointer " << ptr << std::endl;
    delete ptr;
  }
};

template <typename T>
class CustomDeleterTemplate {
 public:
  void operator()(T *ptr) const {
    std::cout << "CustomDeleter called, deleting pointer " << ptr << std::endl;
    delete ptr;
  }
};

int main() {
  // Explicitly provide an instance of CustomDeleter
  std::unique_ptr<int, CustomDeleter> ptr1(new int(42), CustomDeleter());

  // Use the default constructor of CustomDeleter
  std::unique_ptr<int, CustomDeleter> ptr2(new int(42));

  std::cout << "ptr1: " << *ptr1 << std::endl;
  std::cout << "ptr2: " << *ptr2 << std::endl;

  std::shared_ptr<int> ptr3{new int(42), [](int *p) {
                              std::cout
                                  << "CustomDeleter called, deleting pointer "
                                  << p << std::endl;
                              delete p;
                            }};

  std::cout << "ptr3: " << *ptr3 << std::endl;

  std::unique_ptr<float, CustomDeleterTemplate<float>> ptr4(new float(42.0f));

  return 0;
}