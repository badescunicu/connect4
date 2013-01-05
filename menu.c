#include "menu.h"

void ErrorMessage(char *s) {
  addstr(s);
  refresh();
  getch();
  endwin();
  exit(1);
}

void Initialize() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  nodelay(stdscr, TRUE);
}

void InitializeMenu() {
  int c, i = 0;
  char *s = "Auto completing test for various info about the project";
  mvprintw(1, 0 , "Connect4");
  DrawMenu(choice);
  while(1) {
    c = getch();
    if(c == 'q')
      break;
    if(c == KEY_DOWN) {
      choice = (choice + 1) % 3;
      DrawMenu(choice);
    }
    if(c == KEY_UP) {
      choice = (choice + 2) % 3;
      DrawMenu(choice);
    }

    if(i < strlen(s)) {
      mvaddstr(maxy - 1, maxx - 1 - i, s);
      napms(60);
      i++;
    }
    
    refresh();
  }
}

void DrawMenu(int choice) {
  int i;
  for(i = 0; i < 3; i++) {
    move(maxy / 2 + 2 * (i - 1), maxx  / 2 - 8);
    if(i == choice) {
      attron(A_REVERSE);
      printw("%s", menuList[i]);
      attroff(A_REVERSE);
    }
    else
      printw("%s", menuList[i]);
  }
}
