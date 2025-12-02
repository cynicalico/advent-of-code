/* Day 2: Gift Shop
 * https://adventofcode.com/2025/day/2
 */

#include "utils/base.hpp"

SOLUTION(2025,
         02,
         (std::vector<std::tuple<std::uint64_t, std::uint64_t>>),
         (std::uint64_t),
         (std::uint64_t))

static constexpr auto P1_PAT = ctll::fixed_string(R"((\d+)\1)");
static constexpr auto P2_PAT = ctll::fixed_string(R"((\d+)\1+)");

std::vector<std::tuple<std::uint64_t, std::uint64_t>>
aoc2025::day02::parse_input_file() {
    return utils::iter_file_integer_tuples<std::uint64_t, 2>(INPUT_FILENAME);
}

template <auto P>
std::uint64_t match_in_range(
    const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    std::uint64_t ans = 0;
    for (const auto &[start, end] : input)
        for (auto i = start; i <= end; ++i)
            if (std::string s = std::to_string(i); ctre::match<P>(s)) ans += i;
    return ans;
}

std::uint64_t aoc2025::day02::p1(
    const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    return match_in_range<P1_PAT>(input);
}

std::uint64_t aoc2025::day02::p2(
    const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    return match_in_range<P2_PAT>(input);
}
