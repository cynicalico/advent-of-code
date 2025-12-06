#include "src/aoc_proxy.hpp"
#include "src/solution_map.hpp"

#include "thirdparty/argparse.hpp"
#include "thirdparty/dotenv.h"

#include <chrono>
#include <filesystem>
#include <fmt/format.h>
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
    dotenv::init();

    argparse::ArgumentParser program("Advent of Code");

    argparse::ArgumentParser run_parser("run");
    run_parser.add_argument("-y", "--year").help("Year to run (empty for all)").scan<'d', int>();
    run_parser.add_argument("-d", "--day").help("Day to run (empty for all)").scan<'d', int>();
    run_parser.add_argument("-i", "--input").help("Input file to use (empty for default -> input/yyyy/daydd.txt)");

    argparse::ArgumentParser dl_parser("dl");
    dl_parser.add_argument("what").choices("input", "puzzle", "both").help("What to download").required();
    dl_parser.add_argument("year").help("Year to download").scan<'d', int>().required();
    dl_parser.add_argument("day").help("Day to download").scan<'d', int>().required();
    dl_parser.add_argument("--force").help("Force download (still respects throttle)").default_value(false);

    argparse::ArgumentParser submit_parser("submit");
    submit_parser.add_argument("year").help("Year to submit").scan<'d', int>().required();
    submit_parser.add_argument("day").help("Day to submit").scan<'d', int>().required();
    submit_parser.add_argument("part").help("Part to submit (1 or 2)").choices(1, 2).scan<'d', int>().required();
    submit_parser.add_argument("answer").help("Answer to submit").required();

    program.add_subparser(run_parser);
    program.add_subparser(dl_parser);
    program.add_subparser(submit_parser);

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

    } else if (program.is_subcommand_used("dl")) {
        const auto what = dl_parser.get<std::string>("what");
        const auto year = dl_parser.get<int>("year");
        const auto day = dl_parser.get<int>("day");
        const auto force = dl_parser.get<bool>("force");

        if (!AocProxy::check_year_day(year, day)) return 1;

        bool good = true;
        if (what == "input" || what == "both") good &= AocProxy::dl_input(year, day, force);
        if (what == "puzzle" || what == "both") good &= AocProxy::dl_puzzle(year, day, force);
        return good ? 0 : 1;

    } else if (program.is_subcommand_used("submit")) {
        const auto year = submit_parser.get<int>("year");
        const auto day = submit_parser.get<int>("day");
        const auto part = submit_parser.get<int>("part");
        const auto answer = submit_parser.get<std::string>("answer");

        if (!AocProxy::check_year_day(year, day)) return 1;

        bool good = AocProxy::submit_answer(year, day, part, answer);
        return good ? 0 : 1;
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

            fmt::print("  Part 1: {}\n", part1);
            fmt::print("  Part 2: {}\n", part2);
            fmt::print("Took {:.06f}s\n", static_cast<double>(elapsed_ns.count()) / 1e9);

        } catch (const std::exception &e) { fmt::print(stderr, "Error: {}\n\n", e.what()); }

        fmt::print("\n");
    }

    if (solutions_to_run.size() > 1)
        fmt::print("Total time: {:.06f}s\n",
                   static_cast<double>(duration_cast<nanoseconds>(total_elapsed).count()) / 1e9);
}
