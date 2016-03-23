#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "TText.h"
#include "TStack.h"
#include <iostream>

using namespace std;


TTextMem TLink::TextMem;

int menu()
{
	int NumberPosition = 3;
	int key = 0;
	int code;
	do
	{
		system("cls");
		key = (key + NumberPosition) % NumberPosition;
		if (key == 0)
			Draw("-> Load Text");
		else 
			printf("   Load Text");
		if (key == 1)
			Draw("\n-> Exit");
		else
			printf("\n   Exit");
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

int NextMenu(TText Text, int _MenuLength)
{
	int MenuLength = _MenuLength;
	int key = 0;
	int code;
	do
	{
		system("cls");
		key = (key + MenuLength) % MenuLength;
		if (key == 0)
			Draw("-> Operation with Text");
		else
			printf("   Operation with Text");
		if (key == 1)
			Draw("\n-> Save Text");
		else
			printf("\n   Save Text");
		if (key == 2)
			Draw("\n-> Exit");
		else
			printf("\n   Exit");
		printf("\n");
		printf("\n");
		Text.PrintText();

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
	setlocale(LC_ALL, "Russian");
	TLink::InitMem(100);
	TText Text;
	char File[] = "Text.txt";
	char FileResult[] = "ResultFile.txt";
	int answer=-1;

	Text.ReadFile(File);
	int key = 0;
	int Chose = 0;
	int code;
	int MenuLength;
	char strName[20];
	answer = menu();
	if (answer == 0)
	{
		MenuLength = 3;
		while (1)
		{
			answer = NextMenu(Text, MenuLength);
			if (answer == 2)
				break;
			switch (answer)
			{
			case 0:
				do
				{
					system("cls");
					printf("1)  InsNextLine\n");
					printf("2)  InsNextSection\n");
					printf("3)  InsDownLine\n");
					printf("4)  InsDownSection\n");
					printf("5)  DelNextLine\n");
					printf("6)  DelDownLine\n");

					Text.PrintText();

					code = _getch();
					if (code == 0)
						code = _getch();
					if (code == 80)
					{
						Text.GoNextLink();
					}
					if (code == 72)
					{
						Text.GoPrevLink();
					}
					if (code == 77)
					{
						Text.GoDownLink();
					}
					
				} while (code != 13);
				printf("Action:");
				scanf("%d", &Chose);
				if (Chose == 1)
				{
					printf("Input Name Next Line: ");
					cin >> strName;
					Text.InsNextLine(strName);
				}
				if (Chose == 2)
				{
					printf("Input Name Next Section: ");
					cin >> strName;
					Text.InsNextSection(strName);
				}
				if (Chose == 3)
				{
					printf("Input Name Down Line: ");
					cin>>strName;
					Text.InsDownLine(strName);
				}
				if (Chose == 4)
				{
					printf("Input Name Down Section: ");
					cin >> strName;
					Text.InsDownSection(strName);
				}
				if (Chose == 5)
				{
					Text.DelNextLine();
				}
				if (Chose == 6)
				{
					Text.DelDownLine();
				}
				break;
			case 1:
				Text.SaveText(FileResult);
				printf("\n\nSave File - Successfully\n");
				_getch();
				break;
			}
		}
	}
		printf("Good luck!\n");
	return 0;
}

