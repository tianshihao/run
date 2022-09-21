#include <iostream>
#include <iterator>
#include <list>
#include <ostream>
#include <string>
#include <vector>

#include "blob.h"
#include "blob_ptr.h"

/********************************** Ex 16.4 **********************************/
template <typename Itertor, typename Value>
auto Find(Itertor first, Itertor last, Value const& val) {
  for (; first != last && *first != val; ++first) {
  }

  return first;
}

void TestEx_16_4() {
  std::vector<int> vct{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto is_in_vct{vct.cend() != Find(vct.cbegin(), vct.cend(), 5)};
  std::cout << (is_in_vct ? "found\n" : "not found\n");

  std::list<std::string> lst{"a", "b", "c", "d", "e", "f", "g"};
  auto is_in_lst{lst.cend() != Find(lst.cbegin(), lst.cend(), "z")};
  std::cout << (is_in_lst ? "found\n" : "not found\n");

  return;
}

void TestBlob() {
  Blob<int> chunk{1, 2, 6, 10, 12, 8};

  std::cout << chunk.Back() << std::endl;
  std::cout << chunk[4] << std::endl;

  return;
}

int main(int argc, char** argv) {
  TestBlob();
  return 0;
}
