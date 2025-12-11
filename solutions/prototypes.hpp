#pragma once

#include "solutions/prototype_macro.hpp"

/*[[[cog
import cog
import os
import re
from pathlib import Path

first = True
for root, dirs, files in os.walk("solutions", topdown=True):
    dirs[:] = sorted(dirs, key=int) # sort dirs by year
    m = re.match(r"solutions/(\d+)", Path(root).as_posix())
    if m:
        if not first:
            cog.outl()
        first = False
        year = m[1]
        days = []
        for f in files:
            m = re.match(r"day(\d+)\.cpp", Path(f).as_posix())
            if m:
                days.append(m[1])
        for day in sorted(days):
            cog.outl(f"SOLUTION_PROTOTYPE({int(year)}, {int(day)})")
]]]*/
SOLUTION_PROTOTYPE(2024, 1)
SOLUTION_PROTOTYPE(2024, 2)

SOLUTION_PROTOTYPE(2025, 1)
SOLUTION_PROTOTYPE(2025, 2)
SOLUTION_PROTOTYPE(2025, 3)
SOLUTION_PROTOTYPE(2025, 4)
SOLUTION_PROTOTYPE(2025, 5)
SOLUTION_PROTOTYPE(2025, 6)
SOLUTION_PROTOTYPE(2025, 7)
SOLUTION_PROTOTYPE(2025, 8)
SOLUTION_PROTOTYPE(2025, 9)
SOLUTION_PROTOTYPE(2025, 10)
SOLUTION_PROTOTYPE(2025, 11)
//[[[end]]]
