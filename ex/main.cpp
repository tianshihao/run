#include <algorithm>
#include <iostream>
#include <vector>

using ConstIterator = std::vector<int>::const_iterator;

int main() {
  ConstIterator ci;

  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};

  ci = vec.cbegin();
  std::cout << *ci << std::endl;
  ci = vec.cend() - 1;
  std::cout << *ci << std::endl;

  std::for_each(vec.cbegin(), vec.cbegin(),
                [](auto it) { std::cout << it << std::endl; });

  return 0;
}
