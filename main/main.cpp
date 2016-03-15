#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
//#include "TLink.h"
#include <conio.h>
#include <Windows.h>
#include "TText.h"

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void Draw(char str[15])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*Цвет символов - желтый. Цвет фона - темно-серый*/
	//SetConsoleTextAttribute(hConsole, (WORD)((DarkGray << 4) | Yellow));
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightBlue));
	printf(str);
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
}

int menu()
{
	int key = 0;
	int code;
	do
	{
		system("cls");
		key = (key + 3) % 3;
		if (key == 0)
			Draw("-> Load Text");
		else 
			printf("   Load Text");
		if (key == 1)
			Draw("\n-> Operation with Text");
		else
			printf("\n   Operation with Text");
		if (key == 2)
			Draw("\n-> Save Text");
		else
			printf("\n   Save Text");
		printf("\n");

		code = _getch();
		if (code == 0)
			code = _getch();
		if (code == 80) 
			key++;
		if (code == 72) 
			key--;
	} while (code != 13);
	return key;
}
int main()
{
	TText txt;
	char File[] = "Test_text.txt";
	int answer=-1;
	while (1)
	{
		answer = menu();
		switch (answer)
		{
		case 0:
			system("cls");
			txt.ReadFile(File);
			txt.PrintText();
			break;
		case 1:
			system("cls");
			printf("Hello\n"); break;
		case 2:
			system("cls");
			exit; break;
		}
	
		if (answer == 2)
			break;
		_getch();
		
	}
	printf("Good luck!\n");
	return 0;
}

