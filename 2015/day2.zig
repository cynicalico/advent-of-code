// Day 2: I Was Told There Would Be No Math
// https://adventofcode.com/2015/day/2

const std = @import("std");

const io_utils = @import("utils/io.zig");
const parse_utils = @import("utils/parsing.zig");

var stdout_buffer: [1024]u8 = undefined;

pub fn main() !void {
    var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
    const stdout = &stdout_writer.interface;

    var file = try std.fs.cwd().openFile("input/2_1.txt", .{});
    defer file.close();

    var p1_ans: u32 = 0;
    var p2_ans: u32 = 0;

    var buffer: [1024]u8 = undefined;
    var lines = io_utils.FileLineIterator.init(file, &buffer);

    while (try lines.next()) |line| {
        var dims = parse_utils.UnsignedIterator(u32).init(line);
        const l = dims.next() orelse unreachable;
        const w = dims.next() orelse unreachable;
        const h = dims.next() orelse unreachable;

        p1_ans += 2 * l * w + 2 * w * h + 2 * h * l; // surface area
        p1_ans += @min(l * w, w * h, h * l); // slack

        p2_ans += 2 * ((l + w + h) - @max(l, w, h)); // side distance
        p2_ans += l * w * h; // ribbon
    }

    try stdout.print("P1: {}\n", .{p1_ans});
    try stdout.print("P2: {}\n", .{p2_ans});
    try stdout.flush();
}
