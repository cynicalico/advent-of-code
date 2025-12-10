cmake_minimum_required(VERSION 3.20)
project(libaoc LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 12.0.0
)
FetchContent_MakeAvailable(fmt)

set(CMAKE_CXX_STANDARD 23)

add_library(libaoc)
target_compile_features(libaoc PRIVATE cxx_std_23)
target_link_libraries(libaoc PUBLIC fmt::fmt)

add_executable(aoc)
target_compile_features(aoc PRIVATE cxx_std_23)
target_link_libraries(aoc PRIVATE libaoc)

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
