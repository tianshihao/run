#include <iostream>

#include "blob.h"

int TestBlob(int argc, char** argv) {
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

  return 0;
}
