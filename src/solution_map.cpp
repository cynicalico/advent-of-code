#include "src/solution_map.hpp"

#include "solutions/prototypes.hpp"

// clang-format off
std::map<int, std::map<int, Solution>> solution_map() {
    return {
        /*[[[cog
        import cog
        import os
        import re
        from pathlib import Path

        for root, dirs, files in os.walk("solutions", topdown=True):
            dirs[:] = sorted(dirs, key=int) # sort dirs by year
            m = re.match(r"solutions/(\d+)", Path(root).as_posix())
            if m:
                year = m[1]
                cog.outl(f"{{{year}, {{")
                days = []
                for f in files:
                    m = re.match(r"day(\d+)\.cpp", Path(f).as_posix())
                    if m:
                        days.append(m[1])
                for day in sorted(days):
                    cog.outl(f"    {{{day}, AOC_NS({year}, {day})::solution()}},")
                cog.outl("}},")
        ]]]*/
        {2024, {
            {01, AOC_NS(2024, 01)::solution()},
            {02, AOC_NS(2024, 02)::solution()},
        }},
        {2025, {
            {01, AOC_NS(2025, 01)::solution()},
            {02, AOC_NS(2025, 02)::solution()},
            {03, AOC_NS(2025, 03)::solution()},
            {04, AOC_NS(2025, 04)::solution()},
            {05, AOC_NS(2025, 05)::solution()},
            {06, AOC_NS(2025, 06)::solution()},
            {07, AOC_NS(2025, 07)::solution()},
        }},
        //[[[end]]]
    };
}
// clang-format on
