#include "src/aoc_proxy.hpp"
#include "html2md/html2md.h"
#include "utils/io.hpp"
#include <cpr/cpr.h>
#include <filesystem>
#include <fmt/format.h>
#include <fstream>

const char *AocProxy::USER_AGENT = "github.com/cynicalico/advent-of-code by cynicalico@pm.me";
const char *AocProxy::THROTTLE_FILE = ".throttle.timestamp";

bool AocProxy::should_throttle() {
    if (std::filesystem::exists(THROTTLE_FILE)) {
        const auto timestamp = utils::read_file(THROTTLE_FILE);
        const auto seconds_since_last_dl = seconds_since_epoch_() - std::stoll(timestamp);
        return seconds_since_last_dl < THROTTLE_SECONDS;
    }
    return false;
}

void AocProxy::write_throttle_file() { std::ofstream(THROTTLE_FILE) << seconds_since_epoch_(); }

bool AocProxy::dl_input(int year, int day, bool force) {
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

    if (should_throttle()) {
        fmt::print("Outbound traffic limited to once per {} minute(s)\n", THROTTLE_SECONDS / 60);
        return false;
    }

    const auto response = cpr::Get(cpr::Url{url}, cpr::Cookies{{"session", session_token}}, cpr::UserAgent{USER_AGENT});

    if (response.status_code != 200) {
        fmt::print(stderr,
                   "Failed to download input: HTTP {}, Error {} -> {}\n",
                   response.status_code,
                   std::to_string(response.error.code),
                   response.error.message);
        return false;
    }

    std::filesystem::create_directories(fmt::format("input/{}", year));
    std::ofstream(filename) << response.text;

    return true;
}

bool AocProxy::dl_puzzle(int year, int day, bool force) {
    const auto filename = fmt::format("puzzles/{}/day{:02}.md", year, day);
    if (!force && std::filesystem::exists(filename)) {
        fmt::print("Puzzle already downloaded, use --force to override\n");
        return true;
    }

    const auto url = fmt::format("https://adventofcode.com/{}/day/{}", year, day);

    const char *session_token = std::getenv("AOC_SESSION");
    if (!session_token) {
        fmt::print(stderr, "Error: AOC_SESSION environment variable not set\n");
        return false;
    }

    if (should_throttle()) {
        fmt::print("Outbound traffic limited to once per {} minute(s)\n", THROTTLE_SECONDS / 60);
        return false;
    }

    const auto response = cpr::Get(cpr::Url{url}, cpr::Cookies{{"session", session_token}}, cpr::UserAgent{USER_AGENT});

    if (response.status_code != 200) {
        fmt::print(stderr,
                   "Failed to download puzzle: HTTP {}, Error {} -> {}\n",
                   response.status_code,
                   std::to_string(response.error.code),
                   response.error.message);
        return false;
    }

    const auto text = response.text;

    const auto part1_start = text.find("<article class=\"day-desc\">");
    if (part1_start == std::string::npos) return false;
    const auto part1_end = text.find("</article>", part1_start);
    const auto part1_html = text.substr(part1_start, part1_end - part1_start);
    bool ok;
    const auto part1_md = html2md::Convert(part1_html, &ok);
    if (!ok) return false;

    std::filesystem::create_directories(fmt::format("puzzles/{}", year));
    std::ofstream ofs(filename);
    ofs << part1_md;

    const auto part2_start = text.find("<article class=\"day-desc\">", part1_end);
    if (part2_start == std::string::npos) return true; // This isn't a failure, we just haven't unlocked part 2
    const auto part2_end = text.find("</article>", part2_start);
    const auto part2_html = text.substr(part2_start, part2_end - part2_start);
    const auto part2_md = html2md::Convert(part2_html, &ok);
    if (!ok) return false;

    ofs << "\n" << part2_md;

    return true;
}

bool AocProxy::submit_answer(int year, int day, int part, const std::string &answer) {
    const auto url = fmt::format("https://adventofcode.com/{}/day/{}/answer", year, day);

    const char *session_token = std::getenv("AOC_SESSION");
    if (!session_token) {
        fmt::print(stderr, "Error: AOC_SESSION environment variable not set\n");
        return false;
    }

    if (should_throttle()) {
        fmt::print("Outbound traffic limited to once per {} minute(s)\n", THROTTLE_SECONDS / 60);
        return false;
    }

    const auto response = cpr::Post(cpr::Url{url},
                                    cpr::Cookies{{"session", session_token}},
                                    cpr::Payload{{"level", std::to_string(part)}, {"answer", answer}},
                                    cpr::UserAgent{USER_AGENT});

    if (response.status_code != 200) {
        fmt::print(stderr,
                   "Failed to submit answer: HTTP {}, Error {} -> {}\n",
                   response.status_code,
                   std::to_string(response.error.code),
                   response.error.message);
        return false;
    }

    const auto &text = response.text;
    if (const auto resp = parse_answer_response_(text); resp) {
        fmt::print("{}\n", resp);

        // Refresh the puzzle description
        if (part == 1 && std::strcmp(resp, "✓ Correct! That's the right answer!") == 0) dl_puzzle(year, day, true);

        return true;
    }

    fmt::print("⚠ Unknown response from server:\n{}\n", text);
    return false;
}

bool AocProxy::check_year_day(int year, int day) {
    if (year < 2015 || year > 2025) {
        fmt::print("Invalid year: {}\n", year);
        return false;
    }

    if ((year < 2025 && (day < 1 || day > 25)) || (year >= 2025 && (day < 1 || day > 12))) {
        fmt::print("Invalid day: {}\n", day);
        return false;
    }

    return true;
}

std::int64_t AocProxy::seconds_since_epoch_() {
    const auto now = std::chrono::system_clock::now();
    const auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

const char *AocProxy::parse_answer_response_(const std::string &text) {
    if (text.contains("That's the right answer")) return "✓ Correct! That's the right answer!";

    if (text.contains("Did you already complete it")) return "⚠ You've already completed this part.";

    if (text.contains("That's not the right answer")) {
        if (text.contains("too high")) return "✗ Incorrect. Your answer is too high.";
        if (text.contains("too low")) return "✗ Incorrect. Your answer is too low.";
        return "✗ Incorrect. That's not the right answer.";
    }

    if (text.contains("You gave an answer too recently"))
        return "⚠ You gave an answer too recently. Please wait before submitting again.";

    if (text.contains("You don't seem to be solving the right level"))
        return "⚠ You don't seem to be solving the right level. Did you already complete it?";

    return nullptr;
}
