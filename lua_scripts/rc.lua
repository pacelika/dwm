local commands = {
	program_launcher_main = {
		"rofi",
		"-show",
		"run",
	},
	program_launcher_secondary = {
		"dmenu_run",
	},
	terminal = {
		"kitty",
	},
	screenshot_wholescreen = {
		"flameshot",
		"screen",
	},
	screenshot_select = {
		"flameshot",
		"gui",
	},
	file_manager = {
		"kitty",
		"-e",
		"yazi",
	},
}

DWM_fonts = {
	"monoscape:size=10",
}

DWM_colors = {
	normal = {
		fg = "#bbbbbb",
		bg = "#222222",
		border = "#444444",
	},
	selected = {
		fg = "#eeeeee",
		bg = "#005577",
		border = "#005577",
	},
}

DWM_tags = {
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
}

-- see default keymaps at https://github.com/pacelika/dwm_skates/dwm_skates/include/impl/config.c
DWM_keys = {
	{
		modmask = modmask_super,
		key = key_p,
		func_name = "spawn",
		data = { argv = commands.program_launcher_secondary },
	},
	{
		modmask = modmask_super,
		key = key_s,
		func_name = "spawn",
		data = { argv = commands.screenshot_select },
	},
	{
		modmask = modmask_super_shift,
		key = key_m,
		func_name = "spawn",
		data = { argv = commands.screenshot_wholescreen },
	},
	{
		modmask = modmask_super_shift,
		key = key_f,
		func_name = "spawn",
		data = { argv = commands.file_manager },
	},
	{
		modmask = modmask_super_shift,
		key = key_r,
		func_name = "reload_dwm",
	},
}

function _DWM_preinit() end
function _DWM_init() end
function _DWM_reload() end

function _DWM_event(event) end
function _DWM_client_spawned(client) end
function _DWM_client_killed(client) end

function _DWM_terminate() end
