const std = @import("std");

pub const FileCharIterator = struct {
    file: std.fs.File,
    buffer: []u8,

    bytes_read: ?usize = null,
    index: usize = 0,

    pub fn init(file: std.fs.File, buffer: []u8) FileCharIterator {
        return .{ .file = file, .buffer = buffer };
    }

    pub fn next(self: *FileCharIterator) !?u8 {
        if (self.bytes_read == null or self.index == self.bytes_read) {
            self.bytes_read = try self.file.read(self.buffer);
            self.index = 0;
        }

        if (self.bytes_read == 0) return null; // sentinel, we have no more data

        const c = self.buffer[self.index];
        self.index += 1;
        return c;
    }
};

pub const FileLineIterator = struct {
    file: std.fs.File,
    buffer: []u8,
    reader: std.fs.File.Reader,

    pub fn init(file: std.fs.File, buffer: []u8) FileLineIterator {
        return .{ .file = file, .buffer = buffer, .reader = file.reader(buffer) };
    }

    pub fn next(self: *FileLineIterator) !?[]u8 {
        if (self.reader.interface.takeDelimiterExclusive('\n')) |line| {
            self.reader.interface.toss(1);
            return line;
        } else |err| return if (err == error.EndOfStream) null else err;
    }
};

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
