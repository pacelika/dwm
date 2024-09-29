commands = {
	program_launcher = {
		"rofi",
		"-show",
		"run",
	},
	terminal = {
		"kitty",
	},
}

keys = {
	{ modifier = key_SUPER, key = key_d, func = "spawn", arg = { v = commands.program_launcher } },
	{ modifier = key_SUPER, key = key_Return, func = "spawn", arg = { v = commands.terminal } },
	{ modifier = key_SUPER, key = key_q, func = "killclient", arg = { v = commands.program_launcher } },

	{ modifier = key_SUPER_SHIFT, key = key_r, func = "reload_dwm" },
	{ modifier = key_SUPER_SHIFT, key = key_q, func = "quit" },
	{ modifier = key_SUPER_SHIFT, key = key_space, func = "togglefloating" },

	{ modifier = key_SUPER, key = key_j, func = "focusstack", arg = { i = 1 } },
	{ modifier = key_SUPER, key = key_k, func = "focusstack", arg = { i = -1 } },

	{ modifier = key_SUPER, key = key_h, func = "setmfact", arg = { f = -0.05 } },
	{ modifier = key_SUPER, key = key_l, func = "setmfact", arg = { f = 0.05 } },

	{ modifier = key_SUPER_SHIFT, key = key_Return, func = "zoom" },
	{ modifier = key_SUPER, key = key_Tab, func = "view" },

	{ modifier = key_SUPER, key = key_Left, func = "focusmon", { i = -1 } },
	{ modifier = key_SUPER, key = key_Right, func = "focusmon", { i = 1 } },

	{ modifier = key_SUPER_SHIFT, key = key_j, func = "tagmon", { i = -1 } },
	{ modifier = key_SUPER_SHIFT, key = key_k, func = "tagmon", { i = 1 } },
}

function _dwm_init() end

function _dwm_reload() end

function _dwm_terminate(ok) end
