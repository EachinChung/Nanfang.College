#ifndef  __MINESWEEPER_H__
#define  __MINESWEEPER_H__
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <graphics.h>

void Init();
void MainInterface();
void NewGame();
void Custom();
void RankingList();

int Input();
void InitMap();
void Simple();
void Commonly();
void Difficulty();
void RankingListMenu();
void PrintRankingList(int node);
void About();

void TimeUI(TCHAR Time[]);
void InitBomb(int SquareX, int SquareY);
int Calculation(int SquareX, int SquareY);
void Game();
int Flag();
void FlagUI();
void MenuUI();
bool Menu();
void Open(int SquareX, int SquareY);
void Tab(int SquareX, int SquareY);
void Uncertain(int SquareX, int SquareY);
void CancelTab(int SquareX, int SquareY);
void SmilingFace(int boomX, int boomY);
void Win();
void GameOver();
void GameEsc();
int Fraction(int node);
void Sort();
void Settlement();

extern int bomb;
extern int flag;
extern int MapSize;
extern int s, m, h;
extern int max_x, max_y;
extern int Square[30][16];
extern int square_x, square_y;
extern bool custom, TwoInterface, win, fail;

typedef struct rankinglist {
	int second;
	int minute;
	int hour;
}LIST;

extern TCHAR Time[50];
extern LIST record[11];

#endif