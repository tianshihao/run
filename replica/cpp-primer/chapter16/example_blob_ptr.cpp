#include <iostream>

#include "blob.h"

int TestBlobPtr(int argc, char** argv) {
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

  return 0;
}