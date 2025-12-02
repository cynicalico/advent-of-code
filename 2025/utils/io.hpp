#pragma once

#include "ctre.hpp"
#include "utils/parse.hpp"

#include <filesystem>
#include <generator>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

namespace aoc2025::utils {
std::string read_file(const std::filesystem::path &path);

std::generator<std::string> iter_file_lines(const std::filesystem::path &path);

template <auto P>
std::generator<const std::ranges::range_value_t<
    decltype(ctre::search_all<P>(std::declval<const std::string &>()))> &>
iter_file_regex(const std::filesystem::path &path) {
    for (const std::string input = read_file(path);
         const auto match : ctre::search_all<P>(input))
        co_yield match;
}

template <typename T>
std::generator<T> iter_file_integers(const std::filesystem::path &path) {
    for (const std::string input = read_file(path);
         const auto integer : iterate_parse<T>(input))
        co_yield integer;
}

template <typename T, std::size_t N>
auto iter_file_integer_tuples(const std::filesystem::path &path) {
    using tuple_t = decltype(std::tuple_cat(std::declval<std::array<T, N>>()));
    std::vector<tuple_t> result;

    auto gen = iter_file_integers<T>(path);
    for (auto it = gen.begin(); it != gen.end();) {
        std::array<T, N> values;

        std::size_t i = 0;
        for (; i < N && it != gen.end(); ++i, ++it)
            values[i] = *it;

        if (i == N) result.push_back(std::tuple_cat(values));
    }

    return result;
}
} // namespace aoc2025::utils
