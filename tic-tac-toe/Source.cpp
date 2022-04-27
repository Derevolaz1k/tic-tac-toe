#include<iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

int rows;//Длина массива
int kols;



void getArr(char **arr, int rows, int kols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < kols; j++)
				arr[i][j] = '_';			
	}
}

void printArr(char** arr, int rows, int kols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j <kols; j++)
			cout << arr[i][j]<<"|";
		cout << endl;
	}
	
}

void DelArr(char** arr, int rows, int kols)
{
	for (int i = 0; i < rows; i++)
		delete[] arr[i];
	delete[] arr;
}

void getxy(int& x, int& y)
{
	cout << "Введите координату x: ";
	cin >> x;
	x -= 1;
	cout << "Введите координату y: ";
	cin >> y;
	y -= 1;
}

int CounterRows(char** arr, int rows,int kols,int x,int y)
{
	int counterX = 0;
	int counterO = 0;
	for (int i = 0; i < rows; i++)
	{
		if (arr[i][y] == 'x')
			counterX++;
		else
			if (arr[i][y] == 'o')
				counterO++;
	}
	if (counterX == rows)
		return 1;
	else
		if (counterO == kols)
			return 2;
		else 
			return 3;
}

int CounterKols(char** arr, int rows, int kols, int x, int y)
{
	int counterX = 0;
	int counterO = 0;
	for (int i = 0; i < kols; i++)
	{
		if (arr[x][i] == 'x')
			counterX++;
		else
			if (arr[x][i] == 'o')
				counterO++;
	}
	if (counterX == kols)
		return 1;
	else
		if (counterO == kols)
		return 2;
		else
			return 3;
}

int CounterDiag(char** arr, int rows, int kols, int x, int y)
{
	int counterX = 0;
	int counterO = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < kols; j++)
		{
			if (((i + j) == (rows - 1))&& arr[i][j] == 'x')
			{
				counterX++;
			}
				
			else
				if (((i + j) == (rows - 1))&& arr[i][j] == 'o')
				{
					counterO++;
				}
		}
		if (counterX == kols)
			return 1;
		else 
			if(counterO==kols)
			return 2;
	}
	counterX = 0;
	counterO = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < kols; j++)
		{
			if (i==j&&arr[i][j]=='x')
			{
				counterX++;
			}

			else
				if (i==j&&arr[i][j] == 'o')
				{
					counterO++;
				}
		}
		if (counterX == kols)
		{
			return 1;
		}
			
		else
			if (counterO == kols)
			{
				return 2;
			}	
	}
	return 3;
}

int CounterDraw(char** arr, int rows, int kols, int x, int y)
{
	int count = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < kols; j++)
		{
			if (arr[i][j] == '_')
				return 3;
		}
	}
	return 0;
}

int GameOver(int win1, int win2, int diag, int draw)
{
	if (win1 == 1)
	{
		cout << "Победа пользователя №1";
		return 1;
	}

	else
		if (win1 == 2)
		{
			cout << "Победа пользователя №2";
			return 2;
		}
		else
			if (win2 == 1)
			{
				cout << "Победа пользователя №1";
				return 1;
			}
			else
				if (win2 == 2)
				{
					cout << "Победа пользователя №2";
					return 2;
				}
					else
						if (diag == 2)
						{
							cout << "Победа пользователя №2";
							return 2;
						}
						else
							if (diag == 1)
							{
								cout << "Победа пользователя №1";
								return 1;
							}
							else
								if (draw == 3)
								{
									return 3;
								}
							else
									if (draw == 0)
									{
										cout << "Ничья!";
										return 0;
									}
									
}

int main() 
{
	setlocale(LC_ALL, "Ru");
	cout << "Введите размер поля: ";
	cin >> rows;
	kols = rows;
	char** field = new char* [rows];
	for (int i = 0; i < rows; i++)
	{
		field[i] = new char[kols];
	}
	getArr(field, rows, kols);
	int x, y;
	int count = 0;
	
	while (1)
	{
		int Play = -1;
		system("cls");
		printArr(field, rows, kols);
		if (count % 2 == 0)
		{
			cout << "Ходит игрок №1"<<endl;
			cout << "Введите клетку (x,y)";
			getxy(x, y);
			if (x > rows || y > kols||field[x][y]!='_')
				continue;
			field[x][y] = 'x';
		}
			
		else
		{
			cout << "Ходит игрок №2" << endl;
			cout << "Введите клетку (x,y)";
			getxy(x, y);
			if (x > rows || y > kols)
				continue;
			field[x][y] = 'o';
		}
		if (GameOver(CounterRows(field, rows, kols, x, y), CounterKols(field, rows, kols, x, y), CounterDiag(field, rows, kols, x, y), CounterDraw(field, rows, kols, x, y)) == 3)
			count++;
		else
			break;
	}
	DelArr(field, rows, kols);
	system("pause");
	return 0;
}