/* Day 4: The Ideal Stocking Stuffer
 * https://adventofcode.com/2015/day/4
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

SOLUTION(2015, 4, (std::pair<std::uint64_t, std::uint64_t>), (std::uint64_t), (std::uint64_t))

constexpr std::uint64_t NOT_FOUND = std::numeric_limits<std::uint64_t>::max();

std::pair<std::uint64_t, std::uint64_t> AOC_NS(2015, 4)::parse_input(const std::filesystem::path &input_path) {
    auto input = utils::read_file(input_path);
    utils::trim(input);

    std::atomic<std::uint64_t> p1_ans = NOT_FOUND, p2_ans = NOT_FOUND;

    std::atomic<std::uint64_t> current_batch = 1;
    const std::uint64_t batch_size = 10000;

#pragma omp parallel
    {
        std::uint64_t local_p1 = NOT_FOUND, local_p2 = NOT_FOUND;

        while (p1_ans.load() == NOT_FOUND || p2_ans.load() == NOT_FOUND) {
            std::uint64_t batch_start = current_batch.fetch_add(batch_size);
            std::uint64_t batch_end = batch_start + batch_size;

            for (std::uint64_t i = batch_start; (local_p1 == NOT_FOUND || local_p2 == NOT_FOUND) && i < batch_end;
                 ++i) {
                const auto digest = utils::md5::hash(fmt::format("{}{}", input, i));
                if ((digest[0] == 0 && digest[1] == 0 && (digest[2] >> 4) == 0)) {
                    if (local_p1 == NOT_FOUND) local_p1 = i;
                    if (local_p2 == NOT_FOUND && (digest[2] & 0xff) == 0) local_p2 = i;
                }
            }

            if (local_p1 != NOT_FOUND) {
                std::uint64_t expected = NOT_FOUND;
                if (p1_ans.compare_exchange_strong(expected, local_p1)) {
                } else {
                    std::uint64_t current = p1_ans.load();
                    while (current > local_p1 && !p1_ans.compare_exchange_weak(current, local_p1));
                }
            }

            if (local_p2 != NOT_FOUND) {
                std::uint64_t expected = NOT_FOUND;
                if (p2_ans.compare_exchange_strong(expected, local_p2)) {
                } else {
                    std::uint64_t current = p2_ans.load();
                    while (current > local_p2 && !p2_ans.compare_exchange_weak(current, local_p2));
                }
            }
        }
    }

    return {p1_ans.load(), p2_ans.load()};
}

std::uint64_t AOC_NS(2015, 4)::p1(std::pair<std::uint64_t, std::uint64_t> &input) { return input.first; }

std::uint64_t AOC_NS(2015, 4)::p2(std::pair<std::uint64_t, std::uint64_t> &input) { return input.second; }
