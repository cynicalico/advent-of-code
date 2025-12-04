#pragma once

#include "utils/vec.hpp"
#include <generator>

namespace aoc2025::utils {
template <typename T>
std::generator<Vec2<T>> grid_seq(T x_min, T x_max, T y_min, T y_max) {
    for (T y = y_min; y <= y_max; ++y)
        for (T x = x_min; x <= x_max; ++x)
            co_yield Vec2<T>{x, y};
}
} // namespace aoc2025::utils