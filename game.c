#include "connect4.h"

void DrawBoardLayout() {
  clear();

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
          case 3:
            wattrset(board, COLOR_PAIR(8));
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
  refresh();
  wrefresh(board);
}

void Play() {
  int c, availableRow, colChosen = 0, color = colorChoice[1];
  turn = 1;
  nodelay(stdscr, TRUE);
  while(1) {
    c = getch();
    PrintTime();
    PrintScore();
    if(c == 'q') {
      int ch;
      DrawPrompt("Are you sure you want to quit?\n YES(y)/NO(n)");
      do {
        ch = getch();
      }while(ch != 'y' && ch != 'n');

      if(ch == 'y') {
        UpdatePlayer(p[0]);
        UpdatePlayer(p[1]);
        Quit();
        break;
      }
      if(ch == 'n') {
        DrawBoardLayout();
        DrawBoard();
      }
    }

    if(c == 'p') {
      int diff = Pause();
      start_time += diff;
    }

    if(c == 's') {
      SaveGame();
    }

    if(c == ' ' || c == 10) {
      availableRow = GetAvailableRow(colChosen + 1);
      if(availableRow > 0) {
        AnimatePiece(turn, colChosen);
        boardState[availableRow][colChosen + 1] = turn;
        DrawBoard(boardState);
        if(CheckEndOfGameFromPosition(availableRow, colChosen + 1)) {
          char msg[100];
          int ch;
          sprintf(msg, "%s has won!\n Do you want to play again?\n YES(y)/NO(n)",
                  p[turn - 1].name);
          curPointsPlayer[turn - 1]++;
          p[turn - 1].score++;
          PrintScore();
          BlinkWinningPositions();
          DrawPrompt(msg);
          while((ch = getch()) != 'y' && ch != 'n');
          if(ch == 'n') {
            UpdatePlayer(p[0]);
            UpdatePlayer(p[1]);
            Quit();
            break;
          }
          if(ch == 'y') {
            ResetBoard();
            DrawBoardLayout();
            DrawBoard();
          }
        }
        turn = 3 - turn;
        color = colorChoice[turn];
        if(availableRow == 1) {
          colsFull++;
          if(colsFull == 7) {
            colsFull = 0;
            GameIsDraw();
          }
        }
      }
    }

    PreviewPiece(2, colChosen, color);
    if(c == KEY_LEFT || c == 'a') {
      colChosen = (colChosen + 6) % 7;
      PreviewPiece(2, colChosen, color);
    }
    if(c == KEY_RIGHT || c == 'd') {
      colChosen = (colChosen + 1) % 7;
      PreviewPiece(2, colChosen, color);
    }
  }
}

int CheckEndOfGameFromPosition(int row, int col) {
  int ok = 0, count = 0, i = row, j = col;
  InitializeWinningPositions();

   /* check vertical */
  while(boardState[i][j] == boardState[row][col] && i <= 6) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    i++;
  }
  if(count >= 4) {
    return 1;
  }
  
  /* check horizontal */
  count = 0; i = row; j = col;
  InitializeWinningPositions();
  while(boardState[i][j] == boardState[row][col] && j >= 1) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j--;
  }
  j = col + 1;
  while(boardState[i][j] == boardState[row][col] && j <= 7) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j++;
  }
  if(count >= 4) {
    return 1;
  }

  /* check first diagonal */
  count = 0; i = row; j = col;
  InitializeWinningPositions();
  while(boardState[i][j] == boardState[row][col] && j <=7 && i >= 1) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j++;
    i--;
  }
  i = row + 1;
  j = col - 1;
  while(boardState[i][j] == boardState[row][col] && j >=1 && i <= 6) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j--;
    i++;
  }
  if(count >= 4) {
    return 1;
  }

  /* check second diagonal */
  count = 0; i = row; j = col;
  InitializeWinningPositions();
  while(boardState[i][j] == boardState[row][col] && j >=1 && i >= 1) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j--;
    i--;
  }
  i = row + 1;
  j = col + 1;
  while(boardState[i][j] == boardState[row][col] && j <= 7 && i <= 6) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j++;
    i++;
  }
  if(count >= 4) {
    return 1;
  }
  
  return 0;
}

void InitializeWinningPositions() {
  int i, j;
  for(i = 0; i < 2; i++)
   for(j = 0; j < 7; j++)
     winningPositions[i][j] = 0;
}

void BlinkWinningPositions() {
  int i, blinked = 0;
  while(blinked < 5) {
    i = 0;
    while(i < 7 && winningPositions[0][i] != 0) {
      boardState[winningPositions[0][i]][winningPositions[1][i]] = 3;
      i++;
    }
    DrawBoard(boardState);
    napms(150);
    i = 0;
    while(i < 7 && winningPositions[0][i] != 0) {
      boardState[winningPositions[0][i]][winningPositions[1][i]] = turn;
      i++;
    }
    DrawBoard(boardState);
    napms(120);
    
    blinked++;
  }
}

void AnimatePiece(int turn, int colChosen) {
  int i = 1, availableRow = GetAvailableRow(colChosen + 1);
  while(i < availableRow) {
    boardState[i][colChosen + 1] = turn;
    DrawBoard(boardState);
    refresh();
    wrefresh(board);
    napms(120);
    boardState[i][colChosen + 1] = 0;
    DrawBoard(boardState);
    i++;
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
    t = time(NULL);
    int hours, minutes, seconds;

    cur_time = localtime(&t);
    mvprintw(4, 55, "Local Time:");
    mvprintw(5, 55, "%02d:%02d:%02d", cur_time -> tm_hour,
             cur_time -> tm_min, cur_time -> tm_sec);

    dif =  t - start_time;
    seconds = dif % 60;
    dif = dif / 60;
    minutes = dif % 60;
    hours = dif / 60;

    mvprintw(17, 55, "In-game time:");
    mvprintw(18, 55, "%02d:%02d:%02d", hours, minutes, seconds);
}

void PrintScore() {
  switch(turn) {
    case 1:
      mvprintw(7, 56 + strlen(p[0].name) + 
               strlen(" vs ") + strlen(p[1].name), " ");
      attron(COLOR_PAIR(colorChoice[1]));
      mvprintw(7, 53, "*");
      attroff(COLOR_PAIR(colorChoice[1]));
      break;
    case 2:
      mvprintw(7, 53, " ");
      attron(COLOR_PAIR(colorChoice[2]));
      mvprintw(7, 56 + strlen(p[0].name) + 
               strlen(" vs ") + strlen(p[1].name), "*");
      attroff(COLOR_PAIR(colorChoice[2]));
      break;
  }


  attron(A_BOLD);
  mvprintw(7, 55, "%s VS %s", p[0].name, p[1].name);
  attroff(A_BOLD);
  /* print current score */
  mvprintw(9, 55, "Current points:");
  mvprintw(10, 55, "%s: %d", p[0].name, curPointsPlayer[0]);
  mvprintw(11, 55, "%s: %d", p[1].name, curPointsPlayer[1]);

  /* print total score for each player */
  mvprintw(13, 55, "Total points:");
  mvprintw(14, 55, "%s: %d", p[0].name, p[0].score);
  mvprintw(15, 55, "%s: %d", p[1].name, p[1].score);
  mvprintw(17, 55, "Key bindings:");
  mvprintw(18, 55, "q-quit, s-save");
  mvprintw(19, 55, "Movement:");
  mvprintw(20, 55, "LEFT: a / <-");
  mvprintw(21, 55, "RIGHT: d / ->");
  mvprintw(22, 55, "ACTION: SPACE / ENTER");

}

/* Put zeroes in the boardState matrix */
void ResetBoard() {
  int i, j;
  for(i = 0; i < 8; i++)
    for(j = 0; j < 9; j++)
      boardState[i][j] = 0;
}

void GameIsDraw() {
  char *msg = "It's a draw! Do you want to play another one?\n YES(y) / NO(n)";
  int ch;
  DrawPrompt(msg);
  do {
    ch = getch();
  }while(ch != 'y' && ch != 'n');

  if(ch == 'n') {
    UpdatePlayer(p[0]);
    UpdatePlayer(p[1]);
    Quit();
    endwin();
    exit(0);
  }
  if(ch == 'y') {
    ResetBoard();
    DrawBoardLayout();
    DrawBoard();
  }
}
