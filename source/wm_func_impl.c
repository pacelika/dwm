#include <X11/X.h>
#include <X11/Xft/Xft.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#ifdef LUA_RC
#include <sk/lua/lauxlib.h>
#include <sk/lua/lua.h>
#include <sk/lua/lualib.h>
#endif

#include <wm_client.c>
#include <wm_event.c>
#include <wm_input.c>
#include <wm_monitor.c>
#include <wm_stack.c>
#include <wm_tile.c>

#include <globals.c>

void handle_args(int argc, char *argv[]) {
  if (argc == 2 && !strcmp("-v", argv[1]))
    die("dwm-" VERSION);
  else if (argc != 1)
    die("usage: dwm [-v]");
  if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
    fputs("warning: no locale support\n", stderr);
  if (!(dpy = XOpenDisplay(NULL)))
    die("dwm: cannot open display");
}

int is_stack_mem(const void *ptr) {
  int local_var;
  return (ptr > (void *)&local_var);
}

void set_tag_key(int *tag_c, int index, int *offset, unsigned int mod,
                 KeySym key, const void *func) {
  keys[index + *offset].keysym = key;
  keys[index + *offset].mod = mod;
  keys[index + *offset].func = func;
  keys[index + *offset].arg.ui = 1 << *tag_c;
  *offset += 1;
  *tag_c += 1;
}

void set_key_to_func(int index, int *offset, unsigned int mod, KeySym key,
                     const void *func) {

  int _offset = 0;

  if (offset != NULL) {
    _offset = *offset;
  }

  keys[index + _offset].keysym = key;
  keys[index + _offset].mod = mod;
  keys[index + _offset].func = func;

  if (offset != NULL) {
    *offset += 1;
  }
}

void set_key_to_command(int index, int *offset, unsigned int mod, KeySym key,
                        const void *func, const void *cmd) {
  int _offset = 0;

  if (offset != NULL) {
    _offset = *offset;
  }

  keys[index + _offset].keysym = key;
  keys[index + _offset].mod = mod;
  keys[index + _offset].func = func;
  keys[index + _offset].arg.v = cmd;

  if (offset != NULL) {
    *offset += 1;
  }
}

int load_default_keys(){
  int index = 0;

  // Finds the index where a func pointer is not set (NULL), and updates the index where it should start populating data
  for (int i = 0; i < LENGTH(keys); i++) {
    if (keys[i].func == NULL) {
      index = i;
      break;
    }
  }

  memcpy(&keys[index], default_keys, LENGTH(default_keys) * sizeof(Key));

  // Remove duplicate keys //
  for (int i = 0; i < LENGTH(keys); i++) {
    for (int j = i + 1; j < LENGTH(keys); j++) {
      if (keys[i].keysym == keys[j].keysym && keys[i].mod == keys[j].mod) {
        keys[j].mod = NoSymbol;
        keys[j].keysym = NoSymbol;
        keys[j].func = NULL;
        break;
      }
    }
  }

  return 0;
}

void set_func_ptr_by_name(Key *key, const char *func_name) {
  if (func_name == NULL)
    return;

  if (!strcmp(func_name, "spawn")) {
    key->func = spawn;
  }

  else if (!strcmp(func_name, "quit")) {
    key->func = quit;
  }

  /* else if (!strcmp(func_name, "reload_dwm")) { */
  /*   key->func = reload_dwm; */
  /* } */

  else if (!strcmp(func_name, "killclient")) {
    key->func = killclient;
  }

  else if (!strcmp(func_name, "setlayout")) {
    key->func = setlayout;
  }

  else if (!strcmp(func_name, "togglefloating")) {
    key->func = togglefloating;
  }

  else if (!strcmp(func_name, "setmfact")) {
    key->func = setmfact;
  }

  else if (!strcmp(func_name, "incnmaster")) {
    key->func = incnmaster;
  }

  else if (!strcmp(func_name, "focusstack")) {
    key->func = focusstack;
  }

  else if (!strcmp(func_name, "tagmon")) {
    key->func = tagmon;
  }

  else if (!strcmp(func_name, "focusmon")) {
    key->func = focusmon;
  }

  else if (!strcmp(func_name, "togglebar")) {
    key->func = togglebar;
  }

  else if (!strcmp(func_name, "movestack")) {
    key->func = movestack;
  }

  else if (!strcmp(func_name, "set_tile_vertical")) {
    key->func = set_tile_vertical;
  }

  else if (!strcmp(func_name, "set_tile_horizontal")) {
    key->func = set_tile_horizontal;
  }
}

int error_occured = 0;

int error_handler(Display *display, XErrorEvent *event) {
  error_occured = 1;
  return 0;
}

void wm_init(int argc, char *argv[]) {
#ifdef LUA_RC
  L = luaL_newstate();
  luaL_openlibs(L);

  set_lua_globals();
  run_lua_script();

  lua_getglobal(L, "_DWM_preinit");

  if (lua_isfunction(L, -1)) {
    lua_pcall(L, 0, 0, 0);
  }

  lua_pop(L, 1);

  if (load_tags_from_lua() == -1) {
    // TODO: Handle loading tags failure;
  }

  if (load_colors_from_lua() == -1) {
    // TODO: Handle loading colors failure;
  }

  if (load_keys_from_lua() == -1) {
    // TODO: Handle assigning keys failure //
  }
#endif

  handle_args(argc, argv);
  checkotherwm();

#ifndef LUA_RC
    load_default_keys();
#endif

  setup();

  XSetErrorHandler(error_handler);

#ifdef LUA_RC
  lua_getglobal(L, "_DWM_init");

  if (lua_isfunction(L, -1)) {
    lua_pcall(L, 0, 0, 0);
  }

  lua_pop(L, 1);
#endif

  scan();
  run();
  cleanup();
#ifdef LUA_RC
  lua_getglobal(L, "_DWM_terminate");

  if (lua_isfunction(L, -1)) {
    lua_pcall(L, 0, 0, 0);
  }

  lua_pop(L, 1);

  lua_close(L);
#endif
  XCloseDisplay(dpy);
}

int has_interval_passed(int interval) {
  static time_t last_execution_time = 0;
  time_t current_time = time(NULL);

  if (current_time - last_execution_time >= interval) {
    last_execution_time = current_time;
    return 1;
  }

  return 0;
}

#ifdef LUA_RC
int load_keys_from_lua() {
  lua_getglobal(L, "DWM_keys");

  if (lua_isnil(L,-1)) {
    int _ = load_default_keys();
    return 0;
  }

  if (!lua_istable(L, -1) && !lua_isnil(L,-1)) {
    int _ = load_default_keys();
    return -1;
  }

  int keys_len = luaL_len(L, -1);

  if (keys_len == 0) {
    int _ = load_default_keys();
    return 0;
  }

  for (int i = 1; i <= keys_len; ++i) {
    lua_pushinteger(L, i);
    lua_gettable(L, -2);

    Key *key = &keys[i - 1];

    if (lua_istable(L, -1)) {
      lua_getfield(L, -1, "modmask");

      if (lua_isnumber(L, -1)) {
        key->mod = (unsigned int)lua_tointeger(L, -1);
      }

      lua_pop(L, 1);

      lua_getfield(L, -1, "key");

      if (lua_isnumber(L, -1)) {
        key->keysym = XKeycodeToKeysym(dpy, lua_tointeger(L, -1), 0);
      }

      // pop key
      lua_pop(L, 1);

      lua_getfield(L, -1, "func_name");

      if (lua_isstring(L, -1)) {
        const char *func_name = lua_tostring(L, -1);
        set_func_ptr_by_name(key, func_name);
      }

      // pop func_name
      lua_pop(L, 1);

      lua_getfield(L, -1, "data");

      if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "argv");

        if (lua_istable(L, -1)) {
          int command_length = luaL_len(L, -1);

          if (command_length == 0) {
            strcpy(error_message, "command length is 0");
            return -1;
          }

          if (key->arg.v != NULL) {
            free((void *)key->arg.v);
            key->arg.v = NULL;
          }

          key->arg.v = malloc(sizeof(const char *) * (command_length + 1));

          if (key->arg.v == NULL) {
            strcpy(error_message, "Failed to allocate memory for key");
            return SK_ACTION_FAILURE;
          }

          for (int command_index = 1; command_index <= command_length;
               ++command_index) {
            if (!lua_istable(L, -1)) {
              strcpy(error_message, "[Error] command is not a table");
              continue;
            }
            lua_rawgeti(L, -1, command_index);

            if (lua_isstring(L, -1)) {
              const char *cmd = lua_tostring(L, -1);
              ((const char **)(key->arg.v))[command_index - 1] = strdup(cmd);
            } else {
              ((const char **)(key->arg.v))[command_index - 1] = NULL;
              strcpy(error_message,
                     "Could not append to command, must be a string");
              break;
            }
            // pop rawget ref //
            lua_pop(L, 1);
          }

          ((const char **)(key->arg.v))[command_length] = NULL;
        }

        // pop data table //
        lua_pop(L, 1);

        lua_getfield(L, -1, "argn");

        if (lua_isnumber(L, -1)) {
          double int_s;
          double number = lua_tonumber(L, -1);

          if (modf(number, &int_s) == 0.0) {
            key->arg.i = (int)number;
          } else {
            key->arg.f = (float)number;
          }
        }
        // pop argn //
        lua_pop(L, 1);

        lua_getfield(L, -1, "argun");

        if (lua_isnumber(L, -1)) {
          key->arg.ui = (unsigned int)lua_tonumber(L, -1);
        }

        // pop argun
        lua_pop(L, 1);
      }
      lua_pop(L, 1);
    }

    lua_pop(L, 1);
  }

  load_default_keys();
  return 0;
}

void set_lua_globals() {
  if (dpy == NULL) {
    printf("Unable to open display\n");
    return;
  }

  int min_keycode, max_keycode;
  XDisplayKeycodes(dpy, &min_keycode, &max_keycode);

  for (int keycode = min_keycode; keycode <= max_keycode; ++keycode) {
    KeySym keysym = XKeycodeToKeysym(dpy, keycode, 0);
    if (keysym != NoSymbol) {
      char *name = XKeysymToString(keysym);
      char buffer[100];
      sprintf(buffer, "key_%s", name);
      lua_pushinteger(L, keycode);
      lua_setglobal(L, buffer);
    }
  }

  lua_pushinteger(L, MODKEY | ShiftMask);
  lua_setglobal(L, "modmask_super_shift");

  lua_pushinteger(L, MODKEY | ShiftMask | ControlMask);
  lua_setglobal(L, "modmask_super_control_shift");

  lua_pushinteger(L, MODKEY);
  lua_setglobal(L, "modmask_super");

  lua_pushinteger(L, EVENT_DWMHANDLED_KEYPRESS);
  lua_setglobal(L, "EVENT_DWMHANDLED_KEYPRESS");

  lua_pushinteger(L, KeyPress);
  lua_setglobal(L, "EVENT_KEYPRESS");
}

void run_lua_script(void) {
  if (L != NULL) {
    lua_close(L);
    L = luaL_newstate();
    luaL_openlibs(L);
    set_lua_globals();
  }

  const char *home_dir = getenv("HOME");

  if (home_dir == NULL) {
    fprintf(stderr, "Could not get home directory.\n");
    return;
  }

  char script_path[256];

  snprintf(script_path, sizeof(script_path), "%s/%s", home_dir,
           ".config/dwm/config.lua");

  int lua_has_error = luaL_dofile(L, script_path);

  if (lua_has_error) {
    checkotherwm();
    scan();
    cleanup();
  }
}

void reload_dwm(const Arg *arg) {
  run_lua_script();
  lua_getglobal(L, "_DWM_reload");

  if (lua_isfunction(L, -1)) {
    lua_pcall(L, 0, 0, 0);
  }

  for (int i = 0; i < LENGTH(keys); i++) {
    keys[i].func = NULL;
  }

  ungrabkeys(dpy, DefaultRootWindow(dpy));
  if (load_keys_from_lua() == -1) {
    // TODO: Handle reloading keys failure //
  }
  grabkeys();
  XSync(dpy, False);

  // TODO: reload tags and colors //
}

int load_colors_from_lua(void) {
  static int COLOR_FG = 0;
  static int COLOR_BG = 1;
  static int COLOR_BORDER = 2;

  if (L == NULL) {
    return -1;
  }

  lua_getglobal(L, "DWM_colors");

  if (lua_isnil(L,-1)) {
    lua_pop(L, 1);
    return 0;
  }

  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return -1;
  }

  lua_getfield(L, -1, "selected");

  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return -1;
  }

  lua_getfield(L, -1, "fg");

  if (lua_isstring(L, -1)) {
    colors[SchemeSel][COLOR_FG] = strdup(lua_tostring(L, -1));
  }
  // pops fg //
  lua_pop(L, 1);

  lua_getfield(L, -1, "bg");

  if (lua_isstring(L, -1)) {
    colors[SchemeSel][COLOR_BG] = strdup(lua_tostring(L, -1));
  }
  // pops bg //
  lua_pop(L, 1);

  lua_getfield(L, -1, "border");

  if (lua_isstring(L, -1)) {
    colors[SchemeSel][COLOR_BORDER] = strdup(lua_tostring(L, -1));
  }

  // pop border and selected table //
  lua_pop(L, 2);

  // back to dwm_colors

  lua_getfield(L, -1, "normal");

  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return -1;
  }

  lua_getfield(L, -1, "fg");

  if (lua_isstring(L, -1)) {
    colors[SchemeNorm][COLOR_FG] = strdup(lua_tostring(L, -1));
  }
  // pops fg //
  lua_pop(L, 1);

  lua_getfield(L, -1, "bg");

  if (lua_isstring(L, -1)) {
    colors[SchemeNorm][COLOR_BG] = strdup(lua_tostring(L, -1));
  }
  // pops bg //
  lua_pop(L, 1);

  lua_getfield(L, -1, "border");

  if (lua_isstring(L, -1)) {
    colors[SchemeNorm][COLOR_BORDER] = strdup(lua_tostring(L, -1));
  }
  lua_pop(L, 2); // pop border and normal table

  // pop dwm_colors
  lua_pop(L, 1);

  return 0;
}

int load_tags_from_lua(void) {
  if (L == NULL) {
    return -1;
  }

  lua_getglobal(L, "DWM_tags");

  if (lua_isnil(L,-1)) {
    lua_pop(L,1);
    return 0;
  }

  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return -1;
  }

  int len = luaL_len(L, -1);

  if (len > LENGTH(tags)) {
    len = LENGTH(tags);
  }

  for (int i = 1; i <= len; ++i) {
    lua_rawgeti(L, -1, i);

    if (!lua_isstring(L, -1)) {
      lua_pop(L, 1);
      break;
    }

    const char *tag_name = lua_tostring(L, -1);
    tags[i - 1] = strdup(tag_name);

    lua_pop(L, 1);
  }

  return 0;
}
#endif
