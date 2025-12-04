/* Day 4: Printing Department
 * https://adventofcode.com/2025/day/4
 */

#include "utils/base.hpp"

using Grid = aoc2025::utils::Grid2D<char>;
using Pos = aoc2025::utils::Vec2<std::int32_t>;

SOLUTION(2025, 04, (Grid), (std::uint32_t), (std::uint32_t))

Grid aoc2025::day04::parse_input_file() {
    // clang-format off
    return Grid{utils::iter_file_lines(INPUT_FILENAME)
            | std::views::transform([](const auto &line) { return line | std::ranges::to<std::vector>(); })
            | std::ranges::to<std::vector>()};
    // clang-format on
}

std::vector<Pos> get_adjacent_rolls(const Grid &input, const Pos &p) {
    // clang-format off
    return aoc2025::utils::moore_neighborhood_seq(p)
            | std::views::filter([&](const auto &op) { return input.in_bounds(op) && input[op] == '@'; })
            | std::ranges::to<std::vector>();
    // clang-format on
}

std::uint32_t aoc2025::day04::p1(Grid &input) {
    std::uint32_t ans = 0;
    for (const auto &p : utils::grid_seq<std::int32_t>(input))
        if (input[p] == '@' && get_adjacent_rolls(input, p).size() < 4) ans++;
    return ans;
}

std::uint32_t aoc2025::day04::p2(Grid &input) {
    std::vector<Pos> spaces_to_check;
    for (const auto &p : utils::grid_seq<std::int32_t>(input))
        if (input[p] == '@') spaces_to_check.emplace_back(p);

    std::uint32_t ans = 0;
    do {
        std::vector<Pos> buf;
        for (const auto &p : spaces_to_check) {
            if (input[p] != '@') continue;
            if (const auto adjacent_rolls = get_adjacent_rolls(input, p); adjacent_rolls.size() < 4) {
                ans++;
                input[p] = '.';
                buf.append_range(adjacent_rolls);
            }
        }
        std::swap(spaces_to_check, buf);
    } while (!spaces_to_check.empty());
    return ans;
}
