#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#ifndef MENU_H
#define MENU_H

extern char menuList[3][20];
extern int choice, maxx, maxy;
extern WINDOW *menuWindow;

void Initialize();
void InitializeMenu();
void DrawMenu(int choice);
void ErrorMessage(char *s);


#endif
