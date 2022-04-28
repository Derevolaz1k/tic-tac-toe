#include "functions.h"
#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <conio.h>

using namespace std;

void printArr(char** arr, int rows, int kols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < kols; j++)
			cout << arr[i][j] << "|";
		cout << endl;
	}

}

void DelArr(char** arr, int rows, int kols)
{
	for (int i = 0; i < rows; i++)
		delete[] arr[i];
	delete[] arr;
}

void saveGame(char**& arr, int rows, int kols, int count)
{
	SYSTEMTIME date;
	GetSystemTime(&date);
	std::system("cls");
	cout << "Введите название сохранения: ";
	string path;
	getline(cin, path);
	path += ".save";
	ofstream fout("Saves/" + path);
	fout << "#Время " << (date.wDay) << "." << (date.wMonth) << "." << date.wYear << " " << (date.wHour + 5) << ":" << date.wMinute << endl << "#Коммент\n";
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < kols; j++)
		{
			fout << arr[i][j];
		}
		fout << endl;
	}
	fout << count;
	fout.close();
	std::system("cls");
	printArr(arr, rows, kols);
}

int lastStr(string& path)
{
	ifstream fout(path);
	string str;
	while (!fout.eof())
		getline(fout, str);
	fout.close();
	return stoi(str);
}

void loadArr(char**& arr, int& rows, int& kols, string& path)
{
	ifstream fout;
	fout.open(path);
	int counterStr = 0;
	string str;
	while (!fout.eof())
	{
		getline(fout, str);
		if (str[0] != '#')
			counterStr++;
	}
	counterStr--;
	arr = new char* [counterStr];
	for (int i = 0; i < counterStr; i++)
	{
		arr[i] = new char[counterStr];
	}
	counterStr = 0;
	fout.close();
	fout.open("Saves/" + path);
	while (!fout.eof())
	{
		getline(fout, str);
		if (str[0] == '#' || ((int)str[0] >= 48 && (int)str[0] <= 57))
			continue;
		else
		{
			for (int i = 0; i < str.size(); i++)
				arr[counterStr][i] = str[i];
			counterStr++;
		}
	}
	rows = counterStr;
	kols = rows;
	fout.close();
}

int _getX(char**& arr, int rows, int kols, int count)
{
	do {
		try {

			string x;
			cout << "Введите координату x: ";
			getline(cin, x);
			if (x == "Save" || x == "save")
				saveGame(arr, rows, kols, count);
			int num = stoi(x);
			return num - 1;
		}
		catch (const exception& ex)
		{
			if (ex.what() == "invalid stoi argument")
				cout << "Ошибка " << ex.what() << endl;
		}
	} while (1);
}

int _getY(char**& arr, int rows, int kols, int count)
{
	do {
		try {

			string y;
			cout << "Введите координату y: ";
			getline(cin, y);
			if (y == "Save" || y == "save")
				saveGame(arr, rows, kols, count);
			int num = stoi(y);
			return num - 1;
		}
		catch (const exception& ex)
		{
			if (ex.what() == "invalid stoi argument")
				cout << "Ошибка " << endl;
		}
	} while (1);
}

int CounterRows(char** arr, int rows, int kols, int x, int y)
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
			if (((i + j) == (rows - 1)) && arr[i][j] == 'x')
			{
				counterX++;
			}

			else
				if (((i + j) == (rows - 1)) && arr[i][j] == 'o')
				{
					counterO++;
				}
		}
		if (counterX == kols)
			return 1;
		else
			if (counterO == kols)
				return 2;
	}
	counterX = 0;
	counterO = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < kols; j++)
		{
			if (i == j && arr[i][j] == 'x')
			{
				counterX++;
			}

			else
				if (i == j && arr[i][j] == 'o')
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

void getArr(char** arr, int& rows, int& kols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < kols; j++)
			arr[i][j] = '_';
	}
}

void newArr(char**& arr, int& rows, int& kols)
{
	do
	{
		try
		{

			string y;
			cout << "Введите размер поля: ";
			getline(cin, y);
			rows = stoi(y);
			kols = rows;
			break;
		}
		catch (const exception& ex)
		{
			if (ex.what() == "invalid stoi argument")
				cout << "Ошибка " << endl;
		}
	} while (1);
	arr = new char* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new char[kols];
	}
	getArr(arr, rows, kols);
}

void loadGame(char**& arr, int rows, int kols, int& count)
{
	std::system("cls");
	cout << "Введите название сохранения: ";
	string path;
	getline(cin, path);
	path += ".save";
	ifstream fout("Saves/" + path);
	if (!fout.is_open())
	{
		cout << "Ошибка названия сохранения! Начало новой игры!" << endl;
		newArr(arr, rows, kols);
		count = 0;
	}
	else
		if (fout.is_open())
		{
			loadArr(arr, rows, kols, path);
			count = lastStr(path);
		}
	fout.close();
}

void newGame_or_loadGame(char**& arr, int& rows, int& kols, int& count)
{
	char YesNo;
	cout << "Для продолжения игры нажмите 'y', любую клавишу для начала новой игры..." << endl;

	switch (YesNo = _getch())
	{
	case 89:
	case 121:
	{
		cout << "Введите название сохраненной игры: ";
		loadGame(arr, rows, kols, count);
	}break;
	default:
	{
		cout << "Начало новой игры: " << endl;
		newArr(arr, rows, kols);
	}
	}
}