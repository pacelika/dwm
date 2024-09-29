#pragma once

#include <X11/X.h>
#include <X11/keysym.h>
#include <dwm_skates/commands.h>
#include <dwm_skates/config.h>
#include <dwm_skates/def.h>
#include <dwm_skates/impl/wm_def.c>
#include <dwm_skates/wm_func_def.h>

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* function declarations */
static const Layout layouts[3] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

static Key keys[50] = {
    /* modifier                     key        function        argument */
    // {MODKEY, XK_g, spawn, {.v = programlauncher_cmd}},
    // {MODKEY, XK_Return, spawn, {.v = termcmd}},
    // {MODKEY | ShiftMask, XK_r, reload_dwm, {0}},
    // {MODKEY, XK_b, togglebar, {0}},
    // {MODKEY, XK_j, focusstack, {.i = +1}},
    // {MODKEY, XK_k, focusstack, {.i = -1}},
    // {MODKEY, XK_i, incnmaster, {.i = +1}},
    // {MODKEY, XK_p, incnmaster, {.i = -1}},
    // {MODKEY, XK_h, setmfact, {.f = -0.05}},
    // {MODKEY, XK_l, setmfact, {.f = +0.05}},
    // {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    // {MODKEY, XK_Tab, view, {0}},
    // {MODKEY, XK_q, killclient, {0}},
    // {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    // {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    // {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    // {MODKEY, XK_space, setlayout, {0}},
    // {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    // {MODKEY, XK_0, view, {.ui = ~0}},
    // {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    // {MODKEY, XK_comma, focusmon, {.i = -1}},
    // {MODKEY, XK_period, focusmon, {.i = +1}},
    // {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    // {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    // TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
    //     TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
    //         TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
    //
    // {MODKEY | ShiftMask, XK_q, quit, {0}}};
};

static Key tagkeys[9 * 4] = {TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2)
                                 TAGKEYS(XK_4, 3) TAGKEYS(XK_5, 4)
                                     TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6)
                                         TAGKEYS(XK_8, 7) TAGKEYS(XK_9, 8)};

static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
