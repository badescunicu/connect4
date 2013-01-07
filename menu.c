#include "connect4.h"

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
}

int InitializeMenu() {
  int c, i = 0;
  int choice = 0;
  char *s = "Press SPACE or ENTER to choose the option";
  mvprintw(1, 0 , "Connect4");
  nodelay(stdscr, TRUE);
  DrawMenu(choice);
  while(1) {
    c = getch();
    if(c == 10 || c == ' ')
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
  return choice;
}

void DrawMenu(int choice) {
  int i;
  for(i = 0; i < 3; i++) {
    move(maxy / 2 + 2 * (i - 1), (maxx - strlen(menuList[1])) / 2 );
    if(i == choice) {
      attron(A_REVERSE);
      printw("%s", menuList[i]);
      attroff(A_REVERSE);
    }
    else
      printw("%s", menuList[i]);
  }
}

void PlayerSelect() {
  char *msg1 = "Choose your color, ";
  int c;
  nodelay(stdscr, FALSE);
  addstr("test STring");
  clear();
  echo();
  mvprintw(maxy / 4, maxx / 6, "Enter name for player 1: ");
  refresh();
  getnstr(players[0], 30);
  mvprintw(maxy / 4 + 2, maxx / 6, "Enter name for player 2: ");
  getnstr(players[1], 30);
  clear();
  noecho();

  /* Print Color Choice Menu for Player 1 */
  mvprintw(1, (maxx - strlen(msg1) - strlen(players[0])) / 2,
          "%s%s", msg1, players[0]);
  DrawPickColor(3, colorChoice1);
  while(1) {
    c = getch();
    if(c == ' ' || c == 10)
      break;
    if(c == KEY_LEFT) {
      colorChoice1 = (colorChoice1 + 2 ) % 3;
      DrawPickColor(3, colorChoice1);
    }
    if(c == KEY_RIGHT) {
      colorChoice1 = (colorChoice1 + 1) % 3;
      DrawPickColor(3, colorChoice1);
    }
    refresh();
  }

  /* Print Color Choice Menu for Player 2 */
  mvprintw(6, (maxx - strlen(msg1) - strlen(players[1])) / 2,
          "%s%s", msg1, players[1]);
  DrawPickColor(8, colorChoice2);
  while(1) {
    c = getch();
    if(c == ' ' || c == 10)
      break;
    if(c == KEY_LEFT) {
      colorChoice2 = (colorChoice2 + 2 ) % 3;
      DrawPickColor(8, colorChoice2);
    }
    if(c == KEY_RIGHT) {
      colorChoice2 = (colorChoice2 + 1) % 3;
      DrawPickColor(8, colorChoice2);
    }
    refresh();
  }

  /* Increase colorChoice so that would match the COLOR_PAIR */
  colorChoice1 += 3;
  colorChoice2 += 3;
}

void DrawPickColor(int y, int colorChoice) {
  int i;
  switch(colorChoice) {
    case 0:
      mvaddch(y, 6, '*');
      mvaddch(y, maxx / 2 - 2, ' ');
      mvaddch(y, maxx - 13, ' ');
      break;
    case 1:
      mvaddch(y, 6, ' ');
      mvaddch(y, maxx / 2 - 2, '*');
      mvaddch(y, maxx - 13, ' ');
      break;
    case 2:
      mvaddch(y, 6, ' ');
      mvaddch(y, maxx / 2 - 2, ' ');
      mvaddch(y, maxx - 13, '*');
      break;
  }
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(5, COLOR_RED, COLOR_RED);
  init_pair(6, COLOR_GREEN, COLOR_GREEN);
  init_pair(7, COLOR_BLUE, COLOR_BLUE);

  attrset(COLOR_PAIR(1));
  mvprintw(y, 7, "RED");
  attrset(COLOR_PAIR(2));
  mvprintw(y, maxx / 2 - 1, "GREEN");
  attrset(COLOR_PAIR(3));
  mvprintw(y, maxx - 12, "BLUE");
  attrset(A_NORMAL);
}

  
void Quit() {
  clear();
  char *msg = "Hope to see you soon, bye!";
  mvaddstr(maxy / 2, (maxx - strlen(msg)) / 2, msg);
  refresh();
  napms(1500);
}
