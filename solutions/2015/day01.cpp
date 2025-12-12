/* Day 1: Not Quite Lisp
 * https://adventofcode.com/2015/day/1
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

SOLUTION(2015, 1, (std::pair<std::uint64_t, std::uint64_t>), (std::uint64_t), (std::uint64_t))

std::pair<std::uint64_t, std::uint64_t> AOC_NS(2015, 1)::parse_input(const std::filesystem::path &input_path) {
    std::int64_t floor = 0;
    std::int64_t first_basement = -1;
    for (const auto &[i, c] : utils::read_file(input_path) | std::views::enumerate) {
        if (c == '(') ++floor;
        else if (c == ')') --floor;
        if (first_basement == -1 && floor < 0) first_basement = i + 1;
    }
    return {floor, first_basement};
}

std::uint64_t AOC_NS(2015, 1)::p1(std::pair<std::uint64_t, std::uint64_t> &input) { return input.first; }

std::uint64_t AOC_NS(2015, 1)::p2(std::pair<std::uint64_t, std::uint64_t> &input) { return input.second; }
