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
    name = "scanner",
    srcs = ["scanner.cc"],
    hdrs = ["scanner.h"],
    deps = [
        "logger",
        "token",
    ],
)

cc_library(
    name = "logger",
    srcs = ["logger.cc"],
    hdrs = ["logger.h"],
)

cc_library(
    name = "lox",
    srcs = ["lox.cc"],
    hdrs = ["lox.h"],
    deps = [
        "logger",
        "scanner",
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

cc_binary(
    name = "ast_generator",
    srcs = ["ast_generator.cc"],
    copts = ["-std=c++17"],
)

genrule(
    name = "ast",
    outs = ["Expr.h"],
    cmd = "./$(location :ast_generator) > $@",
    tools = [":ast_generator"],
)
