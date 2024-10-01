#pragma once

#include <X11/Xft/Xft.h>

#include <dwm_skates/config.h>
#include <dwm_skates/drw.h>
#include <dwm_skates/macros.h>
#include <dwm_skates/source/config.c>
#include <dwm_skates/util.h>
#include <dwm_skates/wm_func_def.h>

#include <sk/lua/lauxlib.h>
#include <sk/lua/lua.h>
#include <sk/lua/lualib.h>

#define XINERAMA 1

#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */

static const char broken[] = "broken";
static char stext[256];
static int screen;
static int sw, sh; /* X display screen geometry width, height */
static int bh;     /* bar height */
static int lrpad;  /* sum of left and right padding for text */
static int (*xerrorxlib)(Display *, XErrorEvent *);
static unsigned int numlockmask = 0;
static void (*handler[LASTEvent])(XEvent *) = {
    [ButtonPress] = buttonpress,
    [ClientMessage] = clientmessage,
    [ConfigureRequest] = configurerequest,
    [ConfigureNotify] = configurenotify,
    [DestroyNotify] = destroynotify,
    [EnterNotify] = enternotify,
    [Expose] = expose,
    [FocusIn] = focusin,
    [KeyPress] = keypress,
    [MappingNotify] = mappingnotify,
    [MapRequest] = maprequest,
    [MotionNotify] = motionnotify,
    [PropertyNotify] = propertynotify,
    [UnmapNotify] = unmapnotify};
static Atom wmatom[WMLast], netatom[NetLast];
static int running = 1;
static Cur *cursor[CurLast];
static Clr **scheme;
static Display *dpy;
static Drw *drw;
static Monitor *mons, *selmon;
static Window root, wmcheckwin;

/* compile-time check if all tags fit into an unsigned int bit array. */
struct NumTags {
  char limitexceeded[LENGTH(tags) > 31 ? -1 : 1];
};

// My variables //
static lua_State *L = NULL;
static int dwm_reload_count = 0;
static char error_message[256] = {0};

#define EVENT_DWMHANDLED_KEYPRESS KeyPress + 32
