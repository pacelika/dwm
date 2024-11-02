#pragma once

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, 0}                    \
  }

static char dmenumon[2] ="0"; /* component of dmenucmd, manipulated in spawn() */

static const char *COMMAND_PROGRAM_LAUNCHER[] = {"rofi", "-show", "run", 0};
static const char *COMMAND_TERMINAL[] = {"kitty", 0};
static const char *COMMAND_SCREENSHOT[] = {"flameshot","gui", 0};
