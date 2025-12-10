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
                    cog.outl(f"    {{{int(day)}, AOC_NS({int(year)}, {int(day)})::solution()}},")
                cog.outl("}},")
        ]]]*/
        {2024, {
            {1, AOC_NS(2024, 1)::solution()},
            {2, AOC_NS(2024, 2)::solution()},
        }},
        {2025, {
            {1, AOC_NS(2025, 1)::solution()},
            {2, AOC_NS(2025, 2)::solution()},
            {3, AOC_NS(2025, 3)::solution()},
            {4, AOC_NS(2025, 4)::solution()},
            {5, AOC_NS(2025, 5)::solution()},
            {6, AOC_NS(2025, 6)::solution()},
            {7, AOC_NS(2025, 7)::solution()},
        }},
        //[[[end]]]
    };
}
// clang-format on
