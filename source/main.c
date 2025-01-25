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
/* #include <math.h> */

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

int error_handler(Display *display, XErrorEvent *event) {
    // TODO: Handle error handling //
    return 0;
}

void wm_init(int argc, char *argv[]) {
  handle_args(argc, argv);
  checkotherwm();
  setup();

  XSetErrorHandler(error_handler);
  scan();
  run();
  cleanup();
  XCloseDisplay(dpy);
}
