#include "replica/cpp-primer/chapter16/find.h"

#include <gtest/gtest.h>

#include <list>
#include <string>
#include <vector>

TEST(FindTest, Main) {
  std::vector<int> vct{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto is_in_vct{vct.cend() != Find(vct.cbegin(), vct.cend(), 5)};
  EXPECT_EQ(is_in_vct, true);

  std::list<std::string> lst{"a", "b", "c", "d", "e", "f", "g"};
  auto is_in_lst{lst.cend() != Find(lst.cbegin(), lst.cend(), "z")};
  EXPECT_EQ(is_in_lst, false);
}
