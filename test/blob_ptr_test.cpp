#include "replica/cpp-primer/chapter16/blob_ptr.h"

#include <gtest/gtest.h>

TEST(BlobPtrTest, Main) {
  Blob<int> chunk;
  for (int i{0}; i < 20; ++i) {
    chunk.PushBack(i);
  }

  BlobPtr<int> p_chunk{chunk, 1};

  EXPECT_EQ(*p_chunk, 1);
  p_chunk += 5;
  EXPECT_EQ(*p_chunk, 6);
}