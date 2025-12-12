/* Day 12: Christmas Tree Farm
 * https://adventofcode.com/2025/day/12
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

SOLUTION(2025, 12, (std::uint64_t), (std::uint64_t), (std::uint64_t))

std::uint64_t aoc2025::day12::parse_input(const std::filesystem::path &input_path) {
    std::uint64_t ans = 0;
    for (const auto &[_, w, h, counts] : utils::iter_file_regex<R"((\d+)x(\d+): ([\d ]+))">(input_path)) {
        const auto total_area = utils::parse<std::uint64_t>(w) * utils::parse<std::uint64_t>(h);
        const auto total_present_area = utils::sum(utils::iter_parse<std::uint64_t>(counts) |
                                                   std::views::transform([](const auto &c) { return c * 9; }));
        if (total_area >= total_present_area) ans++;
    }
    return ans;
}

std::uint64_t aoc2025::day12::p1(std::uint64_t &input) { return input; }

std::uint64_t aoc2025::day12::p2(std::uint64_t &input) { return 0; }
