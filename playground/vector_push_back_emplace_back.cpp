#include <algorithm>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>

struct Sample {
  Sample() noexcept { std::cout << "default ctor" << std::endl; }
  Sample(int a) noexcept : _a{a} { std::cout << "ctor" << std::endl; }
  Sample(Sample const& other) noexcept : _a{other._a} {
    std::cout << "copy ctor" << std::endl;
  }
  Sample(Sample&& other) noexcept : _a{std::move(other._a)} {
    std::cout << "move ctor" << std::endl;
  }

  int _a;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  std::vector<Sample> vec;

  std::cout << "push_back int" << std::endl;
  vec.push_back(1);
  // vec.emplace(Sample{1});
  std::cout << "emplace_back int" << std::endl;
  vec.emplace_back(1);

  Sample s{1};

  std::cout << "push_back obj" << std::endl;
  vec.push_back(s);

  std::cout << "emplace_back obj" << std::endl;
  vec.emplace_back(s);

  std::cout << "push_back temp obj" << std::endl;
  vec.push_back(Sample{1});
  std::cout << "emplace_back temp obj" << std::endl;
  vec.emplace_back(Sample{1});

  return 0;
}
