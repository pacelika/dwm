#include <dwm_skates/source/globals.c>

void incnmaster(const Arg *arg) {
  selmon->nmaster = MAX(selmon->nmaster + arg->i, 0);
  arrange(selmon);
}

Client *nexttiled(Client *c) {
  for (; c && (c->isfloating || !ISVISIBLE(c)); c = c->next)
    ;
  return c;
}

void vertical_tile(Monitor *m) {
  unsigned int i, n;
  int y, h;
  Client *c;

  for (n = 0, c = m->clients; c; c = c->next)
    if (ISVISIBLE(c))
      n++;
  if (n == 0)
    return;

  y = 0;
  h = m->wh / n; // Each window takes an equal height

  for (i = 0, c = m->clients; c; c = c->next) {
    if (!ISVISIBLE(c))
      continue;
    resize(c, m->wx, m->wy + y, m->ww, h - 2 * c->bw, 0);
    y += h;
  }
}

void horizontal_tile(Monitor *m) {
  unsigned int i, n;
  int x, y, h, w;
  Client *c;

  // Count the number of visible windows
  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;

  if (n == 0)
    return;

  // Calculate the window height and width for each client
  w = m->ww / n;
  h = m->wh;

  x = m->wx;
  y = m->wy;

  // Place clients horizontally
  for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
    resize(c, x, y, w - (2 * c->bw), h - (2 * c->bw), 0);
    x += w;
  }
}

void set_tile_vertical(const Arg *arg) { vertical_tile(selmon); }
void set_tile_horizontal(const Arg *arg) { horizontal_tile(selmon); }

void tile(Monitor *m) {
  unsigned int i, n, h, mw, my, ty;
  Client *c;

  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;
  if (n == 0)
    return;

  if (n > m->nmaster)
    mw = m->nmaster ? m->ww * m->mfact : 0;
  else
    mw = m->ww;
  for (i = my = ty = 0, c = nexttiled(m->clients); c;
       c = nexttiled(c->next), i++)
    if (i < m->nmaster) {
      h = (m->wh - my) / (MIN(n, m->nmaster) - i);
      resize(c, m->wx, m->wy + my, mw - (2 * c->bw), h - (2 * c->bw), 0);
      if (my + HEIGHT(c) < m->wh)
        my += HEIGHT(c);
    } else {
      h = (m->wh - ty) / (n - i);
      resize(c, m->wx + mw, m->wy + ty, m->ww - mw - (2 * c->bw),
             h - (2 * c->bw), 0);
      if (ty + HEIGHT(c) < m->wh)
        ty += HEIGHT(c);
    }
}
