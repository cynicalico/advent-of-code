#pragma once

#include "helpers/io.hpp"
#include "helpers/math.hpp"
#include "helpers/print.hpp"
#include "helpers/std.hpp"

#define SOLUTION_PROTOTYPES(ns, parse_result_t, p1_ans_t, p2_ans_t) \
    namespace ns {                                                  \
    const char *INPUT_FILENAME = "input/day1.txt";                  \
    parse_result_t parse_input_file();                              \
    p1_ans_t p1(const parse_result_t &input);                       \
    p2_ans_t p2(const parse_result_t &input);                       \
    }

#define SOLUTION_MAIN(ns)                          \
    int main(int, char *[]) {                      \
        using namespace ns;                        \
                                                   \
        try {                                      \
            const auto input = parse_input_file(); \
            fmt::print("P1: {}\n", p1(input));     \
            fmt::print("P2: {}\n", p2(input));     \
        } catch (const std::runtime_error &e) {    \
            fmt::print("ERROR: {} \n", e.what());  \
        }                                          \
                                                   \
        return 0;                                  \
    }

#define SOLUTION(ns, parse_result_t, p1_ans_t, p2_ans_t)        \
    SOLUTION_PROTOTYPES(ns, parse_result_t, p1_ans_t, p2_ans_t) \
    SOLUTION_MAIN(ns)
