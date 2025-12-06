#pragma once

#include <cstdint>
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
