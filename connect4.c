#include "connect4.h"
/* Score Database File */
FILE *f;

FILE *saveFile;

Player p[2];
WINDOW *board, *prompt;
int maxx, maxy, boardState[8][9], winningPositions[2][7], 
    colorChoice[3] = {0}, curPointsPlayer[2], turn, colsFull = 0;
char menuList[3][20] = {"New game", "Load saved game", "Quit"},
     players[2][30];

char saveFileName[15];
time_t start_time;

int main() {
  int chosen;
  Initialize();
  getmaxyx(stdscr, maxy, maxx);
  chosen = InitializeMenu();
  switch(chosen) {
    case 0: /* New game */
      start_time = time(NULL);
      PlayerSelect();
      DrawBoardLayout();
      Play();
      break;
    case 1: /* Load saved game */
      Load();
      break;
    case 2: /* Quit */
      Quit();
      break;
    default:
      break;
  }
  endwin();
  return 0;
}
