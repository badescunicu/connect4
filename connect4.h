#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef CONNECT4_H
#define CONNECT4_H

typedef struct {
  char name[30];
  int score;
}Player;

extern FILE *f;
extern Player p[2];
extern char menuList[3][20], players[2][30];
extern int maxx, maxy, boardState[8][9], colorChoice[3],
  curPointsPlayer1, curPointsPlayer2;
extern WINDOW *board;
extern time_t start_time;

void ErrorMessage(char *s);
void Initialize();
int InitializeMenu();
void DrawMenu(int choice);
void PlayerSelect();
void DrawPickColor(int y, int colorChoice);

void DrawBoardLayout();
void DrawBoard();
void PrintTime();
void PrintScore();
void Play();
void PreviewPiece(int colChosen, int color);
int GetAvailableRow(int col);

void AddPlayer(Player p);
int SearchPlayer(Player p);
int GetPlayerScore(Player p);
void UpdatePlayer(Player p);
void PrintDatabase();

void Quit();

#endif
