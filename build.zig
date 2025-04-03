const std = @import("std");

pub fn build(b: *std.Build) void {
	const target = b.standardTargetOptions(.{});
	
	const exe = b.addExecutable(.{
		.name = "dwm",
		.target = target,
		.strip = true
	});

	exe.addIncludePath(.{.cwd_relative = "/usr/X11R6/include"});
	exe.addIncludePath(.{.cwd_relative = "/usr/include/freetype2"});
	exe.addIncludePath(b.path("headers"));
	exe.addIncludePath(b.path("source"));
	
	exe.addCSourceFiles(.{.root = b.path("source"),.files = &.{"config.c","drw.c","dwm.c","transient.c","util.c","main.c"}});
	exe.linkSystemLibrary("Xinerama");
	exe.linkSystemLibrary("fontconfig");
	exe.linkSystemLibrary("Xft");
	exe.linkSystemLibrary("X11");
	exe.linkSystemLibrary("m");

	b.installArtifact(exe);
}
