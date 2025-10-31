pub const Direction = enum { north, south, east, west };

pub const Vec2 = struct {
    x: i32,
    y: i32,

    pub fn init(x: i32, y: i32) Vec2 {
        return .{ .x = x, .y = y };
    }

    pub fn move(self: *Vec2, direction: Direction) void {
        switch (direction) {
            .north => self.y += 1,
            .south => self.y -= 1,
            .east => self.x -= 1,
            .west => self.x += 1,
        }
    }
};
