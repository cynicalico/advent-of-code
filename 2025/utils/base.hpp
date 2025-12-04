#pragma once

#include "utils/io.hpp"
#include "utils/math.hpp"
#include "utils/parse.hpp"
#include "utils/print.hpp"
#include "utils/sequence.hpp"
#include "utils/std.hpp"
#include "utils/vec.hpp"

#include "ctre.hpp"

#define STRINGIZE(x) #x
#define UNPACK(...) __VA_ARGS__

#define SOLUTION_PROTOTYPES(yyyy, dd, parse_result_t, p1_ans_t, p2_ans_t) \
    namespace aoc##yyyy::day##dd {                                        \
        const char *INPUT_FILENAME = "input/day" #dd ".txt";              \
        UNPACK parse_result_t parse_input_file();                         \
        UNPACK p1_ans_t p1(const UNPACK parse_result_t &input);           \
        UNPACK p2_ans_t p2(const UNPACK parse_result_t &input);           \
    }

#define SOLUTION_MAIN(yyyy, dd, p1_ans_t, p2_ans_t)                                              \
    int main(int, char *[]) {                                                                    \
        using namespace std::chrono;                                                             \
        using namespace aoc##yyyy::day##dd;                                                      \
                                                                                                 \
        auto p1_ans = UNPACK p1_ans_t();                                                         \
        auto p2_ans = UNPACK p2_ans_t();                                                         \
                                                                                                 \
        auto start = steady_clock::now();                                                        \
        try {                                                                                    \
            const auto input = parse_input_file();                                               \
            p1_ans = p1(input);                                                                  \
            p2_ans = p2(input);                                                                  \
        } catch (const std::runtime_error &e) {                                                  \
            fmt::print("ERROR: {} \n", e.what());                                                \
        }                                                                                        \
        auto end = steady_clock::now();                                                          \
                                                                                                 \
        const auto elapsed = end - start;                                                        \
        const auto elapsed_ns = duration_cast<nanoseconds>(elapsed);                             \
                                                                                                 \
        fmt::print(STRINGIZE(aoc## yyyy) "::" STRINGIZE(day## dd) "::p1: {}\n", p1_ans);           \
        fmt::print(STRINGIZE(aoc## yyyy) "::" STRINGIZE(day## dd) "::p2: {}\n", p2_ans);           \
        fmt::print("\nElapsed time: {:.06f}s\n", static_cast<double>(elapsed_ns.count()) / 1e9); \
                                                                                                 \
        return 0;                                                                                \
    }

#define SOLUTION(yyyy, dd, parse_result_t, p1_ans_t, p2_ans_t)        \
    SOLUTION_PROTOTYPES(yyyy, dd, parse_result_t, p1_ans_t, p2_ans_t) \
    SOLUTION_MAIN(yyyy, dd, p1_ans_t, p2_ans_t)
