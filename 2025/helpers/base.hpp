#pragma once

#include "helpers/io.hpp"
#include "helpers/math.hpp"
#include "helpers/print.hpp"
#include "helpers/std.hpp"

#include "ctre.hpp"

#define UNPACK(...) __VA_ARGS__

#define SOLUTION_PROTOTYPES(ns, d, parse_result_t, p1_ans_t, p2_ans_t) \
    namespace ns::day##d {                                             \
        const char *INPUT_FILENAME = "input/day" #d ".txt";            \
        UNPACK parse_result_t parse_input_file();                      \
        UNPACK p1_ans_t p1(const UNPACK parse_result_t &input);        \
        UNPACK p2_ans_t p2(const UNPACK parse_result_t &input);        \
    }

#define SOLUTION_MAIN(ns, d)                                                                     \
    int main(int, char *[]) {                                                                    \
        using namespace std::chrono;                                                             \
        using namespace ns::day##d;                                                              \
                                                                                                 \
        auto start = steady_clock::now();                                                        \
        try {                                                                                    \
            const auto input = parse_input_file();                                               \
            fmt::print(#ns "::p1: {}\n", p1(input));                                             \
            fmt::print(#ns "::p2: {}\n", p2(input));                                             \
        } catch (const std::runtime_error &e) {                                                  \
            fmt::print("ERROR: {} \n", e.what());                                                \
        }                                                                                        \
        auto end = steady_clock::now();                                                          \
                                                                                                 \
        const auto elapsed = end - start;                                                        \
        const auto elapsed_ns = duration_cast<nanoseconds>(elapsed);                             \
        fmt::print("\nElapsed time: {:.06f}s\n", static_cast<double>(elapsed_ns.count()) / 1e9); \
                                                                                                 \
        return 0;                                                                                \
    }

#define SOLUTION(ns, d, parse_result_t, p1_ans_t, p2_ans_t)        \
    SOLUTION_PROTOTYPES(ns, d, parse_result_t, p1_ans_t, p2_ans_t) \
    SOLUTION_MAIN(ns, d)
