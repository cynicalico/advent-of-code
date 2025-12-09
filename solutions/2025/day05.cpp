/* Day 5: Cafeteria
 * https://adventofcode.com/2025/day/5
 */

#include "solutions/2025/prototypes.hpp"
#include "utils/utils.hpp"

using Range = utils::Interval<std::uint64_t>;
using Input = std::pair<std::vector<Range>, std::vector<std::uint64_t>>;

SOLUTION(2025, 05, (Input), (std::size_t), (std::size_t))

Input aoc2025::day05::parse_input_file(const std::filesystem::path &input_path) {
    std::vector<Range> ranges;
    std::vector<std::uint64_t> ids;

    bool parsing_ranges = true;
    for (const auto &line : utils::iter_file_lines(input_path)) {
        if (line.empty()) {
            parsing_ranges = false;
            continue;
        }
        if (parsing_ranges) ranges.emplace_back(utils::parse_n<std::uint64_t, 2>(line));
        else ids.emplace_back(utils::parse<std::uint64_t>(line));
    }

    std::ranges::sort(ranges, [](const auto &a, const auto &b) { return a.lo < b.lo; });

    std::vector combined_ranges = {ranges.front()};
    for (const auto &[next_lo, next_hi] : ranges | std::views::drop(1)) {
        if (const auto &[prev_lo, prev_hi] = combined_ranges.back(); prev_hi >= next_lo) {
            if (prev_hi >= next_hi) continue; // interval already accounted for, skip it
            combined_ranges.back().hi = next_hi;
        } else combined_ranges.emplace_back(next_lo, next_hi);
    }

    return {combined_ranges, ids};
}

std::size_t aoc2025::day05::p1(Input &input) {
    return std::ranges::count_if(input.second, [&input](const auto &id) {
        return std::ranges::any_of(input.first, [&id](const auto &range) { return range.contains(id); });
    });
}

std::size_t aoc2025::day05::p2(Input &input) {
    return std::ranges::fold_left(
            input.first, 0, [](std::size_t count, const auto &range) { return count + range.size(); });
}
