// Day 1: Not Quite Lisp
// https://adventofcode.com/2015/day/1

const std = @import("std");
const helpers = @import("helpers.zig");

var stdout_buffer: [1024]u8 = undefined;

pub fn main() !void {
    var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
    const stdout = &stdout_writer.interface;

    var p1_ans: i32 = 0;
    var p2_ans: usize = 0;
    var seeking_basement: bool = true;

    var file = try std.fs.cwd().openFile("input/1_1.txt", .{});
    defer file.close();

    var buffer: [1024]u8 = undefined;
    var iterator = helpers.FileCharIterator.init(file, &buffer);

    while (try iterator.next()) |c| {
        switch (c) {
            '(' => p1_ans += 1,
            ')' => p1_ans -= 1,
            else => unreachable,
        }

        if (seeking_basement) {
            p2_ans += 1;
            seeking_basement = p1_ans >= 0;
        }
    }

    try stdout.print("P1: {}\n", .{p1_ans});
    try stdout.print("P2: {}\n", .{p2_ans});
    try stdout.flush();
}
