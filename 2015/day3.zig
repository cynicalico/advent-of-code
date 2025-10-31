// Day 3: Perfectly Spherical Houses in a Vacuum
// https://adventofcode.com/2015/day/3

const std = @import("std");

const io_utils = @import("utils/io.zig");
const types = @import("utils/types.zig");
const Direction = types.Direction;
const Vec2 = types.Vec2;

var stdout_buffer: [1024]u8 = undefined;

fn move_santa(position: *Vec2, c: u8) void {
    switch (c) {
        '^' => position.*.move(.north),
        'v' => position.*.move(.south),
        '>' => position.*.move(.east),
        '<' => position.*.move(.west),
        else => unreachable,
    }
}

pub fn main() !void {
    var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
    const stdout = &stdout_writer.interface;

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var file = try std.fs.cwd().openFile("input/3_1.txt", .{});
    defer file.close();

    var santa_pos = Vec2.init(0, 0);
    var p1_locations = std.hash_map.AutoHashMap(Vec2, void).init(allocator);
    try p1_locations.put(santa_pos, {});

    var non_robo_santa_pos = Vec2.init(0, 0);
    var robot_santa_pos = Vec2.init(0, 0);
    var robo_santa_moving = false;
    var p2_locations = std.hash_map.AutoHashMap(Vec2, void).init(allocator);
    try p2_locations.put(non_robo_santa_pos, {});

    var buffer: [1024]u8 = undefined;
    var chars = io_utils.FileCharIterator.init(file, &buffer);

    while (try chars.next()) |c| {
        // P1
        move_santa(&santa_pos, c);
        try p1_locations.put(santa_pos, {});

        // P2
        if (robo_santa_moving) {
            move_santa(&robot_santa_pos, c);
            try p2_locations.put(robot_santa_pos, {});
        } else {
            move_santa(&non_robo_santa_pos, c);
            try p2_locations.put(non_robo_santa_pos, {});
        }
        robo_santa_moving = !robo_santa_moving;
    }

    const p1_ans = p1_locations.count();
    const p2_ans = p2_locations.count();

    try stdout.print("P1: {}\n", .{p1_ans});
    try stdout.print("P2: {}\n", .{p2_ans});
    try stdout.flush();
}
