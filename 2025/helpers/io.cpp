#include "helpers/io.hpp"
#include "helpers/print.hpp"
#include <fstream>

std::generator<std::string> aoc2025::helpers::lines(const std::filesystem::path &path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error(fmt::format("Failed to open file: {}", path));

    std::string line;
    while (std::getline(file, line)) {
        co_yield line;
    }
}
