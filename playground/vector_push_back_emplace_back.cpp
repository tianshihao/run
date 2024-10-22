#include <algorithm>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>

struct Sample {
  Sample() noexcept { std::cout << "default constructor" << std::endl; }
  Sample(int const& a) noexcept : _a{a} {
    std::cout << "constructor" << std::endl;
  }
  Sample(Sample const& other) noexcept : _a{other._a} {
    std::cout << "copy constructor" << std::endl;
  }
  Sample(Sample&& other) noexcept : _a{std::move(other._a)} {
    std::cout << "move constructor" << std::endl;
  }

  int _a;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  std::vector<Sample> vec;

  std::cout << "Testing push_back int" << std::endl;
  vec.push_back(1);
  std::cout << std::endl;

  std::cout << "Testing emplace_back int" << std::endl;
  vec.emplace_back(1);
  std::cout << std::endl;

  Sample s{1};

  std::cout << "Testing push_back object" << std::endl;
  vec.push_back(s);
  std::cout << std::endl;

  std::cout << "Testing emplace_back object" << std::endl;
  vec.emplace_back(s);
  std::cout << std::endl;

  std::cout << "Testing push_back temporal object" << std::endl;
  vec.push_back(Sample{1});
  std::cout << std::endl;

  std::cout << "Tesing emplace_back temporal object" << std::endl;
  vec.emplace_back(Sample{1});
  std::cout << std::endl;

  return 0;
}
