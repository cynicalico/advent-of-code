#include "src/solution_map.hpp"

#include "solutions/2024/prototypes.hpp"
#include "solutions/2025/prototypes.hpp"

#define SOLUTION(yyyy, dd)                                                                \
    [](const std::filesystem::path &input_path) -> std::tuple<std::string, std::string> { \
        using AOC_NAMESPACE(yyyy, dd);                                                    \
        auto input = parse_input_file(input_path);                                        \
        auto p1_ans = p1(input);                                                          \
        auto p2_ans = p2(input);                                                          \
        return {fmt::format("{}", p1_ans), fmt::format("{}", p2_ans)};                    \
    }

// clang-format off
std::map<int, std::map<int, Solution>> solution_map() {
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
                cog.outl(f"{{{year}, {{")
                days = []
                for f in files:
                    m = re.match(r"day(\d+)\.cpp", f)
                    if m:
                        days.append(m[1])
                for day in sorted(days):
                    cog.outl(f"    {{{day}, SOLUTION({year}, {day})}},")
                cog.outl("}},")
        ]]]*/
        {2024, {
            {01, SOLUTION(2024, 01)},
        }},
        {2025, {
            {01, SOLUTION(2025, 01)},
            {02, SOLUTION(2025, 02)},
            {03, SOLUTION(2025, 03)},
            {04, SOLUTION(2025, 04)},
            {05, SOLUTION(2025, 05)},
        }},
        //[[[end]]]
        };
}
// clang-format on
