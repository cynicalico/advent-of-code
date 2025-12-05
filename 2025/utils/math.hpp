#pragma once

#include <cmath>
#include <tuple>
#include <type_traits>

namespace aoc2025::utils {
template <typename T>
    requires std::is_integral_v<T>
T mod(T a, T b) {
    T m = a % b;
    if (std::signbit(m) != std::signbit(b)) m += b;
    return m;
}

template <typename T>
    requires std::is_integral_v<T>
T num_digits(T n) {
    return n == 0 ? 1 : static_cast<T>(std::log10(n)) + 1;
}

template <typename T>
    requires std::is_arithmetic_v<T>
struct Interval {
    T lo, hi;

    Interval() = default;
    Interval(T lo, T hi)
        : lo(lo),
          hi(hi) {}
    explicit Interval(const std::tuple<T, T> &t)
        : Interval(std::get<0>(t), std::get<1>(t)) {}

    T size() const { return hi - lo + 1; }

    T mid() const { return (lo + hi) / T(2); }

    template <typename U>
        requires std::convertible_to<T, U>
    bool contains(U v) const {
        return lo <= static_cast<T>(v) && static_cast<T>(v) <= hi;
    }
};
} // namespace aoc2025::utils
