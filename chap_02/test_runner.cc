#include <gtest/gtest.h>

#include "kth_last.hh"
#include "ll_rm_dup.hh"

TEST(linked_list_rm_dup, BasicAssertions) {
  using list_t = linked_list<int>;
  using list_ptr_t = list_t::ptr_t;
  using vec_t = std::vector<int>;
  // tuple of input, expected output
  std::vector<std::tuple<vec_t, vec_t>> test_suite{
      { {1, 2, 3, 4, 5, 6, 7, 7, 8, 3, 2, 9, 2, 3, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9} },
      { {5, 5, 5, 5, 5, 5}, {5} },
      { {3, 3, 3, 1}, {3, 1} },
      { {2}, {2} },
      { {}, {} },
  };

  std::vector<std::function<void(list_ptr_t)>> impls{ll_rm_dup1<int>, ll_rm_dup2<int>};

  for (auto ts : test_suite) {
    for (auto impl : impls) {
      list_ptr_t root = list_t::from_vector(get<0>(ts));
      impl(root);
      auto result = list_t::to_vector(root);
      EXPECT_EQ(result, get<1>(ts));
    }
  }
}

TEST(kth_last, BasicAssertions) {
  using list_t = linked_list<char>;
  using list_ptr_t = list_t::ptr_t;
  using vec_t = std::vector<char>;
  // tuple of input vector, k, expected output
  std::vector<std::tuple<vec_t, size_t, char>> test_suite{
      { {'a', 'b', 'c', 'd'}, 2, 'c' },
      { {'a', 'b', 'c', 'd'}, 4, 'a' },
      { {'a', 'b', 'c', 'd'}, 1, 'd' },
      { {'z'}, 1, 'z' },
  };

  std::vector<std::function<char(list_ptr_t, size_t)>> impls{kth_last1<char>, kth_last2<char>};

  for (auto impl : impls) {
    for (auto ts : test_suite) {
      EXPECT_EQ(impl(list_t::from_vector(get<0>(ts)), get<1>(ts)), get<2>(ts));
    }

    EXPECT_THROW(impl(list_t::from_vector({}), 0), std::logic_error);
    EXPECT_THROW(impl(list_t::from_vector({'a'}), 2), std::logic_error);
    EXPECT_THROW(impl(list_t::from_vector({'a'}), 0), std::logic_error);
  }
}