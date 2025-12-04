cmake_minimum_required(VERSION 3.20)
project(aoc2025 LANGUAGES CXX)

include(FetchContent)

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
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.89.0
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(boost)

add_library(aoc2025)
target_compile_features(aoc2025 PRIVATE cxx_std_23)
target_sources(aoc2025
        PRIVATE
        "utils/io.cpp"
        "utils/math.cpp"

        PUBLIC
        FILE_SET HEADERS
        FILES
        "utils/base.hpp"
        "utils/io.hpp"
        "utils/math.hpp"
        "utils/parse.hpp"
        "utils/print.hpp"
        "utils/sequence.hpp"
        "utils/std.hpp"
        "utils/vec.hpp"
)

target_link_libraries(aoc2025 PUBLIC fmt::fmt ctre Boost::container_hash)

add_executable(day01 solutions/day01.cpp)
target_compile_features(day01 PRIVATE cxx_std_23)
target_link_libraries(day01 PRIVATE aoc2025)

add_executable(day02 solutions/day02.cpp)
target_compile_features(day02 PRIVATE cxx_std_23)
target_link_libraries(day02 PRIVATE aoc2025)

add_executable(day03 solutions/day03.cpp)
target_compile_features(day03 PRIVATE cxx_std_23)
target_link_libraries(day03 PRIVATE aoc2025)

add_executable(day04 solutions/day04.cpp)
target_compile_features(day04 PRIVATE cxx_std_23)
target_link_libraries(day04 PRIVATE aoc2025)
