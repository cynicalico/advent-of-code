#pragma once

#include <cctype>
#include <concepts>
#include <string_view>

namespace aoc2025::helpers {
template <typename T>
    requires std::is_integral_v<T> and std::is_unsigned_v<T>
T parse_unsigned(const std::string_view sv) {
    T result = T(0);
    bool parsing = false;
    for (const auto &c : sv) {
        if (std::isdigit(c))
            parsing = true;
        else if (parsing)
            break;
        if (parsing) result = result * 10 + (c - '0');
    }
    return result;
}
} // namespace aoc2025::helpers