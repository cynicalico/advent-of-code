/* Day 4: Printing Department
 * https://adventofcode.com/2025/day/4
 */

#include "utils/base.hpp"

using Grid = aoc2025::utils::Grid2D<std::int32_t>;
using Pos = aoc2025::utils::Vec2<std::int32_t>;

SOLUTION(2025, 04, (Grid), (std::uint32_t), (std::uint32_t))

Grid aoc2025::day04::parse_input_file() {
    const auto input = utils::iter_file_lines(INPUT_FILENAME) | std::ranges::to<std::vector>();
    auto grid = Grid(input[0].size(), input.size());
    for (const auto &[y, line] : std::views::enumerate(input)) {
        for (const auto &[x, c] : std::views::enumerate(line)) {
            const auto p = utils::Vec2<std::int32_t>(x, y);
            switch (input[y][x]) {
            case '.': grid[p] = -1; break;
            case '@':
                for (const auto &op : utils::moore_neighborhood_seq(p))
                    if (grid.in_bounds(op) && input[op.y][op.x] == '@') grid[p]++;
                break;
            default: std::unreachable();
            }
        }
    }
    return grid;
}

std::uint32_t aoc2025::day04::p1(Grid &input) {
    return std::ranges::count_if(utils::grid_seq<std::size_t>(input),
                                 [&input](const auto &p) { return input[p] >= 0 && input[p] < 4; });
}

std::uint32_t aoc2025::day04::p2(Grid &input) {
    std::uint32_t ans = 0;
    bool moved_roll;
    do {
        moved_roll = false;
        for (const auto &p : utils::grid_seq<std::int32_t>(input)) {
            if (input[p] >= 0 && input[p] < 4) {
                ans++;
                input[p] = -1;
                moved_roll = true;
                for (const auto &op : utils::moore_neighborhood_seq(p))
                    if (input.in_bounds(op)) --input[op];
            }
        }
    } while (moved_roll);
    return ans;
}
