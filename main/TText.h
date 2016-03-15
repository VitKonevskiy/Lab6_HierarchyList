#pragma once

#include "TLink.h"
#include "TStack.h"
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
using namespace std;
class TText
{
public:

	TLink*pFirst;
	TLink*pCurr;
	TStack<TLink*> path;

	TText(TLink* _pFirst = NULL);
	~TText(){};

	void GoNextLink();
	void GoDownLink();
	void GoPrevLink();
	void GoFirstLink();

	void InsNextLine(char* _str);
	void InsNextSection(char* _str);
	void InsDownLine(char* _str);
	void InsDownSection(char* _str);

	void DelNextLine();
	void DelDownLine();

	void Reset();
	void GoNext();
	bool IsEnd();

	string GetLine();
	void SetLine(string str);

	TLink* ReadSection(ifstream& ifs);
	void   ReadFile(char* fname);
	void   PrintSection(TLink* p);
	void   PrintSection(TLink* p, ofstream &ofs);
	void   PrintText();
	void   SaveText(char* fname);
	void   SaveSection(TLink* p, ofstream & ofs);
};









TText::TText(TLink* _pFirst) : path(100)
{
	if (_pFirst == NULL)
	{
		pFirst = new TLink;
		pCurr = pFirst;
	}
	else
	{
		pFirst = _pFirst;
		pCurr = pFirst;
	}
}

void TText::GoNextLink()
{
	if (pCurr != NULL)
	{
		if (pCurr->pNext != NULL)
		{
			path.Push(pCurr);
			pCurr = pCurr->pNext;
		}
	}
}

void TText::GoDownLink()
{
	if (pCurr != NULL)
	{
		if (pCurr->pDown != NULL)
		{
			path.Push(pCurr);
			pCurr = pCurr->pDown;
		}
	}
}

void TText::GoPrevLink()
{
	if (!path.IsEmpty())
	{
		pCurr = path.Pop();
	}
}

void TText::GoFirstLink()
{
	pCurr = pFirst;
	path.Clear();
}

void TText::InsNextLine(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pNext = pCurr->pNext;
		pCurr->pNext = tmp;
	}
}

void TText::InsNextSection(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pDown = pCurr->pNext;
		pCurr->pNext = tmp;
	}
}

void TText::InsDownLine(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pNext = pCurr->pDown;
		pCurr->pDown = tmp;
	}
}

void TText::InsDownSection(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pDown = pCurr->pDown;
		pCurr->pDown = tmp;
	}
}

void TText::DelNextLine()
{
	if (pCurr != NULL)
	{
		TLink* tmp = pCurr->pNext;
		pCurr->pNext = pCurr->pNext->pNext;
		delete tmp;
	}
}

void TText::DelDownLine()
{
	if (pCurr != NULL)
	{
		TLink* tmp = pCurr->pDown;
		pCurr->pDown = pCurr->pDown->pNext;
		delete tmp;
	}
}

void TText::Reset()
{
	pCurr = pFirst;
	path.Clear();

	if (pCurr->pNext != NULL)
		path.Push(pCurr->pNext);
	if (pCurr->pDown != NULL)
		path.Push(pCurr->pDown);
}

void TText::GoNext()
{
	if (!path.IsEmpty())
	{
		pCurr = path.Pop();
		if (pCurr->pNext != NULL)
			path.Push(pCurr->pNext);
		if (pCurr->pDown != NULL)
			path.Push(pCurr->pDown);
	}
}

bool TText::IsEnd()
{
	return (path.IsEmpty());
}

TLink* TText::ReadSection(ifstream& ifs)
{
	TLink* pHead = new TLink();
	TLink* pTmp = pHead;
	string str;
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str[0] == '}')
			break;
		else
		{
			if (str[0] == '{')
				pTmp->pDown = ReadSection(ifs);
			else
			{
				//char   str1[100] = str.c_str();
				TLink* q = new TLink(str.c_str());
				pTmp->pNext = q;
				pTmp = q;
			}
		}
	}

	if (pHead->pDown == NULL)
	{
		TLink* tmp = pHead->pNext;
		delete pHead;
		pHead = tmp;
	}
	return pHead;
}

void TText::ReadFile(char* fname)
{
	ifstream ifs(fname);
	pFirst = ReadSection(ifs);
}

void TText::PrintSection(TLink* p)
{
	if (p != NULL)
	{
		cout << p->str << endl;
		PrintSection(p->pDown);
		PrintSection(p->pNext);
	}
}


void TText::PrintSection(TLink* p, ofstream &ofs)
{
	if (p != NULL)
	{
		ofs << p->str << endl;
		PrintSection(p->pDown);
		PrintSection(p->pNext);
	}
}

void TText::PrintText()
{
	PrintSection(pFirst);
}

void TText::SaveText(char* fname)
{
	ofstream ofs(fname);
	SaveSection(pFirst, ofs);
}
void TText::SaveSection(TLink* p, ofstream & ofs)
{
	if (p != NULL)
	{
		ofs << p->str << endl;
		//Ñêîáêè
		if (p->pDown != NULL)
		{
			ofs << "}" << endl;
			PrintSection(p->pDown);
		}
		if (p->pNext == NULL)
			ofs << "{" << endl;
		else
			PrintSection(p->pNext);
	}
}


string TText::GetLine()
{
	return this->pCurr->str;
}

void TText::SetLine(string str)
{
	*this->pCurr->str = *str.c_str();
}