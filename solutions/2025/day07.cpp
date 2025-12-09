/* Day 7: Laboratories
 * https://adventofcode.com/2025/day/7
 */

#include "solutions/2025/prototypes.hpp"
#include "utils/utils.hpp"

using Manifold = utils::Grid2D<std::uint8_t>;
using Pos = utils::Vec2<std::size_t>;

SOLUTION(2025, 07, (std::pair<std::uint32_t, std::uint64_t>), (std::uint32_t), (std::uint64_t))

std::pair<std::uint32_t, std::uint64_t> aoc2025::day07::parse_input_file(const std::filesystem::path &input_path) {
    Manifold manifold;
    Pos emitter_pos;
    for (const auto &[y, line] : utils::iter_file_lines(input_path) | std::views::enumerate) {
        std::vector<std::uint8_t> row;
        row.reserve(line.size());
        for (const auto &[x, c] : line | std::views::enumerate) {
            if (c == 'S') emitter_pos = Pos(x, y);
            row.emplace_back(c == '^');
        }
        manifold.add_row(row);
    }

    std::uint32_t p1_ans = 0;

    utils::Grid2D<std::uint64_t> timeline_counts(manifold.width(), manifold.height());
    timeline_counts[emitter_pos] = 1;

    std::unordered_set beam_heads = {emitter_pos};
    do {
        std::unordered_set<Pos> new_beam_heads;
        for (const auto &head : beam_heads) {
            const auto next_pos = Pos(head.x, head.y + 1);
            if (!manifold.in_bounds(next_pos)) continue;
            if (manifold[Pos(next_pos)]) {
                p1_ans++;
                new_beam_heads.emplace(next_pos.x - 1, next_pos.y);
                new_beam_heads.emplace(next_pos.x + 1, next_pos.y);
                timeline_counts[Pos(next_pos.x - 1, next_pos.y)] += timeline_counts[head];
                timeline_counts[Pos(next_pos.x + 1, next_pos.y)] += timeline_counts[head];
            } else {
                new_beam_heads.emplace(next_pos);
                timeline_counts[Pos(next_pos)] += timeline_counts[head];
            }
        }
        std::swap(beam_heads, new_beam_heads);
    } while (!beam_heads.empty());

    std::uint64_t p2_ans = 0;
    for (std::size_t x = 0; x < manifold.width(); ++x) p2_ans += timeline_counts[Pos(x, timeline_counts.height() - 1)];

    return {p1_ans, p2_ans};
}

std::uint32_t aoc2025::day07::p1(std::pair<std::uint32_t, std::uint64_t> &input) { return std::get<0>(input); }

std::uint64_t aoc2025::day07::p2(std::pair<std::uint32_t, std::uint64_t> &input) { return std::get<1>(input); }
