#pragma once

#include "utils/utils.hpp"

#define UNPACK(...) __VA_ARGS__

#define AOC_NAMESPACE(yyyy, dd) namespace aoc##yyyy::day##dd

#define SOLUTION_PROTOTYPES(parse_result_t, p1_ans_t, p2_ans_t)                      \
    UNPACK parse_result_t parse_input_file(const std::filesystem::path &input_path); \
    UNPACK p1_ans_t p1(UNPACK parse_result_t &input);                                \
    UNPACK p2_ans_t p2(UNPACK parse_result_t &input);
