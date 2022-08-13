cc_library(
  name = "test_files",
  srcs = [
    "is_char_unique.hh",
    "is_perm_of.hh",
    "url_ify.hh",
  ],
  deps = [
    "//common:utils",
  ],
)

cc_test(
  name = "runner",
  size = "small",
  srcs = ["test_runner.cc"],
  deps = [
    ":test_files",
    "@googletest//:gtest_main",
  ],
)