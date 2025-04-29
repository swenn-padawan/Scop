const std = @import("std");
const print = std.debug.print;
const linux = std.os.linux;

const NB_IDENTIFIERS = 3;

const map_flags = linux.MAP{
    .TYPE = .PRIVATE,
};

const vertex = extern struct { //extern keyword is require for the C memory compatibility
    x:*f16,
    y:*f16,
    z:*f16,
    w:*f16,
};


const ids: [NB_IDENTIFIERS][]const u8 = [_][]const u8{ "v", "vf", "f"};

const flags: u32 = @bitCast(map_flags);

fn checkId(line: []const u8) bool {
    if (line.len == 0 or line[0] == '#') return false;
    if (std.mem.indexOfScalar(u8, line, ' ')) |id_pos|{
        const id = line[0..id_pos] ;
        for (ids) |know_id| {
            if (std.mem.eql(u8, id, know_id))
                return (true);
            }
        return false;
    }
    else return false;
}

fn parseLine(line: []u8) void {
    if (!checkId(line)){
        print("PARSING ERROR at [{s}]\n", .{line});
    }else
        print("{s}\n", .{line});
}

pub fn main() !void {
    const   cwd = std.fs.cwd();
    const   file = try cwd.openFile("ressources/42.obj", .{ .mode = .read_only});
    defer   file.close();
    const   stat = try file.stat();
    const   ptr = linux.mmap(null, stat.size, linux.PROT.READ, map_flags, file.handle, 0);
    const   ptr_char: [*:0]u8 = @ptrFromInt(ptr);
    const   slice = ptr_char[0..std.mem.len(ptr_char)];
    var     index:usize = 0;

    while (index < slice.len){
        const rest = slice[index..];
        if (std.mem.indexOfScalar(u8, rest,'\n')) |rel_pos|{
            const line = rest[0..rel_pos];
            parseLine(line);

            index += rel_pos + 1;
        }else {
            parseLine(rest);
            break;
        }
    }
    _ = linux.munmap(ptr_char, stat.size);
}
