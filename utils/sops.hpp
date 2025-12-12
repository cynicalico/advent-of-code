#pragma once

#include <string>
#include <string_view>

namespace utils {
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);

std::string ltrim_copy(std::string_view s);
std::string rtrim_copy(std::string_view s);
std::string trim_copy(std::string_view s);
} // namespace utils
