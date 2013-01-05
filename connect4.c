#include "menu.h"

int maxx, maxy, x, y, choice = 0;
WINDOW *menuWindow;
char menuList[3][20] = {"New game", "Load saved game", "Quit"};

int main() {
  Initialize();
  getmaxyx(stdscr, maxy, maxx);
  InitializeMenu();
  endwin();
  return 0;
}
