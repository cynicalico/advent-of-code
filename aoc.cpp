#include "src/solution_map.hpp"

#include "argparse/argparse.hpp"

#include <chrono>
#include <filesystem>
#include <fmt/format.h>
#include <fstream>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

std::vector<std::tuple<int, int, Solution, std::filesystem::path>>
filter_solutions(std::optional<int> desired_year,
                 std::optional<int> desired_day,
                 const std::optional<std::string> &desired_input);

void run_solutions(const std::vector<std::tuple<int, int, Solution, std::filesystem::path>> &solutions_to_run);

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("Advent of Code");

    argparse::ArgumentParser run_parser("run");
    run_parser.add_argument("-y", "--year").help("Year to run (empty for all)").scan<'d', int>();
    run_parser.add_argument("-d", "--day").help("Day to run (empty for all)").scan<'d', int>();
    run_parser.add_argument("-i", "--input").help("Input file to use (empty for default -> input/YYYY/dayDD.txt)");

    program.add_subparser(run_parser);

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception &e) {
        fmt::print(stderr, "{}", e.what());
        return 1;
    }

    if (program.is_subcommand_used("run")) {
        const auto desired_year = run_parser.present<int>("year");
        auto desired_day = run_parser.present<int>("day");
        const auto desired_input = run_parser.present<std::string>("input");

        if (!desired_year) desired_day = std::nullopt;

        const auto solutions_to_run = filter_solutions(desired_year, desired_day, desired_input);
        if (solutions_to_run.empty()) {
            fmt::print("No solutions available for criteria\n");
            return 0;
        }

        run_solutions(solutions_to_run);
    }

    return 0;
}
std::vector<std::tuple<int, int, Solution, std::filesystem::path>>
filter_solutions(std::optional<int> desired_year,
                 std::optional<int> desired_day,
                 const std::optional<std::string> &desired_input) {
    std::vector<std::tuple<int, int, Solution, std::filesystem::path>> solutions_to_run;
    for (const auto &[year, solutions] : solution_map()) {
        if (desired_year.has_value() && year != desired_year.value()) continue;

        for (const auto &[day, fn] : solutions) {
            if (desired_day.has_value() && day != desired_day.value()) continue;

            const auto input_path = desired_input.value_or(fmt::format("input/{}/day{:02}.txt", year, day));
            solutions_to_run.emplace_back(year, day, fn, input_path);
        }
    }
    return solutions_to_run;
}

void run_solutions(const std::vector<std::tuple<int, int, Solution, std::filesystem::path>> &solutions_to_run) {
    using namespace std::chrono;

    auto total_elapsed = steady_clock::duration::zero();

    for (const auto &[year, day, fn, input_path] : solutions_to_run) {
        fmt::print("{} Day {:02}\n", year, day);

        try {
            auto start = steady_clock::now();
            const auto [part1, part2] = fn(input_path);
            auto end = steady_clock::now();

            const auto elapsed = end - start;
            total_elapsed += elapsed;
            const auto elapsed_ns = duration_cast<nanoseconds>(elapsed);

            std::optional<std::string> part1_expected = std::nullopt;
            std::optional<std::string> part2_expected = std::nullopt;
            const auto expected_path = fmt::format("expected/{}/day{:02}.txt", year, day);
            if (std::filesystem::exists(expected_path)) {
                std::ifstream ifs(expected_path);
                std::string line;
                if (std::getline(ifs, line)) { part1_expected = line; }
                if (std::getline(ifs, line)) { part2_expected = line; }
            }

            fmt::print("  Part 1: {}", part1);
            if (part1_expected) {
                if (part1 == part1_expected.value()) fmt::print(" ✓");
                else fmt::print(" ✗ ({})", part1_expected.value());
            }
            fmt::print("\n");

            fmt::print("  Part 2: {}", part2);
            if (part2_expected) {
                if (part2 == part2_expected.value()) fmt::print(" ✓");
                else fmt::print(" ✗ ({})", part2_expected.value());
            }
            fmt::print("\n");

            fmt::print("Took {:.06f}s\n", static_cast<double>(elapsed_ns.count()) / 1e9);

        } catch (const std::exception &e) { fmt::print(stderr, "Error: {}\n\n", e.what()); }

        fmt::print("\n");
    }

    if (solutions_to_run.size() > 1)
        fmt::print("Total time: {:.06f}s\n",
                   static_cast<double>(duration_cast<nanoseconds>(total_elapsed).count()) / 1e9);
}
