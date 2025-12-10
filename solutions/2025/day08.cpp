/* Day 8: Playground
 * https://adventofcode.com/2025/day/8
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

using Pos = utils::Vec3<std::int64_t>;

SOLUTION(2025, 8, (std::pair<std::size_t, std::int64_t>), (std::size_t), (std::int64_t))

std::pair<std::size_t, std::int64_t> AOC_NS(2025, 8)::parse_input(const std::filesystem::path &input_path) {
    const auto boxes =
            utils::iter_file_integer_tuples<std::int64_t, 3>(input_path) |
            std::views::transform([](const auto &t) { return Pos(std::get<0>(t), std::get<1>(t), std::get<2>(t)); }) |
            std::ranges::to<std::vector>();

    std::vector<std::pair<std::pair<std::size_t, std::size_t>, std::int64_t>> distances;
    for (std::size_t i = 0; i < boxes.size(); ++i)
        for (std::size_t j = i + 1; j < boxes.size(); ++j)
            distances.emplace_back(std::make_pair(i, j), boxes[i].distance_sq(boxes[j]));
    std::sort(distances.begin(), distances.end(), [](const auto &a, const auto &b) { return a.second < b.second; });

    std::vector<std::int64_t> circuits;
    for (std::size_t i = 0; i < boxes.size(); ++i) circuits.emplace_back(i);

    for (std::size_t i = 0; i < 1000; ++i) {
        const auto &[from, to] = distances[i].first;
        const auto tmp = circuits[to];
        for (std::size_t j = 0; j < circuits.size(); ++j)
            if (circuits[j] == tmp) circuits[j] = circuits[from];
    }

    std::vector<std::int64_t> counts(boxes.size(), 0);
    for (const auto &circuit : circuits) ++counts[circuit];
    std::vector<std::size_t> counts_sorted(counts.begin(), counts.end());
    std::ranges::sort(counts_sorted, std::greater<std::size_t>{});

    const auto p1_ans = counts_sorted[0] * counts_sorted[1] * counts_sorted[2];

    std::int64_t p2_ans;
    for (std::size_t i = 1000; i < distances.size(); ++i) {
        const auto &[from, to] = distances[i].first;
        const auto tmp = circuits[to];
        bool all_match_from = true;
        for (std::size_t j = 0; j < circuits.size(); ++j) {
            if (circuits[j] == tmp) circuits[j] = circuits[from];
            if (circuits[j] != circuits[from]) all_match_from = false;
        }

        if (all_match_from) {
            p2_ans = boxes[from].x * boxes[to].x;
            break;
        }
    }

    return {p1_ans, p2_ans};
}

std::size_t AOC_NS(2025, 8)::p1(std::pair<std::size_t, std::int64_t> &input) { return input.first; }

std::int64_t AOC_NS(2025, 8)::p2(std::pair<std::size_t, std::int64_t> &input) { return input.second; }
