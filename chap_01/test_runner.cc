#include <gtest/gtest.h>

#include <functional>
#include <string>
#include <vector>

#include "is_char_unique.hh"
#include "is_perm_of.hh"
#include "url_ify.hh"

TEST(HelloTest, BasicAssertions) {
  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}

TEST(is_char_unique, BasicAssertions) {
  EXPECT_EQ(is_char_unique(""), true);
  EXPECT_EQ(is_char_unique("abcdefg"), true);
  EXPECT_EQ(is_char_unique("1 23abc"), true);
  EXPECT_EQ(is_char_unique("aa"), false);
  EXPECT_EQ(is_char_unique("a  "), false);
}

TEST(is_perm_of, BasicAssertions) {
  EXPECT_EQ(is_perm_of("", ""), true);
  EXPECT_EQ(is_perm_of("abc", "bac"), true);
  EXPECT_EQ(is_perm_of("1 23abc", "123 abc"), true);
  EXPECT_EQ(is_perm_of("zzz", "zzz"), true);
  EXPECT_EQ(is_perm_of("a  1 2", "1a2   "), true);

  EXPECT_EQ(is_perm_of("a  1 2", "1a2  "), false);
  EXPECT_EQ(is_perm_of("aaa", "aab"), false);
  EXPECT_EQ(is_perm_of("aaa", "aaa "), false);
  EXPECT_EQ(is_perm_of("ccc  ", "ccc"), false);
  EXPECT_EQ(is_perm_of("abcd", "abde"), false);
}

TEST(url_ify, BasicAssertions) {
  struct test {
    test(const std::string &in, const std::string &expected, std::function<void(char *, size_t)> fn) {
      size_t space_cnt = count_if(in.begin(), in.end(), [](char c) { return c == ' '; }) * 2;

      size_t new_len = in.size() + space_cnt + 1;  // +1 for terminating null
      char buf[new_len];

      for (size_t i = 0; i < in.size(); ++i) {
        buf[i] = in[i];
      }

      for (size_t i = 0; i < space_cnt; ++i) {
        buf[in.size() + i] = ' ';
      }

      buf[new_len - 1] = '\0';
      fn(buf, new_len);
      EXPECT_STREQ(buf, expected.c_str());
    }
  };

  // cannot repeat inside functions as they do modify the param
  std::vector<std::function<void(char *, size_t)>> funcs{
      url_ify1,
      url_ify2,
      url_ify3,
  };

  for_each(funcs.begin(), funcs.end(), [](auto fn) {
    test("ab cd", "ab%20cd", fn);
    test("Forward The Foundation", "Forward%20The%20Foundation", fn);
    test("Childhood's End", "Childhood's%20End", fn);
    test("  With Spaces At Start", "%20%20With%20Spaces%20At%20Start", fn);
  });
}