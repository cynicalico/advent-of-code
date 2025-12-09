#pragma once

#include <fmt/format.h>

#include <filesystem>
#include <functional>
#include <string>
#include <tuple>

using Solution = std::function<std::tuple<std::string, std::string>(const std::filesystem::path &)>;

#define UNPACK(...) __VA_ARGS__

#define AOC_NS(yyyy, dd) aoc##yyyy::day##dd

#define SOLUTION_PROTOTYPE(yyyy, dd) \
    namespace AOC_NS(yyyy, dd) {     \
    Solution solution();             \
    }

#define SOLUTION(yyyy, dd, parse_result_t, p1_ans_t, p2_ans_t)                                       \
    namespace AOC_NS(yyyy, dd) {                                                                     \
    UNPACK parse_result_t parse_input(const std::filesystem::path &input_path);                      \
    UNPACK p1_ans_t p1(UNPACK parse_result_t &input);                                                \
    UNPACK p2_ans_t p2(UNPACK parse_result_t &input);                                                \
    }                                                                                                \
    Solution AOC_NS(yyyy, dd)::solution() {                                                          \
        return [](const std::filesystem::path &input_path) -> std::tuple<std::string, std::string> { \
            auto input = parse_input(input_path);                                                    \
            auto p1_ans = p1(input);                                                                 \
            auto p2_ans = p2(input);                                                                 \
            return {fmt::format("{}", p1_ans), fmt::format("{}", p2_ans)};                           \
        };                                                                                           \
    }
