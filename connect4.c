#include "connect4.h"

FILE *f;
Player p[2];
WINDOW *board;
int maxx, maxy, boardState[8][9], winningPositions[2][7], 
    colorChoice[3] = {0}, curPointsPlayer[2], turn;
char menuList[3][20] = {"New game", "Load saved game", "Quit"},
     players[2][30];
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
    case 2: /* Quit */
      Quit();
      break;
    default:
      break;
  }
  endwin();
  return 0;
}
