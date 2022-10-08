#include <iostream>
#include <iterator>
#include <list>
#include <ostream>
#include <string>
#include <vector>

#include "blob.h"
#include "blob_ptr.h"
#include "find.h"
#include "screen.h"

void TestFind() {
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

void TestBlobPtr() {
  Blob<int> blob;

  for (int i{0}; i < 20; ++i) {
    blob.PushBack(i);
    std::cout << i << std::endl;
  }

  BlobPtr<int> p_blob{blob, 1};

  std::cout << "BlobPtr point to " << *p_blob << std::endl;

  return;
}

void TestScreen() {
  Screen<10, 5> scrn{'e'};
  std::cout << scrn;
  std::cout << scrn.Get() << std::endl;

  return;
}

int main(int argc, char **argv) {
  // TestBlob();
  // TestBlobPtr();
  TestScreen();
  return 0;
}
