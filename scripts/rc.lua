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
}

dwm_fonts = {
	"monoscape:size=10",
}

dwm_colors = {
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

dwm_tags = {
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

dwm_keys = {
	{ modkey = key_super, key = key_d, func_name = "spawn", data = { argv = commands.program_launcher_main } },
	{ modkey = key_super, key = key_p, func_name = "spawn", data = { argv = commands.program_launcher_secondary } },
	{ modkey = key_super, key = key_Return, func_name = "spawn", data = { argv = commands.terminal } },
	{ modkey = key_super, key = key_q, func_name = "killclient" },

	{ modkey = key_super_shift, key = key_r, func_name = "reload_dwm" },
	{ modkey = key_super_shift, key = key_q, func_name = "quit" },
	{ modkey = key_super_shift, key = key_space, func_name = "togglefloating" },

	{ modkey = key_super, key = key_j, func_name = "focusstack", data = { argn = 1 } },
	{ modkey = key_super, key = key_k, func_name = "focusstack", data = { argn = -1 } },

	{ modkey = key_super, key = key_h, func_name = "setmfact", data = { argn = -0.05 } },
	{ modkey = key_super, key = key_l, func_name = "setmfact", data = { argn = 0.05 } },

	{ modkey = key_super_shift, key = key_Return, func = "zoom" },
	{ modkey = key_super, key = key_Tab, func_func = "view" },

	{ modkey = key_super, key = key_Left, func_name = "focusmon", data = { argn = -1 } },
	{ modkey = key_super, key = key_Right, func_name = "focusmon", data = { argn = 1 } },

	{ modkey = key_super_shift, key = key_j, func_name = "tagmon", data = { argn = -1 } },
	{ modkey = key_super_shift, key = key_k, func_name = "tagmon", data = { argn = 1 } },
}

function _dwm_init() end

function _dwm_reload() end

function _dwm_terminate(ok) end
