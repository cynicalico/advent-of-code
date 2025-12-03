#pragma once

#include <cmath>
#include <concepts>

namespace aoc2025::utils {
template <class T>
    requires std::is_integral_v<T>
T mod(T a, T b) {
    T m = a % b;
    if (std::signbit(m) != std::signbit(b)) m += b;
    return m;
}

template <class T>
    requires std::is_integral_v<T>
T num_digits(T n) {
    return n == 0 ? 1 : static_cast<T>(std::log10(n)) + 1;
}
} // namespace aoc2025::utils
