#include "replica/cpp-primer/chapter16/shared_ptr.h"

#include <gtest/gtest.h>

TEST(SharedPtr, Main) {
  int *p = new int(3);
  SharedPtr<int> sp(p);

  EXPECT_NE(sp.Get(), nullptr);
  EXPECT_EQ(*(sp.Get()), 3);
  EXPECT_EQ(sp.RefCnt(), 1);

  sp.Release();
  EXPECT_EQ(sp.Get(), nullptr);
}

TEST(SharedPtr, Copy) {
  int *p(new int(4));
  SharedPtr<int> sp1(p);

  EXPECT_EQ(sp1.RefCnt(), 1);

  SharedPtr<int> sp2(sp1);

  EXPECT_EQ(sp1.RefCnt(), 2);
  EXPECT_EQ(sp2.RefCnt(), 2);

  sp1.Release();

  EXPECT_EQ(sp1.Get(), nullptr);
  EXPECT_EQ(sp2.RefCnt(), 1);

  sp2.Release();

  EXPECT_EQ(sp2.Get(), nullptr);
}

TEST(SharedPtr, Deleter) {}

TEST(SharedPtr, MakeShared) {}