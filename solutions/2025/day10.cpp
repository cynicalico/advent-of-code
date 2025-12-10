/* Day 10: Factory
 * https://adventofcode.com/2025/day/10
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

struct Machine {
    std::uint64_t target{0};
    std::vector<std::uint64_t> buttons{};
};

constexpr ctll::fixed_string pieces_pat = R"(\[([\.#]+)\] ([\(\) \d,]+) \{([\d,]+)\})";

SOLUTION(2025, 10, (std::vector<Machine>), (std::uint64_t), (std::uint64_t))

std::vector<Machine> AOC_NS(2025, 10)::parse_input(const std::filesystem::path &input_path) {
    std::vector<Machine> machines;
    for (const auto &[_, target, buttons, joltage_reqs] : utils::iter_file_regex<pieces_pat>(input_path)) {
        Machine m;
        for (const auto &c : target) {
            m.target <<= 1;
            if (c == '#') m.target |= 0b1;
        }
        for (const auto &b : utils::split(buttons, " ")) {
            std::uint64_t buf = 0;
            for (const auto &n : utils::iter_parse<std::uint64_t>(b)) buf |= (1 << (target.size() - 1 - n));
            m.buttons.emplace_back(buf);
        }
        machines.emplace_back(m);
    }
    return machines;
}

namespace AOC_NS(2025, 10) {
std::uint64_t minimum_presses(const Machine &m) {
    std::queue<std::tuple<std::uint64_t, std::size_t, std::uint64_t>> q;
    std::unordered_set<std::uint64_t> visited;
    q.emplace(0, m.buttons.size(), 0);
    visited.emplace(0);
    while (!q.empty()) {
        const auto [v, last_pressed, steps] = q.front();
        q.pop();
        if (v == m.target) return steps;
        for (const auto &[i, b] : m.buttons | std::views::enumerate) {
            const auto w = v ^ b;
            if (i != last_pressed && !visited.contains(w)) {
                visited.emplace(w);
                q.emplace(w, i, steps + 1);
            }
        }
    }
}
}

std::uint64_t AOC_NS(2025, 10)::p1(std::vector<Machine> &input) {
    return std::ranges::fold_left_first(input | std::views::transform(minimum_presses), std::plus{}).value();
}

std::uint64_t AOC_NS(2025, 10)::p2(std::vector<Machine> &input) { return 0; }
