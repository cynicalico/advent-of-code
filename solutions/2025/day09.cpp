/* Day 9: Movie Theater
 * https://adventofcode.com/2025/day/9
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

using Pos = utils::Vec2<std::int64_t>;

SOLUTION(2025, 9, (std::vector<Pos>), (std::int64_t), (std::int64_t))

std::vector<Pos> AOC_NS(2025, 9)::parse_input(const std::filesystem::path &input_path) {
    return utils::iter_file_integer_tuples<std::int64_t, 2>(input_path) |
           std::views::transform([](const auto &t) { return Pos(std::get<0>(t), std::get<1>(t)); }) |
           std::ranges::to<std::vector>();
}

namespace AOC_NS(2025, 9) {
std::int64_t find_largest_rectangle(const std::vector<Pos> &input) {
    std::int64_t max = 0;
    for (std::size_t i = 0; i < input.size(); ++i)
        for (std::size_t j = 0; j < input.size(); ++j)
            max = std::max(max, (std::abs(input[j].x - input[i].x) + 1) * (std::abs(input[j].y - input[i].y) + 1));
    return max;
}
}

std::int64_t AOC_NS(2025, 9)::p1(std::vector<Pos> &input) { return find_largest_rectangle(input); }

std::int64_t AOC_NS(2025, 9)::p2(std::vector<Pos> &input) { return 0; }
