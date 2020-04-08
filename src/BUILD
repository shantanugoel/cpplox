load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "token",
    srcs = [],
    hdrs = [
        "token.h",
        "token_type.h",
    ],
)

cc_library(
    name = "lox",
    srcs = ["lox.cc"],
    hdrs = ["lox.h"],
    deps = [
        "token",
    ],
)

cc_binary(
    name = "cpplox",
    srcs = ["main.cc"],
    deps = [
        ":lox",
    ],
)
