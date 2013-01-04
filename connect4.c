#include "menu.h"

int max_x, max_y, x, y;

int main() {
  WINDOW *wnd;
  Initialize(&wnd);

  refresh();
  getch();
  endwin();
  return 0;
}
