#pragma once
#include <string>

void printArr(char** arr, int rows, int kols);
void DelArr(char** arr, int rows, int kols);
void saveGame(char**& arr, int rows, int kols, int count);
int lastStr(std::string& path);
void loadArr(char**& arr, int& rows, int& kols, std::string& path);
int _getX(char**& arr, int rows, int kols, int count);
int _getY(char**& arr, int rows, int kols, int count);
int CounterRows(char** arr, int rows, int kols, int x, int y);
int CounterKols(char** arr, int rows, int kols, int x, int y);
int CounterDiag(char** arr, int rows, int kols, int x, int y);
int CounterDraw(char** arr, int rows, int kols, int x, int y);
int GameOver(int win1, int win2, int diag, int draw);
void getArr(char** arr, int& rows, int& kols);
void newArr(char**& arr, int& rows, int& kols);
void loadGame(char**& arr, int rows, int kols, int& count);
void newGame_or_loadGame(char**& arr, int& rows, int& kols, int& count);