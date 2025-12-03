/* Day 2: Gift Shop
 * https://adventofcode.com/2025/day/2
 */

#include "utils/base.hpp"

SOLUTION(2025, 02, (std::vector<std::tuple<std::uint64_t, std::uint64_t>>), (std::uint64_t), (std::uint64_t))

std::vector<std::tuple<std::uint64_t, std::uint64_t>> aoc2025::day02::parse_input_file() {
    std::vector<std::tuple<std::uint64_t, std::uint64_t>> ranges;
    for (const auto &[start, end] : utils::iter_file_integer_tuples<std::uint64_t, 2>(INPUT_FILENAME)) {
        if (utils::num_digits(end) > utils::num_digits(start)) {
            const auto next_po10 = std::pow(10, utils::num_digits(start));
            ranges.emplace_back(start, next_po10 - 1);
            ranges.emplace_back(next_po10, end);
        } else
            ranges.emplace_back(start, end);
    }
    return ranges;
}

void find_invalid(std::set<std::uint64_t> &invalid,
                  const std::uint64_t start,
                  const std::uint64_t end,
                  const std::uint64_t digit_min,
                  const std::uint64_t digit_max) {
    const auto digits = aoc2025::utils::num_digits(start);
    for (auto k = digit_min; k <= digit_max; ++k) {
        const auto m = static_cast<std::uint64_t>(std::pow(10, k));
        const auto n = static_cast<std::uint64_t>(std::pow(10, digits - k));
        for (auto i = start / n; i <= end / n; ++i) {
            std::uint64_t j = 0;
            for (auto l = 0; l < digits / k; ++l)
                j = j * m + i;
            if (j >= start && j <= end) invalid.insert(j);
        }
    }
}

std::uint64_t aoc2025::day02::p1(const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    std::set<std::uint64_t> invalid;
    for (const auto &[start, end] : input) {
        const auto digits = utils::num_digits(start);
        if (digits % 2 != 0) continue;
        find_invalid(invalid, start, end, digits / 2, digits / 2);
    }
    return std::ranges::fold_left(invalid, 0, std::plus{});
}

std::uint64_t aoc2025::day02::p2(const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    std::set<std::uint64_t> invalid;
    for (const auto &[start, end] : input) {
        const auto digits = utils::num_digits(start);
        find_invalid(invalid, start, end, 1, digits / 2);
    }
    return std::ranges::fold_left(invalid, 0, std::plus{});
}
