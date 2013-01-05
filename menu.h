#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef MENU_H
#define MENU_H

extern char menuList[3][20], players[2][30];
extern int maxx, maxy, colorChoice1, colorChoice2;
extern WINDOW *menuWindow;

void ErrorMessage(char *s);
void Initialize();
int InitializeMenu();
void DrawMenu(int choice);
void PlayerSelect();
void DrawPickColor(int y, int colorChoice);
void Quit();



#endif
