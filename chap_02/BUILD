cc_library(
    name = "linked_list",
    srcs = [
        "linked_list.hh",
    ],
)

cc_library(
    name = "test_files",
    srcs = [
        "kth_last.hh",
        "ll_rm_dup.hh",
    ],
    deps = [
        "linked_list",
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
