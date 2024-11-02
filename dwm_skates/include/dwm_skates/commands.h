#pragma once

#include <dwm_skates/appearance.h>
#include <dwm_skates/def.h>
#include <dwm_skates/sk_def.h>

#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, SK_NULL }                    \
  }

static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *programlauncher_cmd[] = {"rofi", "-show", "run", SK_NULL};
static const char *termcmd[] = {"kitty", SK_NULL};
