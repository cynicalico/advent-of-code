/* Day 9: Movie Theater
 * https://adventofcode.com/2025/day/9
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

using Pos = utils::Vec2<std::int64_t>;
using Grid = utils::Grid2D<char>;

SOLUTION(2025, 9, (std::vector<Pos>), (std::int64_t), (std::int64_t))

std::vector<Pos> AOC_NS(2025, 9)::parse_input(const std::filesystem::path &input_path) {
    return utils::iter_file_integer_tuples<std::int64_t, 2>(input_path) |
           std::views::transform([](const auto &t) { return Pos(std::get<0>(t), std::get<1>(t)); }) |
           std::ranges::to<std::vector>();
}

namespace AOC_NS(2025, 9) {
std::int64_t find_largest_rectangle(const std::vector<Pos> &input) {
    std::int64_t max = 0;
    for (std::size_t i = 0; i < input.size(); ++i)
        for (std::size_t j = i + 1; j < input.size(); ++j)
            max = std::max(max, (std::abs(input[j].x - input[i].x) + 1) * (std::abs(input[j].y - input[i].y) + 1));
    return max;
}

bool check_corners(const Grid &grid, const Pos &c1, const Pos &c2) {
    const auto c3 = Pos(c1.x, c2.y);
    const auto c4 = Pos(c2.x, c1.y);
    return grid[c3] != 0 && grid[c4] != 0;
}

bool all_red_or_green_edges(const Grid &grid, const Pos &c1, const Pos &c2) {
    const auto sx = std::min(c1.x, c2.x);
    const auto ex = std::max(c1.x, c2.x);
    const auto sy = std::min(c1.y, c2.y);
    const auto ey = std::max(c1.y, c2.y);
    for (std::size_t x = sx; x <= ex; ++x) {
        if (grid[Pos(x, sy)] == 0) return false;
        if (grid[Pos(x, ey)] == 0) return false;
    }
    for (std::size_t y = sy; y <= ey; ++y) {
        if (grid[Pos(sx, y)] == 0) return false;
        if (grid[Pos(ex, y)] == 0) return false;
    }
    return true;
}

std::int64_t find_largest_rectangle_colored(const Grid &grid, const std::vector<Pos> &input) {
    std::int64_t max = 0;
    for (std::size_t i = 0; i < input.size(); ++i) {
        for (std::size_t j = i + 1; j < input.size(); ++j) {
            const auto area = (std::abs(input[j].x - input[i].x) + 1) * (std::abs(input[j].y - input[i].y) + 1);
            if (area < max) continue;
            if (!check_corners(grid, input[i], input[j])) continue;
            if (all_red_or_green_edges(grid, input[i], input[j])) max = area;
        }
    }
    return max;
}
}

std::int64_t AOC_NS(2025, 9)::p1(std::vector<Pos> &input) { return find_largest_rectangle(input); }

std::int64_t AOC_NS(2025, 9)::p2(std::vector<Pos> &input) {
    const auto max_x = std::ranges::max(input, [](const auto &a, const auto &b) { return a.x < b.x; }).x;
    const auto max_y = std::ranges::max(input, [](const auto &a, const auto &b) { return a.y < b.y; }).y;
    auto grid = Grid(max_x + 1, max_y + 1);

    input.emplace_back(input[0]);
    for (const auto &[from, to] : input | std::views::adjacent<2>) {
        const auto sx = std::min(from.x, to.x);
        const auto ex = std::max(from.x, to.x);
        const auto sy = std::min(from.y, to.y);
        const auto ey = std::max(from.y, to.y);
        for (std::size_t y = sy; y <= ey; ++y)
            for (std::size_t x = sx; x <= ex; ++x) grid[Pos(x, y)] = 'X';
        grid[from] = '#';
        grid[to] = '#';
    }
    input.pop_back();

    for (std::size_t y = 0; y < grid.height(); ++y) {
        bool inside = false;
        for (std::size_t x = 0; x < grid.width(); ++x) {
            const auto p = Pos(x, y);
            if (!inside) {
                if (grid[p] == '#' || grid[p] == 'X') inside = true;
            } else if (inside) {
                if (grid[p] == 0) grid[p] = 'X';
                else if (grid[p] == 'X' || grid[p] == 'X') inside = false;
            }
        }
    }

    return find_largest_rectangle_colored(grid, input);
}
