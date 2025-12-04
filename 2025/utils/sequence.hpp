#pragma once

#include "utils/grid.hpp"
#include "utils/vec.hpp"
#include <generator>

namespace aoc2025::utils {
template <typename T>
std::generator<Vec2<T>> moore_neighborhood_seq(const Vec2<T> &p) {
    static constexpr std::array<Vec2<T>, 8> OFFSETS = {
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}};
    for (const auto &d : OFFSETS)
        co_yield p + d;
}

template <typename T>
std::generator<Vec2<T>> von_neumann_neighborhood_seq(const Vec2<T> &p) {
    static constexpr std::array<Vec2<T>, 8> OFFSETS = {{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
    for (const auto &d : OFFSETS)
        co_yield p + d;
}

template <typename T>
std::generator<Vec2<T>> grid_seq(T x_min, T x_max, T y_min, T y_max) {
    for (T y = y_min; y <= y_max; ++y)
        for (T x = x_min; x <= x_max; ++x)
            co_yield Vec2<T>{x, y};
}

template <typename T, typename U>
std::generator<Vec2<T>> grid_seq(const Grid2D<U> &grid) {
    return grid_seq<T>(0, grid.width() - 1, 0, grid.height() - 1);
}
} // namespace aoc2025::utils