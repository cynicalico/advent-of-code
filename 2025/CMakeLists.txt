cmake_minimum_required(VERSION 3.20)
project(aoc2025 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.0.0
)
FetchContent_MakeAvailable(fmt)

add_library(aoc2025)
target_compile_features(aoc2025 PRIVATE cxx_std_23)
target_sources(aoc2025
        PRIVATE
        "helpers/io.cpp"
        "helpers/math.cpp"

        PUBLIC
        FILE_SET HEADERS
        FILES
        "helpers/base.hpp"
        "helpers/io.hpp"
        "helpers/math.hpp"
        "helpers/print.hpp"
        "helpers/std.hpp"
)

add_executable(day1 solutions/day1.cpp)
target_compile_features(day1 PRIVATE cxx_std_23)
target_link_libraries(day1 PRIVATE aoc2025 fmt::fmt)
