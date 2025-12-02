#pragma once

#include <filesystem>
#include <generator>

namespace aoc2025::helpers {
std::string read_file(const std::filesystem::path &path);
std::generator<std::string> iterate_file_lines(const std::filesystem::path &path);
} // namespace aoc2025::helpers