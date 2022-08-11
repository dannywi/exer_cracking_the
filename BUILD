cc_library(
  name = "tests",
  srcs = [
    "is_char_unique.hh",
    "is_perm_of.hh",
    "url_ify.hh",
    "utils.hh",
  ]
)

cc_test(
  name = "runner",
  size = "small",
  srcs = ["test_runner.cc"],
  deps = [
    ":tests",
    "@googletest//:gtest_main",
    ],
)