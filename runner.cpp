#include "utils/print.hpp"
#include <argparse/argparse.hpp>
#include <filesystem>
#include <functional>
#include <map>

using Solution = std::function<std::tuple<std::string, std::string>(const std::filesystem::path &)>;
std::map<int, std::map<int, Solution>> solution_map();

std::vector<std::tuple<int, int, Solution, std::filesystem::path>> filter_solutions(
        std::optional<int> desired_year, std::optional<int> desired_day, std::optional<std::string> desired_input);

void run_solutions(std::vector<std::tuple<int, int, Solution, std::filesystem::path>> solutions_to_run);

int main(int argc, char *argv[]) {
    argparse::ArgumentParser program("AoC Runner");

    argparse::ArgumentParser run_parser("run");
    run_parser.add_argument("-y", "--year").help("Which year to run (empty for all)").scan<'d', int>();
    run_parser.add_argument("-d", "--day").help("Which day to run (empty for all)").scan<'d', int>();
    run_parser.add_argument("-i", "--input").help("Input file to use (empty for default -> input/yyyy/daydd.txt)");

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
        if (!desired_year) desired_day = std::nullopt;

        const auto desired_input = run_parser.present<std::string>("input");

        const auto solutions_to_run = filter_solutions(desired_year, desired_day, desired_input);
        if (solutions_to_run.empty()) {
            fmt::print("No solutions available for criteria\n");
            return 0;
        }

        run_solutions(solutions_to_run);
    }

    return 0;
}

std::vector<std::tuple<int, int, Solution, std::filesystem::path>> filter_solutions(
        std::optional<int> desired_year, std::optional<int> desired_day, std::optional<std::string> desired_input) {
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

void run_solutions(std::vector<std::tuple<int, int, Solution, std::filesystem::path>> solutions_to_run) {
    using namespace std::chrono;

    auto total_elapsed = steady_clock::duration::zero();

    for (const auto &[year, day, fn, input_path] : solutions_to_run) {
        auto start = steady_clock::now();
        const auto [part1, part2] = fn(input_path);
        auto end = steady_clock::now();

        const auto elapsed = end - start;
        total_elapsed += elapsed;
        const auto elapsed_ns = duration_cast<nanoseconds>(elapsed);

        fmt::print("AoC {} Day {:02}\n", year, day);
        fmt::print("  Part 1: {}\n", part1);
        fmt::print("  Part 2: {}\n", part2);
        fmt::print("Took {:.06f}s\n", static_cast<double>(elapsed_ns.count()) / 1e9);
        fmt::print("\n");
    }

    if (solutions_to_run.size() > 1)
        fmt::print("Total time: {:.06f}s\n",
                   static_cast<double>(duration_cast<nanoseconds>(total_elapsed).count()) / 1e9);
}

#include "solutions/2025/prototypes.hpp"

#define SOLUTION(yyyy, dd)                                                                \
    [](const std::filesystem::path &input_path) -> std::tuple<std::string, std::string> { \
        using AOC_NAMESPACE(yyyy, dd);                                                    \
        auto input = parse_input_file(input_path);                                        \
        auto p1_ans = p1(input);                                                          \
        auto p2_ans = p2(input);                                                          \
        return {fmt::format("{}", p1_ans), fmt::format("{}", p2_ans)};                    \
    }

// clang-format off
std::map<int, std::map<int, Solution>> solution_map() {
    return {
    /*[[[cog
    import cog
    import os
    import re

    for root, dirs, files in os.walk("solutions", topdown=True):
        dirs[:] = sorted(dirs, key=int) # sort dirs by year
        m = re.match(r"solutions/(\d+)", root)
        if m:
            year = m[1]
            cog.outl(f"{{{year}, {{")
            days = []
            for f in files:
                m = re.match(r"day(\d+)\.cpp", f)
                if m:
                    days.append(m[1])
            for day in sorted(days):
                cog.outl(f"    {{{day}, SOLUTION({year}, {day})}},")
            cog.outl("}},")
    ]]]*/
    {2025, {
        {01, SOLUTION(2025, 01)},
        {02, SOLUTION(2025, 02)},
        {03, SOLUTION(2025, 03)},
        {04, SOLUTION(2025, 04)},
        {05, SOLUTION(2025, 05)},
    }},
    //[[[end]]]
    };
}
// clang-format on
