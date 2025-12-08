#include "utils/split.hpp"

std::generator<std::string_view> utils::split(std::string_view str, const std::string_view delim) {
    if (delim.empty()) {
        if (!str.empty()) { co_yield str; }
        co_return;
    }

    std::size_t start = 0;
    std::size_t end = str.find(delim);
    while (end != std::string_view::npos) {
        co_yield str.substr(start, end - start);
        start = end + delim.length();
        end = str.find(delim, start);
    }

    co_yield str.substr(start);
}

std::generator<std::string_view> utils::split(std::string_view str, const char delim) {
    std::size_t start = 0;
    std::size_t end = str.find(delim);
    while (end != std::string_view::npos) {
        co_yield str.substr(start, end - start);
        start = end + 1;
        end = str.find(delim, start);
    }

    co_yield str.substr(start);
}
