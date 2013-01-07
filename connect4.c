#include "connect4.h"

int maxx, maxy, x, y, colorChoice1 = 0, colorChoice2 = 0,
    curPointsPlayer1, curPointsPlayer2, totalPointsPlayer1, totalPointsPlayer2;
WINDOW *board;
char menuList[3][20] = {"New game", "Load saved game", "Quit"},
     players[2][30];

int main() {
  int chosen, board_state[8][9];
  Initialize();
  getmaxyx(stdscr, maxy, maxx);
  chosen = InitializeMenu();
  switch(chosen) {
    case 0: /* New game */
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
