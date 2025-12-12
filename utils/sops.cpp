#include "utils/sops.hpp"

#include <algorithm>
#include <cctype>

void utils::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

void utils::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

void utils::trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

std::string utils::ltrim_copy(std::string_view s) {
    auto start = std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); });
    return std::string(start, s.end());
}

std::string utils::rtrim_copy(std::string_view s) {
    auto end = std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base();
    return std::string(s.begin(), end);
}

std::string utils::trim_copy(std::string_view s) {
    auto start = std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); });
    auto end = std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base();
    if (start >= end) return std::string();
    return std::string(start, end);
}
