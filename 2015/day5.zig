// Day 5: Doesn't He Have Intern-Elves For This?
// https://adventofcode.com/2015/day/5

const std = @import("std");

const io_utils = @import("utils/io.zig");
const parse_utils = @import("utils/parsing.zig");

var stdout_buffer: [1024]u8 = undefined;

fn is_nice_p1(string: []u8) bool {
    var vowel_count: u32 = 0;
    var has_double_letter = false;
    var has_no_banned_strings = true;

    for (0..string.len, 1..) |i, j| {
        const a = string[i];

        if (a == 'a' or a == 'e' or a == 'i' or a == 'o' or a == 'u')
            vowel_count += 1;

        if (j < string.len) {
            const b = string[j];

            if (a == b)
                has_double_letter = true;

            if ((a == 'a' and b == 'b') or
                (a == 'c' and b == 'd') or
                (a == 'p' and b == 'q') or
                (a == 'x' and b == 'y'))
                has_no_banned_strings = false;
        }
    }

    return vowel_count >= 3 and has_double_letter and has_no_banned_strings;
}

fn is_nice_p2(string: []u8) bool {
    _ = string;
    return false;
}

pub fn main() !void {
    var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
    const stdout = &stdout_writer.interface;

    var file = try std.fs.cwd().openFile("input/5_1.txt", .{});
    defer file.close();

    var p1_ans: u32 = 0;
    var p2_ans: u32 = 0;

    var buffer: [1024]u8 = undefined;
    var lines = io_utils.FileLineIterator.init(file, &buffer);

    while (try lines.next()) |line| {
        if (is_nice_p1(line)) p1_ans += 1;
        if (is_nice_p2(line)) p2_ans += 1;
    }

    try stdout.print("P1: {}\n", .{p1_ans});
    try stdout.print("P2: {}\n", .{p2_ans});
    try stdout.flush();
}
