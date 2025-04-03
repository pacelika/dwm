const std = @import("std");

pub fn build(b: *std.Build) !void {
	const desktop_file_path = "/usr/share/xsessions/dwm.desktop";
	const libraries = [_][] const u8 {"Xinerama","fontconfig","Xft","X11","m"};
	const include_paths = [_][] const u8 {"/usr/X11R6/include","/usr/include/freetype2","headers","source"};
	
	const skip_file_check_option = b.option(bool,"skip-checks","skip the desktop file check") orelse false;
	const target = b.standardTargetOptions(.{});
	
	const install_step = b.step("install_bin","builds and installs the binary");
	const install_cmd = b.addSystemCommand(&.{"install", "-m", "755", "zig-out/bin/dwm", "/usr/local/bin/dwm"});
		
	const exe = b.addExecutable(.{
		.name = "dwm",
		.target = target,
		.strip = true
	});
	
	const cwd = std.fs.cwd();

	if (!skip_file_check_option) {
			const desktop_file = cwd.openFile(desktop_file_path,.{}) catch |err| switch(err) {
			std.posix.OpenError.FileNotFound => {
				std.debug.print("INFO: '{s}' desktop file does not exists\n",.{desktop_file_path});
				
				const created_file = cwd.createFile(desktop_file_path,.{}) catch |create_err| switch(create_err) {
					std.posix.OpenError.AccessDenied  => {
						std.debug.print("Error: Failed to create '{s}'. Zig must be ran as root\nWhat Error: {any}\n",.{desktop_file_path,create_err});
						std.debug.print("INFO: Running dependency checks. Hint: -Dskip-checks=true\n",.{});
						return;
					},
					else => {
						std.debug.print("Error: Failed to create '{s}'.\nWhat Error: {any}\n",.{desktop_file_path,create_err});
						std.debug.print("INFO: Running dependency checks. Hint: -Dskip-checks=true\n",.{});
						return;
					}
				};
				
				defer created_file.close();
				
				_ = try created_file.write("[Desktop Entry]\n");
				_ = try created_file.write("Name=dwm\n");
				_ = try created_file.write("Comment=Suckless dynamic window manager\n");
				_ = try created_file.write("Exec=dwm\n");
				_ = try created_file.write("Type=Aplication\n");
				
				std.debug.print("INFO: Successfully created desktop file '{s}'\n",.{desktop_file_path});
				return;
			},
			else => {
				std.debug.print("ERROR: something went wrong while trying to open {s}\nWhat Error: {any}\n",.{desktop_file_path,err});
				return;
			}
		};

		defer desktop_file.close();
	}
		
	for (libraries) |library| { exe.linkSystemLibrary(library); }
	for (include_paths) |path| { exe.addIncludePath(.{.cwd_relative = path}); }
	exe.addCSourceFiles(.{.root = b.path("source"),.files = &.{"config.c","drw.c","dwm.c","transient.c","util.c","main.c"}});
	
	b.default_step.dependOn(&exe.step);
	install_step.dependOn(&exe.step);
	install_step.dependOn(&install_cmd.step);
	
	b.installArtifact(exe);	
}
