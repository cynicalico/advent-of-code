#pragma once

#include "ctre.hpp"
#include <generator>
#include <string_view>

namespace utils {
std::generator<std::string_view> split(std::string_view str, std::string_view delim);
std::generator<std::string_view> split(std::string_view str, char delim);

template <ctll::fixed_string P>
std::generator<std::string_view> split(std::string_view str) {
    const auto begin = str.begin();
    const auto end = str.end();
    auto last_pos = begin;

    for (auto match : ctre::search_all<P>(str)) {
        auto match_start = str.begin() + (match.data() - str.data());
        if (last_pos != match_start) co_yield std::string_view(last_pos, match_start);
        last_pos = match_start + match.size();
    }

    if (last_pos != end) co_yield std::string_view(last_pos, end);
}
}
