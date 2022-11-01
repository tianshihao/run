#include "replica/cpp-primer/chapter16/vec.h"

#include <gtest/gtest.h>

TEST(VecTest, Main) {
  Vec<int> vec{1, 2, 3, 4, 5};

  EXPECT_EQ(5, vec.Size());
  EXPECT_EQ(5, vec.Capacity());
  vec.Reserve(10);
  EXPECT_EQ(5, vec.Size());
  EXPECT_EQ(10, vec.Capacity());

  EXPECT_EQ(1, *(vec.Begin()));
  EXPECT_EQ(5, vec.At(4));

  vec.Resize(4);
  EXPECT_EQ(4, vec.Size());
  EXPECT_EQ(10, vec.Capacity());
  vec.Reserve(3);
  EXPECT_EQ(4, vec.Size());
  EXPECT_EQ(10, vec.Capacity());
}