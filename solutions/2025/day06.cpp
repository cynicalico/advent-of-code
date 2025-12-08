/* Day 6: Trash Compactor
 * https://adventofcode.com/2025/day/5
 */

#include "solutions/2025/prototypes.hpp"
#include <filesystem>

AOC_NAMESPACE(2025, 06) {
std::vector<std::string> parse_input_file(const std::filesystem::path &input_path) {
    return utils::iter_file_lines(input_path) | std::ranges::to<std::vector>();
}

std::uint64_t do_op(const std::vector<std::uint64_t> buf, char op) {
    switch (op) {
    case '+': return std::ranges::fold_left_first(buf, std::plus{}).value();
    case '*': return std::ranges::fold_left_first(buf, std::multiplies{}).value();
    default: std::unreachable();
    }
}

std::uint64_t p1(std::vector<std::string> &input) {
    std::vector<std::vector<std::uint64_t>> numbers;
    for (const auto &line : input | std::views::take(input.size() - 1))
        numbers.emplace_back(utils::iter_parse<std::uint64_t>(line) | std::ranges::to<std::vector>());

    const std::vector<char> ops = utils::split<R"(\s+)">(input[input.size() - 1]) |
                                  std::views::transform([](const auto &sv) { return sv[0]; }) |
                                  std::ranges::to<std::vector>();

    std::uint64_t ans = 0;
    for (std::size_t i = 0; i < ops.size(); ++i) {
        std::vector<std::uint64_t> buf;
        for (std::size_t j = 0; j < numbers.size(); ++j) buf.emplace_back(numbers[j][i]);
        ans += do_op(buf, ops[i]);
    }
    return ans;
}

std::uint64_t p2(std::vector<std::string> &input) {
    std::uint64_t ans = 0;
    std::size_t i = 0;
    while (i < input[0].size()) {
        char op = input[input.size() - 1][i];
        std::vector<std::uint64_t> buf;
        bool saw_digit;
        do {
            saw_digit = false;
            std::uint64_t n = 0;
            for (std::size_t j = 0; j < input.size() - 1; ++j) {
                if (input[j][i] != ' ') {
                    saw_digit = true;
                    n *= 10;
                    n += input[j][i] - '0';
                }
            }
            if (saw_digit) buf.emplace_back(n);
            i++;
        } while (saw_digit && i < input[0].size());
        ans += do_op(buf, op);
    }
    return ans;
}
}
