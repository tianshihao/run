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
  std::cout << "a chunk of memory:\n";
  std::cout << chunk;

  std::cout << "the front of this chunk:\n";
  std::cout << chunk.Front() << std::endl;
  std::cout << "the back of this chunk:\n";
  std::cout << chunk.Back() << std::endl;
  std::cout << "the 4-index element of this chunk:\n";
  std::cout << chunk[4] << std::endl;

  std::cout << "construct chunk2 from chunk:\n";
  Blob<int> chunk2{chunk};

  if (chunk == chunk2) {
    std::cout << "chunk == chunk2\n";
  } else {
    std::cout << "chunk != chunk2\n";
  }

  std::cout << "push back 66:\n";
  chunk.PushBack(66);
  std::cout << chunk;

  std::cout << "get first element via BlobPtr:\n";
  std::cout << *(chunk.Begin()) << std::endl;
  std::cout << "get last element via BlobPtr:\n";
  std::cout << *(chunk.End()) << std::endl;

  return;
}

void TestBlobPtr() {
  Blob<int> chunk;
  for (int i{0}; i < 20; ++i) {
    chunk.PushBack(i);
  }
  std::cout << "a chunk of memory:\n";
  std::cout << chunk;

  BlobPtr<int> p_chunk{chunk, 1};

  std::cout << "p_chunk point to 1-index and its value is: " << *p_chunk
            << std::endl;
  p_chunk += 5;
  std::cout << "p_chunk += 5 and value pointed to is: " << *p_chunk
            << std::endl;

  return;
}

void TestScreen() {
  Screen<10, 5> scrn{'e'};
  std::cout << scrn;
  std::cout << scrn.Get() << std::endl;

  return;
}

int main(int argc, char **argv) {
  TestBlob();
  // TestBlobPtr();
  // TestScreen();
  return 0;
}
