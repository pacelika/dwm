#pragma once

#include <def.h>
#include "colors.h"

static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"monospace:size=10"};
static const char dmenufont[] = "monospace:size=10";

#ifdef SCHEME_NAME_PINK
static const char* const scheme_normal_fg = col_white;
static const char* const scheme_normal_bg = col_black;
static const char* const scheme_normal_border = col_black;

static const char* const scheme_sel_fg = col_black;
static const char* const scheme_sel_bg = col_pink;
static const char* const scheme_sel_border = col_pink;
#else
static const char* const scheme_normal_fg = col_gray3;
static const char* const scheme_normal_bg = col_gray1;
static const char* const scheme_normal_border = col_gray2;

static const char* const scheme_sel_fg = col_gray4;
static const char* const scheme_sel_bg = col_cyan;
static const char* const scheme_sel_border = col_cyan;
#endif

static const char *colors[2][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {scheme_normal_fg, scheme_normal_bg, scheme_normal_border},
    [SchemeSel] = {scheme_sel_fg, scheme_sel_bg, scheme_sel_border},
};

static const char *tags[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
