#pragma once

#include "solutions/prototype_macro.hpp"
#include "utils/utils.hpp"
#include <cstdint>
#include <vector>

AOC_NAMESPACE(2024, 01) {
using List = std::vector<std::int32_t>;
SOLUTION_PROTOTYPES((std::tuple<List, List>), (std::int32_t), (std::int32_t))
}

AOC_NAMESPACE(2024, 02) {
using Report = std::vector<std::int32_t>;
SOLUTION_PROTOTYPES((std::vector<Report>), (std::uint32_t), (std::uint32_t))
}
