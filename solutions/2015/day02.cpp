/* Day 2: I Was Told There Would Be No Math
 * https://adventofcode.com/2015/day/2
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

using Dims = std::tuple<std::uint64_t, std::uint64_t, std::uint64_t>;

SOLUTION(2015, 2, (std::vector<Dims>), (std::uint64_t), (std::uint64_t))

std::vector<Dims> AOC_NS(2015, 2)::parse_input(const std::filesystem::path &input_path) {
    return utils::iter_file_integer_tuples<std::uint64_t, 3>(input_path);
}

std::uint64_t AOC_NS(2015, 2)::p1(std::vector<Dims> &input) {
    return *std::ranges::fold_left_first(input | std::views::transform([](const Dims &dims) {
                                             auto [l, w, h] = dims;
                                             return 2 * (l * w + w * h + h * l) + std::min({l * w, w * h, h * l});
                                         }),
                                         std::plus{});
}

std::uint64_t AOC_NS(2015, 2)::p2(std::vector<Dims> &input) {
    return *std::ranges::fold_left_first(input | std::views::transform([](const Dims &dims) {
                                             auto [l, w, h] = dims;
                                             return 2 * std::min({l + w, w + h, h + l}) + l * w * h;
                                         }),
                                         std::plus{});
}
