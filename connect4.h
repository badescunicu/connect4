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

extern FILE *f, *saveFile;
extern Player p[2];
extern char menuList[3][20], players[2][30], saveFileName[15];
extern int maxx, maxy, boardState[8][9], colorChoice[3],
  winningPositions[2][7], curPointsPlayer[2], turn;
extern WINDOW *board, *prompt;
extern time_t start_time;

/* Menu functions */
void ErrorMessage(char *s);
void Initialize();
int InitializeMenu();
void DrawMenu(int choice);
void PlayerSelect();
void DrawPickColor(int y, int colorChoice);
int Pause();
void SaveGame();
void Load();
void DrawPrompt(char *s);

/* Gameplay functions */
void DrawBoardLayout();
void DrawBoard();
void PrintTime();
void PrintScore();
void Play();
void PreviewPiece(int row, int colChosen, int color);
int GetAvailableRow(int col);
void AnimatePiece(int turn, int colChosen);
int CheckEndOfGameFromPosition(int row, int col);
void InitializeWinningPositions();
void BlinkWinningPositions();
void ResetBoard();

/* Score database functions */
void AddPlayer(Player p);
int SearchPlayer(Player p);
int GetPlayerScore(Player p);
void UpdatePlayer(Player p);
void PrintDatabase();

void Quit();

#endif
