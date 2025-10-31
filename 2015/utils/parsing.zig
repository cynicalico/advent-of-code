const std = @import("std");

pub fn UnsignedIterator(comptime T: type) type {
    const info = @typeInfo(T);
    if (info != .int or info.int.signedness == .signed)
        @compileError("T must be one of u8, u16, u32, u64, u128, or usize");

    return struct {
        input: []u8,
        index: usize = 0,

        pub fn init(input: []u8) UnsignedIterator(T) {
            return .{ .input = input };
        }

        pub fn next(self: *UnsignedIterator(T)) ?T {
            while (self.index < self.input.len and !std.ascii.isDigit(self.input[self.index])) : (self.index += 1) {}
            if (self.index >= self.input.len) return null;

            var acc: T = 0;
            while (self.index < self.input.len and std.ascii.isDigit(self.input[self.index])) : (self.index += 1) {
                acc *= 10;
                acc += self.input[self.index] - '0';
            }
            return acc;
        }
    };
}
