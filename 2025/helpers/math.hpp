#pragma once

#include <cmath>
#include <concepts>

namespace aoc2025::helpers {
template <class T>
    requires std::is_integral_v<T>
T mod(T a, T b) {
    T m = a % b;
    if (std::signbit(m) != std::signbit(b)) m += b;
    return m;
}
} // namespace aoc2025::helpers