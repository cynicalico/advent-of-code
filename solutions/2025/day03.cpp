/* Day 3: Lobby
 * https://adventofcode.com/2025/day/3
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

using Joltage = std::uint64_t;
using BatteryBank = std::vector<Joltage>;

SOLUTION(2025, 03, (std::vector<BatteryBank>), (Joltage), (Joltage))

std::vector<BatteryBank> AOC_NS(2025, 03)::parse_input(const std::filesystem::path &input_path) {
    // clang-format off
    return utils::iter_file_lines(input_path) |
           std::views::transform([](const auto &line) {
               return line | std::views::transform([](const char c) { return c - '0'; }) |
                             std::ranges::to<BatteryBank>();
           }) |
           std::ranges::to<std::vector>();
    // clang-format on
}

namespace aoc2025::day03 {
Joltage find_max_joltage(const BatteryBank &bank, const std::size_t battery_count) {
    Joltage max_joltage = 0;
    std::size_t search_start = 0;
    for (std::size_t i = 0; i < battery_count; ++i) {
        Joltage max_idx = search_start;
        for (std::size_t j = search_start + 1; j < bank.size() - (battery_count - (i + 1)); ++j)
            if (bank[j] > bank[max_idx]) max_idx = j;
        max_joltage = max_joltage * 10 + bank[max_idx];
        search_start = max_idx + 1;
    }
    return max_joltage;
}
} // namespace aoc2025::day03

Joltage AOC_NS(2025, 03)::p1(std::vector<BatteryBank> &input) {
    const auto max_joltages = input | std::views::transform([](const auto &bank) { return find_max_joltage(bank, 2); });
    return std::ranges::fold_left(max_joltages, 0, std::plus{});
}

Joltage AOC_NS(2025, 03)::p2(std::vector<BatteryBank> &input) {
    const auto max_joltages =
            input | std::views::transform([](const auto &bank) { return find_max_joltage(bank, 12); });
    return std::ranges::fold_left(max_joltages, 0, std::plus{});
}
