#pragma once

#include "solutions/prototype_macro.hpp"
#include "utils/utils.hpp"
#include <cstdint>
#include <tuple>
#include <utility>
#include <vector>

AOC_NAMESPACE(2025, 01) {
SOLUTION_PROTOTYPES((std::vector<int>), (int), (int))
}

AOC_NAMESPACE(2025, 02) {
using Range = std::tuple<std::uint64_t, std::uint64_t>;
SOLUTION_PROTOTYPES((std::vector<Range>), (std::uint64_t), (std::uint64_t))
}

AOC_NAMESPACE(2025, 03) {
using Joltage = std::uint64_t;
using BatteryBank = std::vector<Joltage>;
SOLUTION_PROTOTYPES((std::vector<BatteryBank>), (Joltage), (Joltage))
}

AOC_NAMESPACE(2025, 04) {
using Grid = utils::Grid2D<std::int32_t>;
using Pos = utils::Vec2<std::int32_t>;
SOLUTION_PROTOTYPES((Grid), (std::uint32_t), (std::uint32_t))
}

AOC_NAMESPACE(2025, 05) {
using Range = utils::Interval<std::uint64_t>;
using Input = std::pair<std::vector<Range>, std::vector<std::uint64_t>>;
SOLUTION_PROTOTYPES((Input), (std::size_t), (std::size_t))
}

AOC_NAMESPACE(2025, 06) {
SOLUTION_PROTOTYPES((std::vector<std::string>), (std::uint64_t), (std::uint64_t))
}

AOC_NAMESPACE(2025, 07) {
using Manifold = utils::Grid2D<std::uint8_t>;
using Pos = utils::Vec2<std::size_t>;
SOLUTION_PROTOTYPES((std::pair<std::uint32_t, std::uint64_t>), (std::uint32_t), (std::uint64_t))
}
