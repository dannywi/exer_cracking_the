cc_library(
    name = "test_files",
    srcs = glob(["*.hh"]),
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
