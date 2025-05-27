const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{}); // Any target is allowed and default is native

    // allow the person running `zig build` to select between
    // - Debug,        -ReleaseSafe,
    // - ReleaseFast,  - ReleaseSmall.
    const optimize = b.standardOptimizeOption(.{});

    const root_src = b.path("app");

    const bloom_exe = b.addExecutable(.{
        .name = "Bloom",
        .root_module = null,
        .target = target,
        .optimize = optimize,
    });

    bloom_exe.linkLibC();
    bloom_exe.linkLibCpp();
    bloom_exe.addIncludePath(b.path("app"));

    {
        var root_dir = try std.fs.cwd().openDir("app", .{ .iterate = true });
        defer root_dir.close();

        var walker = try root_dir.walk(b.allocator);
        defer walker.deinit();

        while (try walker.next()) |fs_entry| {
            if (fs_entry.kind == .file and (std.mem.endsWith(u8, fs_entry.basename, ".cpp") or std.mem.endsWith(u8, fs_entry.basename, ".c"))) {
                bloom_exe.addCSourceFile(.{
                    .file = try root_src.join(b.allocator, fs_entry.path),
                });
            }
        }
    }

    // This creates another `std.Build.Step.Compile`, but this one builds an executable
    // rather than a static library.
    // This declares intent for the executable to be installed into the
    // standard location when the user invokes the "install" step (the default
    // step when running `zig build`).
    b.installArtifact(bloom_exe);

    // This *creates* a Run step in the build graph, to be executed when another
    // step is evaluated that depends on it. The next line below will establish
    // such a dependency.
    const run_cmd = b.addRunArtifact(bloom_exe);
    // By making the run step depend on the install step, it will be run from the
    // installation directory rather than directly from within the cache directory.
    // This is not necessary, however, if the application depends on other installed
    // files, this ensures they will be present and in the expected location.
    run_cmd.step.dependOn(b.getInstallStep());

    // This allows the user to pass arguments to the application in the build
    // command itself, like this: `zig build run -- arg1 arg2 etc`
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    // This creates a build step. It will be visible in the `zig build --help` menu,
    // and can be selected like this: `zig build run`
    // This will evaluate the `run` step rather than the default, which is "install".
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
