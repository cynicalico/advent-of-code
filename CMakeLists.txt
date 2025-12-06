cmake_minimum_required(VERSION 3.20)
project(libaoc LANGUAGES CXX)

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
        URL https://github.com/boostorg/boost/releases/download/boost-1.89.0/boost-1.89.0-cmake.7z
        URL_HASH SHA256=252149f583054515b10688855b24ca1c16072b5118e603b8fe017894d319c262
        USES_TERMINAL_DOWNLOAD TRUE
        DOWNLOAD_NO_EXTRACT FALSE
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(boost)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr
        GIT_TAG 1.14.1
)
FetchContent_MakeAvailable(cpr)

add_library(libaoc)
target_compile_features(libaoc PRIVATE cxx_std_23)
target_sources(libaoc
        PRIVATE
        # [[[cog
        # import cog
        # import os
        #
        # for root, dirs, files in os.walk("solutions", topdown=True):
        #   dirs[:] = sorted(dirs, key=int) # sort dirs by year
        #   for f in sorted(files):
        #       if f.endswith(".cpp"):
        #           cog.outl(f"\"{os.path.join(root, f)}\"")
        # ]]]
        "solutions/2024/day01.cpp"
        "solutions/2025/day01.cpp"
        "solutions/2025/day02.cpp"
        "solutions/2025/day03.cpp"
        "solutions/2025/day04.cpp"
        "solutions/2025/day05.cpp"
        # [[[end]]]

        PUBLIC
        FILE_SET solution_headers
        TYPE HEADERS
        FILES
        # [[[cog
        # import cog
        # import os
        #
        # for root, dirs, files in os.walk("solutions", topdown=True):
        #   dirs[:] = sorted(dirs, key=int) # sort dirs by year
        #   for f in sorted(files):
        #       if f.endswith(".hpp"):
        #           cog.outl(f"\"{os.path.join(root, f)}\"")
        # ]]]
        "solutions/prototype_macro.hpp"
        "solutions/2024/prototypes.hpp"
        "solutions/2025/prototypes.hpp"
        # [[[end]]]

        PRIVATE
        # [[[cog
        # import cog
        # import os
        #
        # for root, dirs, files in os.walk("utils"):
        #   for f in sorted(files):
        #       if f.endswith(".cpp"):
        #           cog.outl(f"\"{os.path.join(root, f)}\"")
        # ]]]
        "utils/io.cpp"
        # [[[end]]]

        PUBLIC
        FILE_SET utils
        TYPE HEADERS
        FILES
        # [[[cog
        # import cog
        # import os
        #
        # for root, dirs, files in os.walk("utils"):
        #   for f in sorted(files):
        #       if f.endswith(".hpp"):
        #           cog.outl(f"\"{os.path.join(root, f)}\"")
        # ]]]
        "utils/grid.hpp"
        "utils/io.hpp"
        "utils/math.hpp"
        "utils/parse.hpp"
        "utils/print.hpp"
        "utils/sequence.hpp"
        "utils/std.hpp"
        "utils/utils.hpp"
        "utils/vec.hpp"
        # [[[end]]]

        PUBLIC
        FILE_SET thirdparty
        TYPE HEADERS
        FILES
        "thirdparty/argparse.hpp"
        "thirdparty/dotenv.h"
)

target_link_libraries(libaoc PUBLIC fmt::fmt ctre Boost::container_hash cpr::cpr)

add_executable(aoc
        aoc.cpp
        src/aoc_proxy.cpp
        src/aoc_proxy.hpp
        src/solution_map.cpp
        src/solution_map.hpp
)
target_compile_features(aoc PRIVATE cxx_std_23)
target_link_libraries(aoc PRIVATE libaoc)
