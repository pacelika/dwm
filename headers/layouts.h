#pragma once

#include <X11/X.h>
#include <X11/keysym.h>
#include <commands.h>
#include <config.h>
#include <def.h>
#include <wm_def.c>
#include <wm_func_def.h>

/* function declarations */
static const Layout layouts[3] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};
