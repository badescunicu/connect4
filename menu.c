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

/* Select name and color for both players */
void PlayerSelect() {
  /* Initialize start_time after hitting new game" */
  char *msg1 = "Choose your color, ";
  int c, i;
  nodelay(stdscr, FALSE);
  clear();
  echo();
  mvprintw(maxy / 4, maxx / 6, "Enter name for player 1: ");
  refresh();
  getnstr(p[0].name, 10);
  mvprintw(maxy / 4 + 2, maxx / 6, "Enter name for player 2: ");
  getnstr(p[1].name, 10);

  /* Check if player is in database */
  for(i = 0; i <= 1; i++) {
    if(SearchPlayer(p[i]))
      p[i].score = GetPlayerScore(p[i]);
    else {
      p[i].score = 0;
      AddPlayer(p[i]);
    }
  }
  clear();
  noecho();

  /* Print Color Choice Menu for Player 1 */
  mvprintw(1, (maxx - strlen(msg1) - strlen(p[0].name)) / 2,
          "%s%s", msg1, p[0].name);
  DrawPickColor(3, colorChoice[1]);
  while(1) {
    c = getch();
    if(c == ' ' || c == 10)
      break;
    if(c == KEY_LEFT) {
      colorChoice[1] = (colorChoice[1] + 2 ) % 3;
      DrawPickColor(3, colorChoice[1]);
    }
    if(c == KEY_RIGHT) {
      colorChoice[1] = (colorChoice[1] + 1) % 3;
      DrawPickColor(3, colorChoice[1]);
    }
    refresh();
  }

  /* Print Color Choice Menu for Player 2 */
  mvprintw(6, (maxx - strlen(msg1) - strlen(p[1].name)) / 2,
          "%s%s", msg1, p[1].name);
  DrawPickColor(8, colorChoice[2]);
  while(1) {
    c = getch();
    if(c == ' ' || c == 10)
      break;
    if(c == KEY_LEFT) {
      colorChoice[2] = (colorChoice[2] + 2 ) % 3;
      DrawPickColor(8, colorChoice[2]);
    }
    if(c == KEY_RIGHT) {
      colorChoice[2] = (colorChoice[2] + 1) % 3;
      DrawPickColor(8, colorChoice[2]);
    }
    refresh();
  }

  /* Increase colorChoice so that would match the COLOR_PAIR */
  colorChoice[1] += 5;
  colorChoice[2] += 5;
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
  init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(5, COLOR_RED, COLOR_RED);
  init_pair(6, COLOR_GREEN, COLOR_GREEN);
  init_pair(7, COLOR_BLUE, COLOR_BLUE);
  init_pair(8, COLOR_WHITE, COLOR_WHITE);

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

int Pause() {
  int c;
  time_t start_pause = time(NULL), end_pause;
  char *msg = "GAME PAUSED ---> PRESS p FOR RESUMING THE GAME",
      *msg2 = "                                              ";
  mvprintw(0, (maxx - strlen(msg)) / 2, "%s", msg);
  while(1) {
    c = getch();
    if(c == 'p') {
      end_pause = time(NULL);
      mvprintw(0, (maxx - strlen(msg2)) / 2, "%s", msg2);
      break;
    }
  }
  int diff = end_pause - start_pause;
  return diff;
}

void SaveGame() {
  clear();
  nodelay(stdscr, FALSE);
  echo();
  mvprintw(4, 4, "Insert the name for save file: ");
  getnstr(saveFileName, 10);
  saveFile = fopen(saveFileName, "ab");
  fwrite(p, sizeof(Player), 2, saveFile); 
  fwrite(curPointsPlayer, sizeof(curPointsPlayer[1]), 2, saveFile);
  fwrite(boardState, sizeof(boardState), 1, saveFile);
  fwrite(colorChoice, sizeof(colorChoice), 1, saveFile);
  noecho();
  nodelay(stdscr, TRUE);
  DrawBoardLayout();
  DrawBoard();
  fclose(saveFile);
}

void Load() {
  clear();
  nodelay(stdscr, FALSE);
  echo();
  mvprintw(4, 4, "Insert the name for save file: ");
  getnstr(saveFileName, 10);
  noecho();
  saveFile = fopen(saveFileName, "rb");
  if(saveFile == NULL)
    ErrorMessage("Error at opening save file!");

  fread(&p[0], sizeof(Player), 1, saveFile);
  fread(&p[1], sizeof(Player), 1, saveFile);
  fread(&curPointsPlayer[0], sizeof(curPointsPlayer[0]), 1, saveFile);
  fread(&curPointsPlayer[1], sizeof(curPointsPlayer[1]), 1, saveFile);
  fread(boardState, sizeof(boardState), 1, saveFile);
  fread(colorChoice, sizeof(colorChoice), 1, saveFile);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(5, COLOR_RED, COLOR_RED);
  init_pair(6, COLOR_GREEN, COLOR_GREEN);
  init_pair(7, COLOR_BLUE, COLOR_BLUE);
  init_pair(8, COLOR_WHITE, COLOR_WHITE);

  fclose(saveFile);
  start_time = time(NULL);
  DrawBoardLayout();
  DrawBoard();
  Play();
}

void DrawPrompt(char *s) {
  int x, y;
  prompt = newwin(5, 40, 5, 5);
  getmaxyx(prompt, y, x);
  mvwprintw(prompt, 1, 1, "%s", s); 
  refresh();
  touchwin(prompt);
  wrefresh(prompt);
  getch();
}

