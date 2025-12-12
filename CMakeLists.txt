cmake_minimum_required(VERSION 3.21)
project(libaoc LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin)
endforeach()

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_library(libaoc)
add_library(libaoc::libaoc ALIAS libaoc)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.0.0
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
        z3
        GIT_REPOSITORY https://github.com/Z3Prover/z3.git
        GIT_TAG z3-4.15.4
)
FetchContent_MakeAvailable(z3)
if(TARGET libz3)
    target_include_directories(libz3 INTERFACE $<BUILD_INTERFACE:${z3_SOURCE_DIR}/src/api/c++>)
endif()
if(NOT TARGET z3::libz3)
    add_library(z3::libz3 ALIAS libz3)
endif()

find_package(OpenMP REQUIRED)
if(MSVC)
    target_compile_options(libaoc PRIVATE "/openmp:llvm /openmp:experimental")
endif()

target_compile_features(libaoc PRIVATE cxx_std_23)
if(MSVC)
    target_compile_options(libaoc PRIVATE "-Wno-c++98-compat")
endif()
target_link_libraries(libaoc PUBLIC fmt::fmt OpenMP::OpenMP_CXX z3::libz3)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(libaoc PRIVATE LIBAOC_EXPORTS)
    if(NOT WIN32)
        set_target_properties(libaoc PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
    endif()
endif()

add_executable(aoc)
target_compile_features(aoc PRIVATE cxx_std_23)
target_link_libraries(aoc PRIVATE libaoc::libaoc)

if(WIN32)
    add_custom_command(TARGET aoc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:aoc>
        $<TARGET_FILE_DIR:aoc>
        COMMAND_EXPAND_LISTS
        COMMENT "Copying runtime DLLs to output directory"
    )
endif()

##################################################
# EVERYTHING BELOW HERE IS GLOBBED AUTOMATICALLY #
#           TO UPDATE, RUN `just cog`            #
##################################################

target_sources(libaoc
        PRIVATE
        # [[[cog
        # import cog
        # import os
        # from pathlib import Path
        #
        # for root, dirs, files in os.walk("solutions", topdown=True):
        #     dirs[:] = sorted(dirs, key=int) # sort dirs by year
        #     for f in sorted(files):
        #         if f.endswith(".cpp"):
        #             cog.outl(f"\"{Path(os.path.join(root, f)).as_posix()}\"")
        # ]]]
        "solutions/2015/day01.cpp"
        "solutions/2015/day02.cpp"
        "solutions/2024/day01.cpp"
        "solutions/2024/day02.cpp"
        "solutions/2025/day01.cpp"
        "solutions/2025/day02.cpp"
        "solutions/2025/day03.cpp"
        "solutions/2025/day04.cpp"
        "solutions/2025/day05.cpp"
        "solutions/2025/day06.cpp"
        "solutions/2025/day07.cpp"
        "solutions/2025/day08.cpp"
        "solutions/2025/day09.cpp"
        "solutions/2025/day10.cpp"
        "solutions/2025/day11.cpp"
        # [[[end]]]

        PUBLIC
        FILE_SET solution_headers
        TYPE HEADERS
        FILES
        # [[[cog
        # import cog
        # import os
        # from pathlib import Path
        #
        # for root, dirs, files in os.walk("solutions", topdown=True):
        #     dirs[:] = sorted(dirs, key=int) # sort dirs by year
        #     for f in sorted(files):
        #         if f.endswith(".hpp"):
        #             cog.outl(f"\"{Path(os.path.join(root, f)).as_posix()}\"")
        # ]]]
        "solutions/export_macro.hpp"
        "solutions/prototype_macro.hpp"
        "solutions/prototypes.hpp"
        # [[[end]]]

        PRIVATE
        # [[[cog
        # import cog
        # import os
        # from pathlib import Path
        #
        # for root, dirs, files in os.walk("utils"):
        #     for f in sorted(files):
        #         if f.endswith(".cpp"):
        #             cog.outl(f"\"{Path(os.path.join(root, f)).as_posix()}\"")
        # ]]]
        "utils/io.cpp"
        "utils/split.cpp"
        # [[[end]]]

        PUBLIC
        FILE_SET utils_headers
        TYPE HEADERS
        FILES
        # [[[cog
        # import cog
        # import os
        # from pathlib import Path
        #
        # for root, dirs, files in os.walk("utils"):
        #     for f in sorted(files):
        #         if f.endswith(".hpp"):
        #             cog.outl(f"\"{Path(os.path.join(root, f)).as_posix()}\"")
        # ]]]
        "utils/grid.hpp"
        "utils/io.hpp"
        "utils/math.hpp"
        "utils/parse.hpp"
        "utils/print.hpp"
        "utils/priority_queue.hpp"
        "utils/sequence.hpp"
        "utils/split.hpp"
        "utils/std.hpp"
        "utils/utils.hpp"
        "utils/vec.hpp"
        # [[[end]]]

        PRIVATE
        # [[[cog
        # import cog
        # import os
        # from pathlib import Path
        #
        # for root, dirs, files in os.walk("thirdparty"):
        #     for f in sorted(files):
        #         if f.endswith(".cpp"):
        #             cog.outl(f"\"{Path(os.path.join(root, f)).as_posix()}\"")
        # ]]]
        # [[[end]]]

        PUBLIC
        FILE_SET thirdparty
        TYPE HEADERS
        BASE_DIRS thirdparty
        FILES
        # [[[cog
        # import cog
        # import os
        # from pathlib import Path
        #
        # for root, dirs, files in os.walk("thirdparty"):
        #     for f in sorted(files):
        #         if f.endswith(".hpp") or f.endswith(".h"):
        #             cog.outl(f"\"{Path(os.path.join(root, f)).as_posix()}\"")
        # ]]]
        "thirdparty/ctre.hpp"
        "thirdparty/hash_combine.hpp"
        "thirdparty/argparse/argparse.hpp"
        # [[[end]]]
)

target_sources(aoc
        PRIVATE
        # [[[cog
        # import cog
        # import os
        # from pathlib import Path
        #
        # for p in os.listdir("."):
        #     if os.path.isfile(p) and p.endswith(".cpp"):
        #         cog.outl(f"\"{Path(p).as_posix()}\"")
        # ]]]
        "aoc.cpp"
        # [[[end]]]

        # [[[cog
        # import cog
        # import os
        # from pathlib import Path
        #
        # for root, dirs, files in os.walk("src", topdown=True):
        #     for f in sorted(files):
        #         if f.endswith(".hpp") or f.endswith(".cpp"):
        #             cog.outl(f"\"{Path(os.path.join(root, f)).as_posix()}\"")
        # ]]]
        "src/solution_map.cpp"
        "src/solution_map.hpp"
        # [[[end]]]
)
