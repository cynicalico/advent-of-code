#pragma once

#include "ctre.hpp"
#include "parse.hpp"

#include <filesystem>
#include <generator>
#include <ranges>
#include <type_traits>
#include <utility>

namespace aoc2025::utils {
std::string read_file(const std::filesystem::path &path);

std::generator<std::string> iterate_file_lines(const std::filesystem::path &path);

template <auto P>
std::generator<const std::ranges::range_value_t<decltype(ctre::search_all<P>(std::declval<const std::string &>()))> &>
iterate_file_regex(const std::filesystem::path &path) {
    for (const std::string input = read_file(path); const auto match : ctre::search_all<P>(input))
        co_yield match;
}

template <typename T>
std::generator<T> iterate_file_integers(const std::filesystem::path &path) {
    for (const std::string input = read_file(path); const auto integer : iterate_parse<T>(input))
        co_yield integer;
}
} // namespace aoc2025::utils