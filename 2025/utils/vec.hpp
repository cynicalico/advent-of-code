#pragma once

#include <type_traits>

namespace aoc2025::utils {
template <typename T>
struct Vec2 {
    T x, y;

    Vec2()
        : x(T(0)),
          y(T(0)) {}

    Vec2(T x, T y)
        : x(x),
          y(y) {}

    bool operator==(const Vec2 &other) const = default;
};
} // namespace aoc2025::utils

template <typename T>
struct std::hash<aoc2025::utils::Vec2<T>> {
    std::size_t operator()(const aoc2025::utils::Vec2<T> &v) const noexcept {
        const std::size_t h1 = std::hash<T>{}(v.x);
        const std::size_t h2 = std::hash<T>{}(v.y);
        return h1 ^ h2 << 1;
    }
};