#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
  std::vector<int> vec{1, 2, 3, 4, 5};

  std::for_each(vec.begin(), vec.end(), [](auto& i) { i *= 2; });
  std::for_each(vec.begin(), vec.end(),
                [](auto i) { std::cout << i << std::endl; });

  return 0;
}
