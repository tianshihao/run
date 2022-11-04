#include "replica/cpp-primer/chapter16/unique_ptr.h"

#include <gtest/gtest.h>

TEST(UniquePtr, Base) {
  UniquePtr<int> up1;
  EXPECT_EQ(up1.Bool(), false);

  int* p{new int(7)};
  up1.Reset(p);
  EXPECT_EQ(up1.Bool(), true);

  EXPECT_EQ(*up1, 7);
  EXPECT_EQ(*(up1.Get()), 7);

  UniquePtr<int> up2(new int(-43));
  EXPECT_EQ(*up2, -43);

  up2.Swap(up1);
  EXPECT_EQ(*up1, -43);
  EXPECT_EQ(*up2, 7);

  up2.Release();
  EXPECT_EQ(up2.Bool(), false);
  EXPECT_EQ(up2.Get(), nullptr);

  up2.Swap(up1);
  EXPECT_EQ(up1.Bool(), false);
  EXPECT_EQ(up1.Get(), nullptr);
  EXPECT_EQ(up2.Bool(), true);
  EXPECT_NE(up2.Get(), nullptr);
  EXPECT_EQ(*up2, -43);
}
