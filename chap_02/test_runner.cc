#include <gtest/gtest.h>

#include "ll_rm_dup.hh"

TEST(linked_list_rm_dup, BasicAssertions) {
  using list_t = linked_list<int>;
  using list_ptr_t = list_t::ptr_t;

  struct suite {
    using vec_t = std::vector<int>;
    vec_t inp;
    vec_t exp;
    suite(const vec_t& inp, const vec_t& exp) : inp(inp), exp(exp) {}
  };

  std::vector<suite> test_suite{
      suite({1, 2, 3, 4, 5, 6, 7, 7, 8, 3, 2, 9, 2, 3, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}),
      suite({5, 5, 5, 5, 5, 5}, {5}),
      suite({3, 3, 3, 1}, {3, 1}),
      suite({2}, {2}),
      suite({}, {}),
  };

  std::vector<std::function<void(list_ptr_t)>> impls{ll_rm_dup1<int>};

  for (auto ts : test_suite) {
    for (auto impl : impls) {
      list_ptr_t root = list_t::from_vector(ts.inp);
      impl(root);
      auto result = list_t::to_vector(root);
      EXPECT_EQ(result, ts.exp);
    }
  }
}