/* Day 2: Red-Nosed Reports
 * https://adventofcode.com/2024/day/2
 */

#include "solutions/2024/prototypes.hpp"
#include <cstdint>
#include <filesystem>
#include <ranges>
#include <vector>

AOC_NAMESPACE(2024, 02) {
std::vector<Report> parse_input_file(const std::filesystem::path &input_path) {
    // clang-format off
    return utils::iter_file_lines(input_path) |
           std::views::transform([](const auto &line) {
               return utils::iter_parse<std::int32_t>(line) | std::ranges::to<Report>();
           }) |
           std::ranges::to<std::vector>();
    // clang-format on
}

bool is_safe(const Report &report) {
    std::int32_t prev_sign = 0;
    bool is_monotonic = true;
    bool is_stableish = true;
    for (const auto &[a, b] : report | std::views::adjacent<2>) {
        if (prev_sign != 0) is_monotonic &= prev_sign == (std::signbit(a - b) ? -1 : 1);
        is_stableish &= utils::Interval(1, 3).contains(std::abs(a - b));
        prev_sign = std::signbit(a - b) ? -1 : 1;
        if (!is_monotonic || !is_stableish) break;
    }
    return is_monotonic && is_stableish;
}

bool is_safe_dampened(const Report &report) {
    if (is_safe(report)) return true;
    Report dampened;
    dampened.reserve(report.size() - 1);
    for (int i = 0; i < report.size(); ++i) {
        dampened.clear();
        for (int j = 0; j < report.size(); ++j)
            if (j != i) dampened.emplace_back(report[j]);
        if (is_safe(dampened)) return true;
    }
    return false;
}

std::uint32_t p1(std::vector<Report> &input) { return std::ranges::count_if(input, is_safe); }

std::uint32_t p2(std::vector<Report> &input) { return std::ranges::count_if(input, is_safe_dampened); }
}
