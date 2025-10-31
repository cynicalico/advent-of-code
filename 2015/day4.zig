// Day 4: The Ideal Stocking Stuffer
// https://adventofcode.com/2015/day/4

const std = @import("std");

var stdout_buffer: [1024]u8 = undefined;

pub fn main() !void {
    var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
    const stdout = &stdout_writer.interface;

    var file = try std.fs.cwd().openFile("input/4_1.txt", .{});
    defer file.close();

    var candidate: u32 = 1;
    var p1_ans: u32 = 0;
    var p2_ans: u32 = 0;

    var read_buffer: [64]u8 = undefined;
    var file_reader = file.reader(&read_buffer);
    const reader = &file_reader.interface;
    const prefix_len = try file_reader.getSize();
    const prefix = try reader.take(prefix_len);

    var buffer: [64]u8 = undefined;
    @memmove(buffer[0..prefix_len], prefix);
    var md5_result: [16]u8 = undefined;

    while (true) {
        var n = candidate;
        const n_len = @as(usize, @intFromFloat(@floor(@log10(@as(f32, @floatFromInt(n)))))) + 1;
        var offset = n_len;
        while (n != 0) : (offset -= 1) {
            buffer[prefix_len - 1 + offset] = @as(u8, @truncate(n % 10)) + '0';
            n /= 10;
        }
        std.crypto.hash.Md5.hash(buffer[0 .. prefix_len + n_len], md5_result[0..], .{});

        if (p1_ans == 0 and
            md5_result[0] == 0 and
            md5_result[1] == 0 and
            md5_result[2] >> 4 == 0)
            p1_ans = candidate;

        if (md5_result[0] == 0 and
            md5_result[1] == 0 and
            md5_result[2] == 0)
            p2_ans = candidate;

        if (p1_ans != 0 and p2_ans != 0) break;

        candidate += 1;
    }

    try stdout.print("P1: {}\n", .{p1_ans});
    try stdout.print("P2: {}\n", .{p2_ans});
    try stdout.flush();
}
