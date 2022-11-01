#include "replica/cpp-primer/chapter16/blob.h"

#include <gtest/gtest.h>

TEST(BlobTest, Main) {
  Blob<int> chunk{1, 2, 6, 10, 12, 8};

  EXPECT_EQ(chunk.Front(), 1);
  EXPECT_EQ(chunk.Back(), 8);
  EXPECT_EQ(chunk[4], 12);

  Blob<int> chunk2{chunk};

  EXPECT_EQ(chunk == chunk2, true);

  chunk.PushBack(66);

  EXPECT_EQ(1, *(chunk.Begin()));
  EXPECT_EQ(66, *(chunk.End()));
}