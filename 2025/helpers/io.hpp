#pragma once

#include <filesystem>
#include <generator>

namespace aoc2025::helpers {
std::generator<std::string> lines(const std::filesystem::path &path);
} // namespace aoc2025::helpers