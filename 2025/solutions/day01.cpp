/* Day 1: Secret Entrance
 * https://adventofcode.com/2025/day/1
 */

#include "utils/base.hpp"

SOLUTION(2025, 01, (std::vector<int>), (int), (int))

std::vector<int> aoc2025::day01::parse_input_file() {
    // clang-format off
    return utils::iter_file_lines(INPUT_FILENAME) |
           std::views::transform([](const auto &line) {
               const auto amount = utils::parse<int>(line);
               return line[0] == 'L' ? -amount : amount;
           }) |
           std::ranges::to<std::vector>();
    // clang-format on
}

int aoc2025::day01::p1(std::vector<int> &input) {
    int ans = 0;
    int position = 50;
    for (const auto amount : input) {
        position = utils::mod(position + amount, 100);
        if (position == 0) ans++;
    }
    return ans;
}

int aoc2025::day01::p2(std::vector<int> &input) {
    int ans = 0;
    int position = 50;
    for (const auto amount : input) {
        const int prev_position = position;
        position = utils::mod(position + amount, 100);
        ans += std::abs(amount) / 100;
        if (const bool crossed_zero = amount < 0 ? prev_position < position : prev_position > position;
            position != 0 && prev_position != 0 && crossed_zero)
            ans++;
        if (position == 0) ans++;
    }
    return ans;
}
