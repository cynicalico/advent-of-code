#include "fmt/format.h"
#include <cstdlib>
#include <fstream>
#include <utility>
#include <vector>

enum class RotationDir { Left, Right };

struct Rotation {
    RotationDir dir;
    int amount;
};

std::vector<Rotation> parse_input_file();
int p1(const std::vector<Rotation> &rotations);
int p2(const std::vector<Rotation> &rotations);

int main(int, char *[]) {
    try {
        const auto rotations = parse_input_file();
        fmt::print("P1: {}\n", p1(rotations));
        fmt::print("P2: {}\n", p2(rotations));
    } catch (const std::runtime_error &e) {
        fmt::print("ERROR: {} \n", e.what());
    }

    return 0;
}

std::vector<Rotation> parse_input_file() {
    std::vector<Rotation> rotations;

    std::ifstream ifs("input/day1.txt");
    if (!ifs.is_open()) throw std::runtime_error("Failed to open input file: input/day1.txt\n");

    std::string line;
    while (std::getline(ifs, line)) {
        const auto amount = std::strtol(line.c_str() + 1, nullptr, 10);
        switch (line[0]) {
        case 'L':
            rotations.emplace_back(RotationDir::Left, amount);
            break;
        case 'R':
            rotations.emplace_back(RotationDir::Right, amount);
            break;
        default:
            std::unreachable();
        }
    }

    return rotations;
}

int mod(const int a, const int b) {
    int r = a % b;
    if (std::signbit(r) != std::signbit(b)) r += b;
    return r;
}

int p1(const std::vector<Rotation> &rotations) {
    int ans = 0;

    int position = 50;
    for (const auto &rotation : rotations) {
        switch (rotation.dir) {
        case RotationDir::Left:
            position = mod(position - rotation.amount, 100);
            break;
        case RotationDir::Right:
            position = mod(position + rotation.amount, 100);
            break;
        }

        if (position == 0) ans++;
    }

    return ans;
}

int p2(const std::vector<Rotation> &rotations) {
    int ans = 0;

    int position = 50;
    for (const auto &rotation : rotations) {
        ans += rotation.amount / 100;

        const int prev_position = position;
        switch (rotation.dir) {
        case RotationDir::Left:
            position = mod(position - rotation.amount, 100);
            if (position != 0 && prev_position != 0 && prev_position < position) ans++;
            break;
        case RotationDir::Right:
            position = mod(position + rotation.amount, 100);
            if (position != 0 && prev_position != 0 && prev_position > position) ans++;
            break;
        }

        if (position == 0) ans++;
    }

    return ans;
}