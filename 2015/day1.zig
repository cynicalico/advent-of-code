// Day 1: Not Quite Lisp
// https://adventofcode.com/2015/day/1

const std = @import("std");

var stdout_buffer: [1024]u8 = undefined;
var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
const stdout = &stdout_writer.interface;

pub fn main() !void {
    const cwd = std.fs.cwd();
    var input = try cwd.openFile("input/1_1.txt", .{});
    defer input.close();

    var p1_ans: i32 = 0;
    var p2_ans: usize = 0;
    var seeking_basement: bool = true;

    var input_buffer: [1024]u8 = undefined;
    var bytes_read: usize = undefined;
    while (true) {
        bytes_read = try input.read(&input_buffer);
        if (bytes_read == 0) break;

        for (input_buffer[0..bytes_read]) |c| {
            switch (c) {
                '(' => {
                    p1_ans += 1;
                },
                ')' => {
                    p1_ans -= 1;
                },
                else => unreachable,
            }

            if (seeking_basement) {
                p2_ans += 1;
                if (p1_ans < 0) {
                    seeking_basement = false;
                }
            }
        }
    }

    try stdout.print("P1: {}\n", .{p1_ans});
    try stdout.print("P2: {}\n", .{p2_ans});
    try stdout.flush();
}
