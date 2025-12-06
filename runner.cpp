#include "thirdparty/argparse.hpp"
#include "thirdparty/dotenv.h"
#include "utils/io.hpp"
#include "utils/print.hpp"
#include <cpr/cpr.h>
#include <filesystem>
#include <functional>
#include <map>

using Solution = std::function<std::tuple<std::string, std::string>(const std::filesystem::path &)>;
std::map<int, std::map<int, Solution>> solution_map();

std::vector<std::tuple<int, int, Solution, std::filesystem::path>>
filter_solutions(std::optional<int> desired_year,
                 std::optional<int> desired_day,
                 const std::optional<std::string> &desired_input);

void run_solutions(const std::vector<std::tuple<int, int, Solution, std::filesystem::path>> &solutions_to_run);

auto THROTTLE_TIMESTAMP_FILE = ".last_dl.timestamp";
constexpr int THROTTLE_SECONDS = 180;
bool dl_input(int year, int day, bool force);
bool dl_puzzle(int year, int day, bool force);
std::int64_t seconds_since_epoch();
bool should_throttle_dl();
void write_throttle_file();

int main(int argc, char *argv[]) {
    dotenv::init();

    argparse::ArgumentParser program("AoC Runner");

    argparse::ArgumentParser run_parser("run");
    run_parser.add_argument("-y", "--year").help("Year to run (empty for all)").scan<'d', int>();
    run_parser.add_argument("-d", "--day").help("Day to run (empty for all)").scan<'d', int>();
    run_parser.add_argument("-i", "--input").help("Input file to use (empty for default -> input/yyyy/daydd.txt)");

    argparse::ArgumentParser dl_parser("dl");
    dl_parser.add_argument("what").choices("input", "puzzle", "both").help("What to download").required();
    dl_parser.add_argument("year").help("Year to download").scan<'d', int>().required();
    dl_parser.add_argument("day").help("Day to download").scan<'d', int>().required();
    dl_parser.add_argument("--force").help("Force download (still respects throttle)").default_value(false);

    program.add_subparser(run_parser);
    program.add_subparser(dl_parser);

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

    } else if (program.is_subcommand_used("dl")) {
        if (should_throttle_dl()) {
            fmt::print("Downloads throttled to once per 3 minutes\n");
            return 0;
        }

        const auto what = dl_parser.get<std::string>("what");
        const auto year = dl_parser.get<int>("year");
        const auto day = dl_parser.get<int>("day");
        const auto force = dl_parser.get<bool>("force");

        if (year < 2015 || year > 2025) {
            fmt::print("Invalid year: {}\n", year);
            return 1;
        }

        if ((year < 2025 && (day < 1 || day > 25)) || (year >= 2025 && (day < 1 || day > 12))) {
            fmt::print("Invalid day: {}\n", day);
            return 1;
        }

        bool good = true;
        if (what == "input" || what == "both") good &= dl_input(year, day, force);
        if (what == "puzzle" || what == "both") good &= dl_puzzle(year, day, force);
        write_throttle_file();
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

bool dl_input(int year, int day, bool force) {
    const auto filename = fmt::format("input/{}/day{:02}.txt", year, day);
    if (!force && std::filesystem::exists(filename)) {
        fmt::print("Input already downloaded, use --force to override\n");
        return true;
    }

    const auto url = fmt::format("https://adventofcode.com/{}/day/{}/input", year, day);

    const char *session_token = std::getenv("AOC_SESSION");
    if (!session_token) {
        fmt::print(stderr, "Error: AOC_SESSION environment variable not set\n");
        return false;
    }

    const auto response = cpr::Get(cpr::Url{url},
                                   cpr::Cookies{{"session", session_token}},
                                   cpr::UserAgent{"github.com/cynicalico/advent-of-code by cynicalico@pm.me"});
    if (response.status_code != 200) {
        fmt::print(stderr,
                   "Failed to download input: HTTP {}, Error {} -> {}\n",
                   response.status_code,
                   std::to_string(response.error.code),
                   response.error.message);
        return false;
    }

    std::filesystem::create_directories(fmt::format("input/{}", year));
    std::ofstream(fmt::format("input/{}/day{:02}.txt", year, day)) << response.text;

    return true;
}

bool dl_puzzle(int year, int day, bool force) {
    fmt::print("TBD");
    return true;
}

std::int64_t seconds_since_epoch() {
    const auto now = std::chrono::system_clock::now();
    const auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

bool should_throttle_dl() {
    if (std::filesystem::exists(THROTTLE_TIMESTAMP_FILE)) {
        const auto timestamp = utils::read_file(THROTTLE_TIMESTAMP_FILE);
        const auto seconds_since_last_dl = seconds_since_epoch() - std::stoll(timestamp);
        return seconds_since_last_dl < THROTTLE_SECONDS;
    }
    return false;
}

void write_throttle_file() { std::ofstream(THROTTLE_TIMESTAMP_FILE) << seconds_since_epoch(); }

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
