#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef CONNECT4_H
#define CONNECT4_H

extern char menuList[3][20], players[2][30];
extern int maxx, maxy, colorChoice1, colorChoice2;
extern WINDOW *board;

void ErrorMessage(char *s);
void Initialize();
int InitializeMenu();
void DrawMenu(int choice);
void PlayerSelect();
void DrawPickColor(int y, int colorChoice);
void DrawBoardLayout();
void DrawBoard(int boardState[8][9]);
void Quit();



#endif
