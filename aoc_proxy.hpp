#pragma once

#include "utils/utils.hpp"
#include <cpr/cpr.h>
#include <filesystem>
#include <fstream>
#include <string>

class AocProxy {
    static const char *USER_AGENT;

    static const char *THROTTLE_FILE;
    static constexpr int THROTTLE_SECONDS = 180;

public:
    static bool should_throttle();
    static void write_throttle_file();

    static bool dl_input(int year, int day, bool force);
    static bool dl_puzzle(int year, int day, bool force);

    static bool submit_answer(int year, int day, int part, const std::string &answer);

    static bool check_year_day(int year, int day);

private:
    static std::int64_t seconds_since_epoch_();

    static const char *parse_answer_response_(const std::string &response);
};

const char *AocProxy::USER_AGENT = "github.com/cynicalico/advent-of-code by cynicalico@pm.me";
const char *AocProxy::THROTTLE_FILE = ".last_dl.timestamp";

inline bool AocProxy::should_throttle() {
    if (std::filesystem::exists(THROTTLE_FILE)) {
        const auto timestamp = utils::read_file(THROTTLE_FILE);
        const auto seconds_since_last_dl = seconds_since_epoch_() - std::stoll(timestamp);
        return seconds_since_last_dl < THROTTLE_SECONDS;
    }
    return false;
}

inline void AocProxy::write_throttle_file() { std::ofstream(THROTTLE_FILE) << seconds_since_epoch_(); }

inline bool AocProxy::dl_input(int year, int day, bool force) {
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
    write_throttle_file();

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

inline bool AocProxy::dl_puzzle(int year, int day, bool force) {
    if (should_throttle()) {
        fmt::print("Outbound traffic limited to once per {} minute(s)\n", THROTTLE_SECONDS / 60);
        return false;
    }

    fmt::print("TBD");
    return true;
}

inline bool AocProxy::submit_answer(int year, int day, int part, const std::string &answer) {
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
    write_throttle_file();

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
        return true;
    }

    fmt::print("⚠ Unknown response from server:\n{}\n", text);
    return false;
}

inline bool AocProxy::check_year_day(int year, int day) {
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

inline std::int64_t AocProxy::seconds_since_epoch_() {
    const auto now = std::chrono::system_clock::now();
    const auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

inline const char *AocProxy::parse_answer_response_(const std::string &text) {
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
