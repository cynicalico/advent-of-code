#include "argparse/argparse.hpp"
#include "utils/print.hpp"
#include <filesystem>
#include <functional>
#include <map>

struct Answer {
    std::string part1;
    std::string part2;
};

using Solution = std::function<Answer(const std::filesystem::path &)>;

std::map<const char *, std::map<const char *, Solution>> solution_map();

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("AoC Runner");

    argparse::ArgumentParser run_parser("run");

    program.add_subparser(run_parser);

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &e) {
        fmt::print(stderr, "Error: {}", e.what());
        return 1;
    }

    return 0;
}

// #define SOLUTION_MAIN(yyyy, dd, p1_ans_t, p2_ans_t)                                              \
//     int main(int, char *[]) {                                                                    \
//         using namespace std::chrono;                                                             \
//         using namespace aoc##yyyy::day##dd;                                                      \
//                                                                                                  \
//         auto p1_ans = UNPACK p1_ans_t();                                                         \
//         auto p2_ans = UNPACK p2_ans_t();                                                         \
//                                                                                                  \
//         auto start = steady_clock::now();                                                        \
//         try {                                                                                    \
//             auto input = parse_input_file();                                                     \
//             p1_ans = p1(input);                                                                  \
//             p2_ans = p2(input);                                                                  \
//         } catch (const std::runtime_error &e) {                                                  \
//             fmt::print("ERROR: {} \n", e.what());                                                \
//         }                                                                                        \
//         auto end = steady_clock::now();                                                          \
//                                                                                                  \
//         const auto elapsed = end - start;                                                        \
//         const auto elapsed_ns = duration_cast<nanoseconds>(elapsed);                             \
//                                                                                                  \
//         fmt::print(STRINGIZE(aoc## yyyy) "::" STRINGIZE(day## dd) "::p1: {}\n", p1_ans);           \
//         fmt::print(STRINGIZE(aoc## yyyy) "::" STRINGIZE(day## dd) "::p2: {}\n", p2_ans);           \
//         fmt::print("\nElapsed time: {:.06f}s\n", static_cast<double>(elapsed_ns.count()) / 1e9); \
//                                                                                                  \
//         return 0;                                                                                \
//     }

#define SOLUTION(yyyy, dd)                                             \
    [](const std::filesystem::path &input_path) -> Answer {            \
        using namespace aoc##yyyy::day##dd;                            \
        auto input = parse_input_file(input_path);                     \
        auto p1_ans = p1(input);                                       \
        auto p2_ans = p2(input);                                       \
        return {fmt::format("{}", p1_ans), fmt::format("{}", p2_ans)}; \
    }

// clang-format off
/*[[[cog
import cog
import os
import re

for root, dirs, files in os.walk("solutions", topdown=True):
    dirs[:] = sorted(dirs, key=int) # sort dirs by year
    for f in sorted(files, key=lambda p: re.match(r"day(\d+)\.hpp", p)[1]):
        cog.outl(f"#include \"{os.path.join(root, f)}\"")
]]]*/
#include "solutions/2025/day01.hpp"
#include "solutions/2025/day02.hpp"
#include "solutions/2025/day03.hpp"
#include "solutions/2025/day04.hpp"
#include "solutions/2025/day05.hpp"
//[[[end]]]

std::map<const char *, std::map<const char *, Solution>> solution_map() {
    return {
    /*[[[cog
    import cog
    import os
    import re

    for root, dirs, files in os.walk("solutions", topdown=True):
        dirs[:] = sorted(dirs, key=int) # sort dirs by year
        m = re.match(r"solutions/(\d+)", root)
        if m:
            year = m[1]
            cog.outl(f"{{\"{year}\", {{")
            days = []
            for f in files:
                m = re.match(r"day(\d+)\.hpp", f)
                if m:
                    days.append(m[1])
            for day in sorted(days):
                cog.outl(f"    {{\"{day}\", SOLUTION({year}, {day})}},")
            cog.outl("}},")
    ]]]*/
    {"2025", {
        {"01", SOLUTION(2025, 01)},
        {"02", SOLUTION(2025, 02)},
        {"03", SOLUTION(2025, 03)},
        {"04", SOLUTION(2025, 04)},
        {"05", SOLUTION(2025, 05)},
    }},
    //[[[end]]]
    };
}
// clang-format on
