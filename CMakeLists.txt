cmake_minimum_required(VERSION 3.20)
project(aoc LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse
        GIT_TAG v3.2
)
FetchContent_MakeAvailable(argparse)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.0.0
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
        compile-time-regular-expressions
        GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions
        GIT_TAG v3.10.0
)
FetchContent_MakeAvailable(compile-time-regular-expressions)

set(BOOST_INCLUDE_LIBRARIES container_hash)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
        boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.89.0/boost-1.89.0-cmake.7z
        URL_HASH SHA256=252149f583054515b10688855b24ca1c16072b5118e603b8fe017894d319c262
        USES_TERMINAL_DOWNLOAD TRUE
        DOWNLOAD_NO_EXTRACT FALSE
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(boost)

add_library(aoc)
target_compile_features(aoc PRIVATE cxx_std_23)
target_sources(aoc
        PRIVATE
        "utils/io.cpp"

        PUBLIC
        FILE_SET utils
        TYPE HEADERS
        FILES
        "utils/base.hpp"
        "utils/grid.hpp"
        "utils/io.hpp"
        "utils/math.hpp"
        "utils/parse.hpp"
        "utils/print.hpp"
        "utils/sequence.hpp"
        "utils/std.hpp"
        "utils/vec.hpp"

        PRIVATE
        FILE_SET solution_headers
        TYPE HEADERS
        FILES
        # [[[cog
        # import cog
        # import os
        # import re
        #
        # def extract_day(p):
        #   return re.match(r"day(\d+)\.hpp", p)[1]
        #
        # for root, dirs, files in os.walk("solutions", topdown=True):
        #   dirs[:] = sorted(dirs, key=int) # sort dirs by year
        #   for f in sorted(files, key=extract_day):
        #       cog.outl(f"\"{os.path.join(root, f)}\"")
        # ]]]
        "solutions/2025/day01.hpp"
        "solutions/2025/day02.hpp"
        "solutions/2025/day03.hpp"
        "solutions/2025/day04.hpp"
        "solutions/2025/day05.hpp"
        # [[[end]]]
)

target_link_libraries(aoc PUBLIC argparse::argparse fmt::fmt ctre Boost::container_hash)

add_executable(runner runner.cpp)
target_compile_features(runner PRIVATE cxx_std_23)
target_link_libraries(runner PRIVATE aoc)
