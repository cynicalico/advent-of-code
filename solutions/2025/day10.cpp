/* Day 10: Factory
 * https://adventofcode.com/2025/day/10
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

struct Machine {
    std::uint64_t target;
    std::vector<std::uint64_t> target_joltage;
    std::string buttons;
};

SOLUTION(2025, 10, (std::vector<Machine>), (std::uint64_t), (std::uint64_t))

constexpr ctll::fixed_string PIECES_PAT = R"(\[([\.#]+)\] ([\(\) \d,]+) \{([\d,]+)\})";

std::vector<Machine> AOC_NS(2025, 10)::parse_input(const std::filesystem::path &input_path) {
    std::vector<Machine> machines;
    for (const auto &[_, target_pattern, buttons, joltage_reqs] : utils::iter_file_regex<PIECES_PAT>(input_path)) {
        std::uint64_t target = 0;
        for (const auto &c : target_pattern) {
            target <<= 1;
            if (c == '#') target |= 0b1;
        }
        machines.emplace_back(target,
                              utils::iter_parse<std::uint64_t>(joltage_reqs) | std::ranges::to<std::vector>(),
                              std::string(buttons));
    }
    return machines;
}

namespace AOC_NS(2025, 10) {
std::vector<std::uint64_t> buttons_as_bits_vector(const std::string &buttons) {
    const auto max_button = std::ranges::max(utils::iter_parse<std::uint64_t>(buttons));
    std::vector<std::uint64_t> result;
    for (const auto &b : utils::split(buttons, " ")) {
        std::uint64_t buf = 0;
        for (const auto &n : utils::iter_parse<std::uint64_t>(b)) buf |= (1 << (max_button - n));
        result.emplace_back(buf);
    }
    return result;
}

std::uint64_t minimum_presses_p1(const Machine &m) {
    std::vector<std::uint64_t> buttons = buttons_as_bits_vector(m.buttons);
    std::queue<std::tuple<std::uint64_t, std::size_t, std::uint64_t>> q;
    std::unordered_set<std::uint64_t> visited;
    q.emplace(0, buttons.size(), 0);
    visited.emplace(0);
    while (!q.empty()) {
        const auto [v, last_pressed, steps] = q.front();
        q.pop();
        if (v == m.target) return steps;
        for (const auto &[i, b] : buttons | std::views::enumerate) {
            const auto w = v ^ b;
            if (i != last_pressed && !visited.contains(w)) {
                visited.emplace(w);
                q.emplace(w, i, steps + 1);
            }
        }
    }
    std::unreachable();
}
}

std::uint64_t AOC_NS(2025, 10)::p1(std::vector<Machine> &input) {
    return *std::ranges::fold_left_first(input | std::views::transform(minimum_presses_p1), std::plus{});
}

namespace AOC_NS(2025, 10) {
std::uint64_t minimum_presses_p2(const Machine &m) {
    z3::context ctx;
    z3::optimize optimizer(ctx);

    const auto buttons = utils::split(m.buttons, " ") | std::views::transform([](const auto &s) {
                             return utils::iter_parse<std::uint64_t>(s) | std::ranges::to<std::vector>();
                         }) |
                         std::ranges::to<std::vector>();

    std::vector<z3::expr> vars;
    for (std::size_t i = 0; i < buttons.size(); ++i) {
        vars.emplace_back(ctx.int_const(fmt::format("x{}", i).c_str()));
        optimizer.add(vars[i] >= 0);
    }

    for (const auto &[t_i, t] : m.target_joltage | std::views::enumerate) {
        z3::expr_vector vec(ctx);
        for (const auto &[b_i, b] : buttons | std::views::enumerate)
            if (std::ranges::contains(b, t_i)) vec.push_back(vars[b_i]);
        optimizer.add(z3::sum(vec) == ctx.int_val(t));
    }

    z3::expr_vector vec(ctx);
    for (const auto &var : vars) vec.push_back(var);
    z3::expr sum = z3::sum(vec);

    optimizer.minimize(sum);
    if (optimizer.check() == z3::sat) {
        const auto model = optimizer.get_model();
        return *std::ranges::fold_left_first(
                vars | std::views::transform([&model](const auto &v) { return model.eval(v).get_numeral_uint64(); }),
                std::plus{});
    }
    std::unreachable();
}
}

std::uint64_t AOC_NS(2025, 10)::p2(std::vector<Machine> &input) {
    std::uint64_t total = 0;
#pragma omp parallel for reduction(+ : total)
    for (std::size_t i = 0; i < input.size(); ++i) total += minimum_presses_p2(input[i]);
    return total;
}
