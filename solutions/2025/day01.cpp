/* Day 1: Secret Entrance
 * https://adventofcode.com/2025/day/1
 */

#include "solutions/2025/prototypes.hpp"
#include <cmath>
#include <filesystem>
#include <ranges>
#include <vector>

AOC_NAMESPACE(2025, 01) {
std::vector<int> parse_input_file(const std::filesystem::path &input_path) {
    // clang-format off
    return utils::iter_file_lines(input_path) |
           std::views::transform([](const auto &line) {
               const auto amount = utils::parse<int>(line);
               return line[0] == 'L' ? -amount : amount;
           }) |
           std::ranges::to<std::vector>();
    // clang-format on
}

int p1(std::vector<int> &input) {
    int ans = 0;
    int position = 50;
    for (const auto amount : input) {
        position = utils::mod(position + amount, 100);
        if (position == 0) ans++;
    }
    return ans;
}

int p2(std::vector<int> &input) {
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
}
