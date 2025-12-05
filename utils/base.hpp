#pragma once

#include "utils/grid.hpp"
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

#define SOLUTION_PROTOTYPES(yyyy, dd, parse_result_t, p1_ans_t, p2_ans_t)                \
    namespace aoc##yyyy::day##dd {                                                       \
        UNPACK parse_result_t parse_input_file(const std::filesystem::path &input_path); \
        UNPACK p1_ans_t p1(UNPACK parse_result_t & input);                               \
        UNPACK p2_ans_t p2(UNPACK parse_result_t & input);                               \
    }
