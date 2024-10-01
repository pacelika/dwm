#pragma once
#include <dwm_skates/source/globals.c>

void focusstack(const Arg *arg) {
  Client *c = NULL, *i;

  if (!selmon->sel || (selmon->sel->isfullscreen && lockfullscreen))
    return;
  if (arg->i > 0) {
    for (c = selmon->sel->next; c && !ISVISIBLE(c); c = c->next)
      ;
    if (!c)
      for (c = selmon->clients; c && !ISVISIBLE(c); c = c->next)
        ;
  } else {
    for (i = selmon->clients; i != selmon->sel; i = i->next)
      if (ISVISIBLE(i))
        c = i;
    if (!c)
      for (; i; i = i->next)
        if (ISVISIBLE(i))
          c = i;
  }
  if (c) {
    focus(c);
    restack(selmon);
  }
}

void detachstack(Client *c) {
  Client **tc, *t;

  for (tc = &c->mon->stack; *tc && *tc != c; tc = &(*tc)->snext)
    ;
  *tc = c->snext;

  if (c == c->mon->sel) {
    for (t = c->mon->stack; t && !ISVISIBLE(t); t = t->snext)
      ;
    c->mon->sel = t;
  }
}

void attachstack(Client *c) {
  c->snext = c->mon->stack;
  c->mon->stack = c;
}

void restack(Monitor *m) {
  Client *c;
  XEvent ev;
  XWindowChanges wc;

  drawbar(m);
  if (!m->sel)
    return;
  if (m->sel->isfloating || !m->lt[m->sellt]->arrange)
    XRaiseWindow(dpy, m->sel->win);
  if (m->lt[m->sellt]->arrange) {
    wc.stack_mode = Below;
    wc.sibling = m->barwin;
    for (c = m->stack; c; c = c->snext)
      if (!c->isfloating && ISVISIBLE(c)) {
        XConfigureWindow(dpy, c->win, CWSibling | CWStackMode, &wc);
        wc.sibling = c->win;
      }
  }
  XSync(dpy, False);
  while (XCheckMaskEvent(dpy, EnterWindowMask, &ev))
    ;
}

void movestack(const Arg *arg) {
  Client *c = NULL, *p = NULL, *pc = NULL, *i;

  if (arg->i > 0) {
    /* find the client after selmon->sel */
    for (c = selmon->sel->next; c && (!ISVISIBLE(c) || c->isfloating);
         c = c->next)
      ;
    if (!c)
      for (c = selmon->clients; c && (!ISVISIBLE(c) || c->isfloating);
           c = c->next)
        ;

  } else {
    /* find the client before selmon->sel */
    for (i = selmon->clients; i != selmon->sel; i = i->next)
      if (ISVISIBLE(i) && !i->isfloating)
        c = i;
    if (!c)
      for (; i; i = i->next)
        if (ISVISIBLE(i) && !i->isfloating)
          c = i;
  }
  /* find the client before selmon->sel and c */
  for (i = selmon->clients; i && (!p || !pc); i = i->next) {
    if (i->next == selmon->sel)
      p = i;
    if (i->next == c)
      pc = i;
  }

  /* swap c and selmon->sel selmon->clients in the selmon->clients list */
  if (c && c != selmon->sel) {
    Client *temp = selmon->sel->next == c ? selmon->sel : selmon->sel->next;
    selmon->sel->next = c->next == selmon->sel ? c : c->next;
    c->next = temp;

    if (p && p != c)
      p->next = c;
    if (pc && pc != selmon->sel)
      pc->next = selmon->sel;

    if (selmon->sel == selmon->clients)
      selmon->clients = c;
    else if (c == selmon->clients)
      selmon->clients = selmon->sel;

    arrange(selmon);
  }
}
