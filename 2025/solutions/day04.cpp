/* Day 4: Printing Department
 * https://adventofcode.com/2025/day/4
 */

#include "utils/base.hpp"

SOLUTION(2025, 04, (std::vector<std::string>), (std::uint32_t), (std::uint32_t))

std::vector<std::string> aoc2025::day04::parse_input_file() {
    return utils::iter_file_lines(INPUT_FILENAME) | std::ranges::to<std::vector>();
}

using Pos = aoc2025::utils::Vec2<std::int32_t>;

std::vector<Pos>
get_adjacent_rolls(const std::vector<std::string> &input, const std::int32_t ox, const std::int32_t oy) {
    std::vector<Pos> buf;
    for (std::int32_t y = oy > 0 ? oy - 1 : oy; y <= (oy < input.size() - 1 ? oy + 1 : oy); ++y)
        for (std::int32_t x = ox > 0 ? ox - 1 : ox; x <= (ox < input[oy].size() - 1 ? ox + 1 : ox); ++x)
            if (!(y == oy && x == ox) && input[y][x] == '@') buf.emplace_back(x, y);
    return buf;
}

std::uint32_t aoc2025::day04::p1(const std::vector<std::string> &input) {
    std::uint32_t ans = 0;
    for (std::int32_t y = 0; y < input.size(); ++y)
        for (std::int32_t x = 0; x < input[y].size(); ++x)
            if (input[y][x] == '@' && get_adjacent_rolls(input, x, y).size() < 4) ans++;
    return ans;
}

std::uint32_t aoc2025::day04::p2(const std::vector<std::string> &input) {
    std::vector<std::string> input_copy = input;

    std::vector<Pos> spaces_to_check;
    for (std::int32_t y = 0; y < input_copy.size(); ++y)
        for (std::int32_t x = 0; x < input_copy[y].size(); ++x)
            if (input_copy[y][x] == '@') spaces_to_check.emplace_back(x, y);

    std::uint32_t ans = 0;
    do {
        std::vector<Pos> buf;
        for (const auto &[x, y] : spaces_to_check) {
            if (input_copy[y][x] != '@') continue;
            if (const auto adjacent_rolls = get_adjacent_rolls(input_copy, x, y); adjacent_rolls.size() < 4) {
                ans++;
                input_copy[y][x] = '.';
                buf.append_range(adjacent_rolls);
            }
        }
        std::swap(spaces_to_check, buf);
    } while (!spaces_to_check.empty());
    return ans;
}
