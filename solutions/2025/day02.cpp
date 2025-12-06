/* Day 2: Gift Shop
 * https://adventofcode.com/2025/day/2
 */

#include "solutions/2025/prototypes.hpp"
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <ranges>
#include <set>

AOC_NAMESPACE(2025, 02) {
std::vector<Range> parse_input_file(const std::filesystem::path &input_path) {
    std::vector<Range> ranges;
    for (const auto &[start, end] : utils::iter_file_integer_tuples<std::uint64_t, 2>(input_path)) {
        if (utils::num_digits(end) > utils::num_digits(start)) {
            const auto next_po10 = std::pow(10, utils::num_digits(start));
            ranges.emplace_back(start, next_po10 - 1);
            ranges.emplace_back(next_po10, end);
        } else ranges.emplace_back(start, end);
    }
    return ranges;
}

void find_invalid(std::set<std::uint64_t> &invalid,
                  const std::uint64_t start,
                  const std::uint64_t end,
                  const std::uint64_t digit_min) {
    const auto digits = utils::num_digits(start);
    for (auto k = digit_min; k <= digits / 2; ++k) {
        if (digits % k != 0) continue;
        const auto m = static_cast<std::uint64_t>(std::pow(10, k));
        const auto n = static_cast<std::uint64_t>(std::pow(10, digits - k));
        for (auto i = start / n; i <= end / n; ++i) {
            std::uint64_t j = 0;
            for (auto l = 0; l < digits / k; ++l) j = j * m + i;
            if (j >= start && j <= end) invalid.insert(j);
        }
    }
}

std::uint64_t p1(std::vector<Range> &input) {
    std::set<std::uint64_t> invalid;
    for (const auto &[start, end] : input) {
        const auto digits = utils::num_digits(start);
        if (digits % 2 != 0) continue;
        find_invalid(invalid, start, end, digits / 2);
    }
    return std::ranges::fold_left(invalid, 0, std::plus{});
}

std::uint64_t p2(std::vector<Range> &input) {
    std::set<std::uint64_t> invalid;
    for (const auto &[start, end] : input) find_invalid(invalid, start, end, 1);
    return std::ranges::fold_left(invalid, 0, std::plus{});
}
}
