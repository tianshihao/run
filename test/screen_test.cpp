#include "replica/cpp-primer/chapter16/screen.h"

#include <gtest/gtest.h>

TEST(ScreenTest, Main) {
  int const width{10}, height{5};
  Screen<width, height> scrn{'e'};

  scrn.Move(4, 7);
  EXPECT_EQ(scrn.GetCursor(), 47);

  scrn.Set('x');
  EXPECT_EQ('e', scrn.Get());

  scrn.Set(1, 3, 'y');
}