/* Day 3: Lobby
 * https://adventofcode.com/2025/day/3
 */

#include "utils/base.hpp"

using Joltage = std::uint64_t;
using BatteryBank = std::vector<Joltage>;

SOLUTION(2025, 03, (std::vector<BatteryBank>), (Joltage), (Joltage))

std::vector<BatteryBank> aoc2025::day03::parse_input_file() {
    // clang-format off
    return utils::iter_file_lines(INPUT_FILENAME)
        | std::views::transform([](const auto &line) {
            return line | std::views::transform([](const char c) { return c - '0'; }) | std::ranges::to<BatteryBank>();
        })
        | std::ranges::to<std::vector>();
    // clang-format on
}

Joltage max_joltage(const BatteryBank &bank, const std::size_t battery_count) {
    Joltage acc = 0;
    std::size_t search_start = 0;
    for (std::size_t i = 0; i < battery_count; ++i) {
        Joltage max_idx = search_start;
        for (std::size_t j = search_start + 1; j < bank.size() - (battery_count - (i + 1)); ++j)
            if (bank[j] > bank[max_idx]) max_idx = j;
        acc = acc * 10 + bank[max_idx];
        search_start = max_idx + 1;
    }
    return acc;
}

Joltage aoc2025::day03::p1(const std::vector<BatteryBank> &input) {
    const auto max_joltages = input | std::views::transform([](const auto &bank) { return max_joltage(bank, 2); });
    return std::ranges::fold_left(max_joltages, 0, std::plus{});
}

Joltage aoc2025::day03::p2(const std::vector<BatteryBank> &input) {
    const auto max_joltages = input | std::views::transform([](const auto &bank) { return max_joltage(bank, 12); });
    return std::ranges::fold_left(max_joltages, 0, std::plus{});
}
