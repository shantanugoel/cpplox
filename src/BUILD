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
        "ast",
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
    name = "generate_ast",
    outs = ["expr.h"],
    cmd = "./$(location :ast_generator) > $@",
    tools = [":ast_generator"],
)

cc_library(
    name = "ast",
    hdrs = [":generate_ast"],
    deps = [
        ":token",
    ],
)

cc_binary(
    name = "ast_printer",
    srcs = ["ast_printer.cc"],
    includes = ["."],
    deps = [
        ":ast",
    ],
)
