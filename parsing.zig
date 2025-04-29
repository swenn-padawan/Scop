const std = @import("std");
const linux = std.os.linux;

const NB_IDENTIFIERS = 2;

const map_flags = linux.MAP{
    .TYPE = .PRIVATE,
};

const ids: [NB_IDENTIFIERS][]const u8 = [_][]const u8{ "v", "vf" };

const flags: u32 = @bitCast(map_flags);

fn checkId(id: [:0]const u8) bool {
    for (ids) |know_id| {
        if (std.mem.eql(u8, id, know_id))
            return (true);
    }
    return (false);
}

pub fn main() !void {
    const file = try std.fs.openFileAbsolute("/nfs/homes/stetrel/42Spe/Scop/objs/Cube.obj", .{ .mode = .read_only });
    defer file.close();
    const stat = try file.stat();
    const ptr = linux.mmap(null, stat.size, linux.PROT.READ, map_flags, file.handle, 0);
    const ptr_char: [*:0]u8 = @ptrFromInt(ptr);
    const slice = ptr_char[0..std.mem.len(ptr_char)];

    if (std.mem.indexOfScalar(u8, slice, '~')) |pos| {
        std.debug.print("{c}\n", .{ptr_char[pos]});
    } else std.debug.print("char not found", .{});

    _ = linux.munmap(ptr_char, stat.size);
}
