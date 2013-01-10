#include "connect4.h"

void DrawBoardLayout() {
  clear();
  int b[8][9];

  int c;
  int x, y, boardmaxx = 44, boardmaxy = 19;
  board = newwin(boardmaxy, boardmaxx, 4, 3);
  wattron(board, COLOR_PAIR(4));

  for(x = 0; x < boardmaxx; x++) {
    mvwaddch(board, 0, x, '*');
    mvwaddch(board, boardmaxy - 1, x, '*');
  }

  for(y = 0; y < boardmaxy; y++) {
    mvwaddstr(board, y, 0, "**");
    mvwaddstr(board, y, boardmaxx - 2, "**");
  }
  
  for(y = 1; y <= boardmaxy - 2; y++)
    for(x = 0; x < boardmaxx; x += 6)
      mvwaddstr(board, y, x, "**");

  for(x = 1; x <= boardmaxx - 2; x++)
    for(y = 0; y < boardmaxy; y += 3)
      mvwaddch(board, y, x, '*');

  refresh();
  wrefresh(board);
}

void DrawBoard() {
  int i, j, x, y;
  for(i = 1; i <= 6; i++) {
    y = 1 + 3 * (i - 1);
    for(j = 1; j <= 7; j++) {
      x = 2 + 6 * (j - 1);
      if(boardState[i][j] != 0) {
        switch(boardState[i][j]) {
          case 1:
            wattrset(board, COLOR_PAIR(colorChoice[1]));
            break;
          case 2:
            wattrset(board, COLOR_PAIR(colorChoice[2]));
            break;
        }
      mvwaddstr(board, y, x, "****");
      mvwaddstr(board, y + 1, x, "****");
      wattrset(board, A_NORMAL);
      }
      else {
        wattrset(board, COLOR_PAIR(1));
        mvwaddstr(board, y, x, "    ");
        mvwaddstr(board, y + 1, x, "    ");
      }
    }
  }
}



void Play() {
  int c, availableRow, colChosen = 0, color = colorChoice[1], turn = 1;
  nodelay(stdscr, TRUE);
  while(1) {
    c = getch();
    PrintTime();
    PrintScore();
    if(c == 'q')
      break;
    if(c == ' ' || c == 10) {
      availableRow = GetAvailableRow(colChosen + 1);
      if(availableRow > 0) {
        int i = 1;
        while(i < availableRow) {
          boardState[i][colChosen + 1] = turn;
          DrawBoard(boardState);
          refresh();
          wrefresh(board);
          napms(120);
          boardState[i][colChosen + 1] = 0;
          DrawBoard(boardState);
          refresh();
          wrefresh(board);
          i++;
        }
        boardState[availableRow][colChosen + 1] = turn;
        DrawBoard(boardState);
        refresh();
        wrefresh(board);
        turn = 3 - turn;
        color = colorChoice[turn];
      }
    }

    PreviewPiece(2, colChosen, color);
    if(c == KEY_LEFT) {
      colChosen = (colChosen + 6) % 7;
      PreviewPiece(2, colChosen, color);
    }
    if(c == KEY_RIGHT) {
      colChosen = (colChosen + 1) % 7;
      PreviewPiece(2, colChosen, color);
    }
  }
}

/* Display a piece above the board */
void PreviewPiece(int row, int colChosen, int color) {
  int i;
  for(i = 0; i < 7; i++) {
    if(i == colChosen) {
      attron(COLOR_PAIR(color));
      mvprintw(row, 5 + 6 * i, "****");
      mvprintw(row + 1, 5 + 6 * i, "****");
      attroff(COLOR_PAIR(color));
    }
    else {
      mvprintw(row, 5 + 6 * i, "    ");
      mvprintw(row + 1, 5 + 6 * i, "    ");
    }
  }
}

int GetAvailableRow(int col) {
  int i = 0;
  while(boardState[i + 1][col] == 0 && i <= 5)
    i++;
  return i;
}

/* Prints current time and time spent since the beginning of the game */
void PrintTime() {
    struct tm *cur_time;
    time_t t, dif;
    int hours, minutes, seconds;

    t = time(NULL);
    cur_time = localtime(&t);
    mvprintw(4, maxx - 20, "%02d:%02d:%02d", cur_time -> tm_hour,
             cur_time -> tm_min, cur_time -> tm_sec);

    dif =  t - start_time;
    seconds = dif % 60;
    dif = dif / 60;
    minutes = dif % 60;
    hours = dif / 60;

    mvprintw(14, maxx - 20, "%02d:%02d:%02d", hours, minutes, seconds);
}

void PrintScore() {
  mvprintw(6, maxx - 20, "%s VS %s", p[0].name, p[1].name);
  /* print current score */
  mvprintw(8, maxx - 20, "%s: %d", p[0].name, curPointsPlayer1);
  mvprintw(9, maxx - 20, "%s: %d", p[1].name, curPointsPlayer2);

  /* print total score for each player */
  mvprintw(11, maxx - 20, "%s: %d", p[0].name, p[0].score);
  mvprintw(12, maxx - 20, "%s: %d", p[1].name, p[1].score);
}





