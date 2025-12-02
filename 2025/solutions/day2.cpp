/* Day 2: Gift Shop
 * https://adventofcode.com/2025/day/2
 */

#include "helpers/base.hpp"

SOLUTION(2025, 02, (std::vector<std::tuple<std::uint64_t, std::uint64_t>>), (std::uint64_t), (std::uint64_t))

std::vector<std::tuple<std::uint64_t, std::uint64_t>> aoc2025::day02::parse_input_file() {
    static constexpr auto input_pat = ctll::fixed_string(R"((\d+)-(\d+),?)");
    std::vector<std::tuple<std::uint64_t, std::uint64_t>> ranges;
    for (const std::string input = helpers::read_file(INPUT_FILENAME);
         const auto match : ctre::search_all<input_pat>(input))
        ranges.emplace_back(std::atoll(std::string_view(match.get<1>()).data()),
                            std::atoll(std::string_view(match.get<2>()).data()));
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
    static constexpr auto p1_pat = ctll::fixed_string(R"((\d+)\1)");
    return match_in_range<p1_pat>(input);
}

std::uint64_t aoc2025::day02::p2(const std::vector<std::tuple<std::uint64_t, std::uint64_t>> &input) {
    static constexpr auto p2_pat = ctll::fixed_string(R"((\d+)\1+)");
    return match_in_range<p2_pat>(input);
}
