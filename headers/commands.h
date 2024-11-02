#pragma once

#include <def.h>
#include <sk_def.h>

#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, 0}                    \
  }

static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *COMMAND_PROGRAM_LAUNCHER[] = {"rofi", "-show", "run", 0};
static const char *COMMAND_TERMINAL[] = {"kitty", 0};
static const char *COMMAND_SCREENSHOT[] = {"flameshot","gui", 0};
