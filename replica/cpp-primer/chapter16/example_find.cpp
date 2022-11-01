#include <iostream>
#include <list>
#include <vector>

#include "find.h"

int TestFind(int argc, char **argv) {
  std::vector<int> vct{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto is_in_vct{vct.cend() != Find(vct.cbegin(), vct.cend(), 5)};
  std::cout << (is_in_vct ? "found\n" : "not found\n");

  std::list<std::string> lst{"a", "b", "c", "d", "e", "f", "g"};
  auto is_in_lst{lst.cend() != Find(lst.cbegin(), lst.cend(), "z")};
  std::cout << (is_in_lst ? "found\n" : "not found\n");

  return 0;
}
