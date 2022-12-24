cc_library(
    name = "test_files",
    srcs = ["queue_with_stacks.hh"],
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
