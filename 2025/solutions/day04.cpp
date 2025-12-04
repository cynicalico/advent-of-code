/* Day 4: Printing Department
 * https://adventofcode.com/2025/day/4
 */

#include "utils/base.hpp"

SOLUTION(2025, 04, (std::vector<std::string>), (std::uint32_t), (std::uint32_t))

std::vector<std::string> aoc2025::day04::parse_input_file() {
    return utils::iter_file_lines(INPUT_FILENAME) | std::ranges::to<std::vector>();
}

using Pos = aoc2025::utils::Vec2<std::int32_t>;

constexpr std::array<Pos, 8> OFFSETS = {{{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}};

bool in_bounds(const std::vector<std::string> &input, const Pos &p) {
    return p.x >= 0 && p.x < input[p.y].size() && p.y >= 0 && p.y < input.size();
}

std::vector<Pos> get_adjacent_rolls(const std::vector<std::string> &input, const Pos &p) {
    // clang-format off
    return OFFSETS | std::views::transform([&](const auto &o) { return p + o; })
                   | std::views::filter([&](const auto &op) { return in_bounds(input, op) && input[op.y][op.x] == '@'; })
                   | std::ranges::to<std::vector>();
    // clang-format on
}

std::uint32_t aoc2025::day04::p1(const std::vector<std::string> &input) {
    std::uint32_t ans = 0;
    for (const auto &p : utils::grid_seq<std::int32_t>(0, input[0].size() - 1, 0, input.size() - 1))
        if (input[p.y][p.x] == '@' && get_adjacent_rolls(input, p).size() < 4) ans++;
    return ans;
}

std::uint32_t aoc2025::day04::p2(const std::vector<std::string> &input) {
    std::vector<std::string> input_copy = input;

    std::vector<Pos> spaces_to_check;
    for (const auto &p : utils::grid_seq<std::int32_t>(0, input[0].size() - 1, 0, input.size() - 1))
        if (input_copy[p.y][p.x] == '@') spaces_to_check.emplace_back(p);

    std::uint32_t ans = 0;
    do {
        std::vector<Pos> buf;
        for (const auto &[x, y] : spaces_to_check) {
            if (input_copy[y][x] != '@') continue;
            if (const auto adjacent_rolls = get_adjacent_rolls(input_copy, {x, y}); adjacent_rolls.size() < 4) {
                ans++;
                input_copy[y][x] = '.';
                buf.append_range(adjacent_rolls);
            }
        }
        std::swap(spaces_to_check, buf);
    } while (!spaces_to_check.empty());
    return ans;
}
