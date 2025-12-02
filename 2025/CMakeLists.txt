cmake_minimum_required(VERSION 3.20)
project(aoc2025 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.0.0
)
FetchContent_MakeAvailable(fmt)

add_executable(day1 day1.cpp)
target_compile_features(day1 PRIVATE cxx_std_23)
target_link_libraries(day1 PRIVATE fmt::fmt)
