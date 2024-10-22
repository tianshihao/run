#include <algorithm>  // for std::any_of
#include <array>
#include <atomic>
#include <iostream>
#include <string>
#include <vector>

#define GOOGLE_ARRAYSIZE(a)     \
  ((sizeof(a) / sizeof(*(a))) / \
   static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

// singleton
class Singleton {
 public:
  static Singleton& getInstance() {
    static Singleton instance;
    return instance;
  }

  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  std::string SetName() {
    // Get the input from the user
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    return name;
  }

 private:
  Singleton() = default;
};

// static const std::string name{Singleton::getInstance().SetName()};

int main() {
  // std::array<int, 5> arr = {1, 2, 3, 4, 5};
  // std::cout << "Array size: " << GOOGLE_ARRAYSIZE(arr) << std::endl;

  // define a c style array
  // int arr[] = {1, 2, 3, 4, 5};
  // double* arr{new double[1]{3.}};
  double* arr;
  std::cout << "Array size: " << GOOGLE_ARRAYSIZE(arr) << std::endl;
  std::cout << "sizeof(arr): " << sizeof(arr) << std::endl;
  std::cout << "sizeof(*(arr)): " << sizeof(*(arr)) << std::endl;
  std::cout << "sizeof(arr) / sizeof(*(arr)): " << sizeof(arr) / sizeof(*(arr))
            << std::endl;
  std::cout << "!(sizeof(arr) % sizeof(*(arr))): "
            << !(sizeof(arr) % sizeof(*(arr))) << std::endl;

  return 0;
}