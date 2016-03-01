#pragma once

#include "TLink.h"
#include "TStack.h"

/*-------------------------------------------------------------------------*/
class TText
{
private:

	TLink*         pFirst;
	TLink*         pCurr;
	TStack<TLink*> path;

public:

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
};
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
TText::TText(TLink* _pFirst = NULL) : path(100)
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
/*-------------------------------------------------------------------------*/
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
/*-------------------------------------------------------------------------*/
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
/*-------------------------------------------------------------------------*/
void TText::GoPrevLink()
{
	if (!path.IsEmpty())
	{
		pCurr = path.Pop;
	}
}
/*-------------------------------------------------------------------------*/
void TText::GoFirstLink()
{
	pCurr = pFirst;
	path.Clear();
}
/*-------------------------------------------------------------------------*/
void TText::InsNextLine(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pNext = pCurr->pNext;
		pCurr->pNext = tmp;
	}
}
/*-------------------------------------------------------------------------*/
void TText::InsNextSection(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pDown = pCurr->pNext;
		pCurr->pNext = tmp;
	}
}
/*-------------------------------------------------------------------------*/
void TText::InsDownLine(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pNext = pCurr->pDown;
		pCurr->pDown = tmp;
	}
}
/*-------------------------------------------------------------------------*/
void TText::InsDownSection(char* _str)
{
	if (pCurr != NULL)
	{
		TLink* tmp = new TLink(_str);
		tmp->pDown = pCurr->pDown;
		pCurr->pDown = tmp;
	}
}
/*-------------------------------------------------------------------------*/
void TText::DelNextLine()
{
	if (pCurr != NULL)
	{
		TLink* tmp = pCurr->pNext;
		pCurr->pNext = pCurr->pNext->pNext;
		delete tmp;
	}
}
/*-------------------------------------------------------------------------*/
void TText::DelDownLine()
{
	if (pCurr != NULL)
	{
		TLink* tmp = pCurr->pDown;
		pCurr->pDown = pCurr->pDown->pNext;
		delete tmp;
	}
}
/*-------------------------------------------------------------------------*/
void TText::Reset()
{
	pCurr = pFirst;
	path.Clear();

	if (pCurr->pNext != NULL)
		path.Push(pCurr->pNext);
	if (pCurr->pDown != NULL)
		path.Push(pCurr->pDown);
}
/*-------------------------------------------------------------------------*/
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
/*-------------------------------------------------------------------------*/
bool TText::IsEnd()
{
	return (path.IsEmpty());
}
/*-------------------------------------------------------------------------*/
