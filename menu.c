#include "menu.h"

void Initialize(WINDOW **wnd) {
  *wnd = initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(*wnd, TRUE);
  start_color();
}
