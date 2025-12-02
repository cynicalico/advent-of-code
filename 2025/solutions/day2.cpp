/* Day 2: Gift Shop
 * https://adventofcode.com/2025/day/2
 */

#include "utils/base.hpp"

SOLUTION(2025, 02, (std::vector<std::tuple<std::uint64_t, std::uint64_t>>), (std::uint64_t), (std::uint64_t))

static constexpr auto INPUT_PAT = ctll::fixed_string(R"((\d+)-(\d+),?)");
static constexpr auto P1_PAT = ctll::fixed_string(R"((\d+)\1)");
static constexpr auto P2_PAT = ctll::fixed_string(R"((\d+)\1+)");

std::vector<std::tuple<std::uint64_t, std::uint64_t>> aoc2025::day02::parse_input_file() {
    std::vector<std::tuple<std::uint64_t, std::uint64_t>> ranges;
    for (const auto &[whole, start, end] : utils::iterate_file_regex<INPUT_PAT>(INPUT_FILENAME))
        ranges.emplace_back(utils::parse_unsigned<std::uint64_t>(start), utils::parse_unsigned<std::uint64_t>(end));
    return ranges;
}

template <auto P>
std::uint64_t match_in_range(const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    std::uint64_t ans = 0;
    for (const auto &[start, end] : input)
        for (auto i = start; i <= end; ++i)
            if (std::string s = std::to_string(i); ctre::match<P>(s)) ans += i;
    return ans;
}

std::uint64_t aoc2025::day02::p1(const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    return match_in_range<P1_PAT>(input);
}

std::uint64_t aoc2025::day02::p2(const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    return match_in_range<P2_PAT>(input);
}
