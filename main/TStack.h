#pragma once
// ������������ ��������� ������ - ����

// |   | 4
// |   | 3
// |   | 2
// |   | 1 
// |___| 0
//      -1

//const int MaxStackSize = 1000;
#define MaxStackSize 1000


using namespace std;

template <class T>
class TStack
{
private:
	int MaxSize;  // ������ �����
	int Index;    // ������ �������� ��������
	T*  mas;      // ��� ���� � ���� �������
public:
	TStack(int len = 10)
	{
		if ((len <= 0) || (len > MaxStackSize))
			throw len;
		else
		{
			MaxSize = len;
			Index = -1;
			mas = new T[MaxSize];
		}
	}/*-------------------------------------------------------------------------*/

	TStack(const TStack& s)
	{
		MaxSize = s.MaxSize;
		Index = s.Index;
		mas = new T[MaxSize];
		for (int i = 0; i < (Index + 1); i++)
			mas[i] = s.mas[i];
	}/*-------------------------------------------------------------------------*/

	~TStack()
	{
		delete[] mas;
	}/*-------------------------------------------------------------------------*/

	TStack& operator= (const TStack& s)
	{
		if (MaxSize != s.MaxSize)
		{
			delete[] mas;
			MaxSize = s.MaxSize;
			mas = new T[MaxSize];
		}
		Index = s.Index;
		for (int i = 0; i < (MaxSize + 1); i++)
			mas[i] = s.mas[i];
		return *this;
	}/*-------------------------------------------------------------------------*/

	//�������� �� ������� � �������
	bool IsEmpty()
	{
		if (Index == -1)
			return true;
		return false;
	}/*-------------------------------------------------------------------------*/

	bool IsFull()
	{
		if (Index == (MaxSize - 1))
			return true;
		return false;
	}

	//�������� �� ������

	T Top()               // ����������� ������� ������� �����
	{
		return mas[Index];
	}/*-------------------------------------------------------------------------*/

	T Pop()               // ���������� ������� ������� �����
	{
		if (IsEmpty())
			throw Index;
		else
			return mas[Index--];
	}/*-------------------------------------------------------------------------*/

	void Push(const T n)   // �������� ������� � ����
	{
		if (IsFull())
			throw Index;
		else
		{
			Index++;
			mas[Index] = n;
		}
	}/*-------------------------------------------------------------------------*/

	void Clear()           // �������� ����
	{
		Index = -1;
	}
};//----------------------------------------------------------------------------------------------------------------------------