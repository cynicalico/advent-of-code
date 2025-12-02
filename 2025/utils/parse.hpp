#pragma once

#include <cctype>
#include <generator>
#include <string_view>
#include <type_traits>

namespace aoc2025::utils {
template <typename T>
    requires std::is_integral_v<T> and std::is_unsigned_v<T>
T parse(const std::string_view sv) {
    T result = T(0);
    bool parsing = false;
    for (const auto &c : sv) {
        if (std::isdigit(c)) {
            parsing = true;
            result = result * 10 + (c - '0');
        } else if (parsing)
            break;
    }
    return result;
}

template <typename T>
    requires std::is_integral_v<T> and std::is_unsigned_v<T>
std::generator<T> iterate_parse(const std::string_view sv) {
    T result = 0;
    bool parsing = false;
    for (const auto c : sv) {
        if (std::isdigit(c)) {
            parsing = true;
            result = result * 10 + (c - '0');
        } else if (parsing) {
            co_yield result;
            result = 0;
            parsing = false;
        }
    }
    if (parsing) co_yield result;
}

template <typename T>
    requires std::is_integral_v<T> and std::is_signed_v<T>
T parse(const std::string_view sv) {
    T result = T(0);
    T sign = 1;
    char prev = '\0';
    bool parsing = false;
    for (const auto &c : sv) {
        if (std::isdigit(c)) {
            if (!parsing && prev == '-') sign = -1;
            parsing = true;
            result = result * 10 + (c - '0');
        } else if (parsing)
            break;
        prev = c;
    }
    return result * sign;
}

template <typename T>
    requires std::is_integral_v<T> and std::is_signed_v<T>
std::generator<T> iterate_parse(const std::string_view sv) {
    T result = 0;
    T sign = 1;
    char prev = '\0';
    bool parsing = false;
    for (const auto c : sv) {
        if (std::isdigit(c)) {
            if (!parsing && prev == '-') sign = -1;
            parsing = true;
            result = result * 10 + (c - '0');
        } else if (parsing) {
            co_yield result *sign;
            result = 0;
            sign = 1;
            parsing = false;
        }
        prev = c;
    }
    if (parsing) co_yield result *sign;
}
} // namespace aoc2025::utils