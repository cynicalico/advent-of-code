/* Day 1: Historian Hysteria
 * https://adventofcode.com/2024/day/1
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

using List = std::vector<std::int32_t>;

SOLUTION(2024, 1, (std::tuple<List, List>), (std::int32_t), (std::int32_t))

std::tuple<List, List> AOC_NS(2024, 1)::parse_input(const std::filesystem::path &input_path) {
    List l1, l2;
    for (const auto &line : utils::iter_file_lines(input_path)) {
        const auto [a, b] = utils::parse_n<std::uint32_t, 2>(line);
        l1.emplace_back(a);
        l2.emplace_back(b);
    }
    std::ranges::sort(l1);
    std::ranges::sort(l2);
    return {l1, l2};
}

std::int32_t AOC_NS(2024, 1)::p1(std::tuple<List, List> &input) {
    const auto distance = std::views::zip_transform(std::minus{}, std::get<0>(input), std::get<1>(input)) |
                          std::views::transform([](const auto &d) { return std::abs(d); });
    return std::ranges::fold_left_first(distance, std::plus{}).value();
}

std::int32_t AOC_NS(2024, 1)::p2(std::tuple<List, List> &input) {
    std::unordered_map<std::int32_t, std::int32_t> counts;
    for (const auto &n : std::get<1>(input)) counts[n]++;
    const auto similarity =
            std::get<0>(input) | std::views::transform([&counts](const auto &n) { return n * counts[n]; });
    return std::ranges::fold_left_first(similarity, std::plus{}).value();
}
