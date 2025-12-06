#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <string>

using Solution = std::function<std::tuple<std::string, std::string>(const std::filesystem::path &)>;

std::map<int, std::map<int, Solution>> solution_map();
