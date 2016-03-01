#define _CRT_SECURE_NO_WARNINGS
#pragma once


#include <string>

const int MaxLen = 81;
/*-------------------------------------------------------------------------------*/
class TLink
{
public:

	char   str[MaxLen]; // Строка в списке ( заголовок)
	TLink* pNext; // Указатель на тот же уровень
	TLink* pDown; // Указатель на подуровень

	TLink();
	TLink(char* _str, TLink* _pNext = NULL, TLink* _pDown = NULL);
	~TLink();
};

/*-------------------------------------------------------------------------------*/
TLink::TLink()
{
	pNext = NULL;
	pDown = NULL;
	str[0] = '\0';
}
/*-------------------------------------------------------------------------------*/
TLink::TLink(char* _str, TLink* _pNext, TLink* _pDown)
{
	pNext = _pNext;
	pDown = _pDown;
	strcpy(str, _str);
}
/*-------------------------------------------------------------------------------*/