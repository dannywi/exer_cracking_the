#include <gtest/gtest.h>

#include <cstdlib>
#include <ctime>
#include <vector>

#include "binary_search.hh"

TEST(test, BasicAssertions) {
  std::vector<int> t{1, 2, 3, 7};
  EXPECT_TRUE(cr::binary_search(t.begin(), t.end(), 3));
  EXPECT_FALSE(cr::binary_search(t.begin(), t.end(), 5));
}
