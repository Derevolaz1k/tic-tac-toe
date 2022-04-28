#include<iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <string>
#include "functions.h"

using namespace std;

int main() 
{
	setlocale(LC_ALL, "Ru");
	int rows=0;
	int kols=0;
	char** field = nullptr;
	int count = 0;
	newGame_or_loadGame(field,rows,kols,count);
	int x, y;
	while (1)
	{
		int Play = -1;
		std::system("cls");
		cout << "Save - сохранить игру."<<endl;
		printArr(field, rows, kols);
		if (count % 2 == 0)
		{
			cout << "Ходит игрок №1"<<endl;
			cout << "Введите клетку (x,y)";
			x = _getX(field,rows,kols,count);
			y = _getY(field, rows, kols, count);
			if (x > rows || y > kols||field[x][y]!='_')
				continue;
			field[x][y] = 'x';
		}
			
		else
		{
			cout << "Ходит игрок №2" << endl;
			cout << "Введите клетку (x,y)";
			x = _getX(field, rows, kols, count);
			y = _getY(field, rows, kols, count);
			if (x > rows || y > kols || field[x][y] != '_')
				continue;
			field[x][y] = 'o';
		}
		if (GameOver(CounterRows(field, rows, kols, x, y), CounterKols(field, rows, kols, x, y), CounterDiag(field, rows, kols, x, y), CounterDraw(field, rows, kols, x, y)) == 3)
			count++;
		else
			break;
	}
	DelArr(field, rows, kols);
	std::system("pause");
	return 0;
}