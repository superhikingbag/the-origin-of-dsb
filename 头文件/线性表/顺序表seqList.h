#pragma once
#include<stdlib.h>
#include"linearList.h"
#include <iostream>
using namespace std;
const int defaultSize = 100;
template <class T>
class SeqList :public LinearList<T> 
{
protected:
	T* data;
	int maxsize;
	int last;
	void reSize(int newSize);
public:
	SeqList(int sz = defaultSize);
	SeqList(SeqList<T>& L);
	~SeqList() { delete[]data; }
	int Size()const { return maxsize; }
	int Length()const { return last + 1; }
	int Search(T& x)const;
	int Locate(int i)const;
	bool getData(int i, T& x)const
	{
		if (i > 0 && i <= last + 1)
		{
			x = data[i - 1];
			return true;
		}
		else
			return false;
	}
	void setData(int i, T& x)
	{
		if(i>0&&i<=last+1)
			data[i-1]=x
	}
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty()
	{
		return(last == -1) ? true : false;
	}
	void input();
	void output();
	SeqList<T>operator=(SeqList<T>& L);
};
template <class T>
SeqList<T>::SeqList(int sz)
{
	if (sz > 0)
	{
		maxsize = sz;
		last = -1;
		if (data == NULL)
		{
			cerr << "NMSL内存分配错误" << endl;
			exit(1);
		}
	}
}
template <class T>
SeqList<T>::SeqList(SeqList<T>& L)
{
	maxsize = L.Size();
	last = L.Length() - 1;
	T value;
	data = new T[maxsize];
	if (data == NULL)
	{
		cerr << "NMSL内存分配错误" << endl;
		exit(1);
	}
	for (int i = 1; i <= last + 1; i++)
	{
		L.getData(i, value);
		data[i - 1] = value;
	}
}
template <class T>
void SeqList<T>::reSize(int newSize)
{
	if (newSize <= 0)
	{
		cerr << "无效的数组大小" << endl;
		exit(1);
	}
	if (newSize != maxsize)
	{
		T* newarray = new T[newSize];
		if(newarray==NULL)
		{
			cerr << "NMSL内存分配错误" << endl;
			exit(1);
		}
		int n = last + 1;
		T* srcptr = data;
		T* destptr = newarray;
		while(n--)
			*destptr++=*srcptr++;
		delete[]data;
		data = newarray;
		maxsize = newSize; 
	}
}
template <class T>
int SeqList<T>::Search(T& x)const
{
	for (int i = 0; i <= last; i++)
		if (data[i] == x)
			return i + 1;
	return 0;
}
template <class T>
int SeqList<T>::Locate(int i)const
{
	for (i >= 1 && i <= last + 1)
		return i;
	else
	return 0;
}
template <class T>
bool SeqList<T>::Insert(int i, T& x)
{
	if (last == maxSize - 1)
		return false;
	if (i<0 || i>last + 1)
		return false;
	for (int j = last; j > +i; j--)
		data[j + 1] = data[j];
	data[j] = x;
	last++;
	return true;
}
template <class T>
bool SeqList<T>::Remove(int i, T& x)
{
	if (last ==  - 1)
		return false;
	if (i<1 || i>last + 1)
		return false;
	x = data[i - 1];
	for (int j = i; j <= last; j++)
		data[j - 1] = data[j];
	last--;
	return true;
}
template <class T>
void SeqList<T>::input()
{
	cout<<"开始建立顺序表，请输入表中元素个数："
		while (1)
		{
			cin >> last;
			if (last <= maxsize - 1)break;//这有问题，逻辑不通
			cout << "表元素个数输入有误，范围不能超过" << maxsize - 1 << ":";
		}
	for (int i = 0; i <= last; i++)
	{
		cin >> data[i];
		cout << i + 1 << endl;
	}
}
template <class T>
void SeqList<T>::output()
{
	cout << "顺序表当前元素最后位置为："last << endl;
	for (int i = 0; i <= last; i++)
		cout << "#" << i + 1 << ":" << data[i] << endl;

}
template <class T>
SeqList<T>SeqList<T>::operator=(SeqList<T>& L1)
{
	maxsize = L1.Size();
	last = L1.Length() - 1;
	T value;
	data = new T[maxsize];
	if (data == NULL)
	{
		cerr << "NMSL内存分配错误" << endl;
		exit(1);
	}
	for (int i = 1; i <= last + 1; i++)
	{
		L1.getData(i, value);
		data[i - 1] = value;
	}
}
/*void union(SeqList<int>& LA, SeqList<int>& LB)//合并LA和LB，存于A
{
	int n = LA.Length(), m = LB.Length(), i, k, x;
	for (int i; i <= m; i++)
	{
		LB.getData(i, x);
		k = LA.Search(x);
		if (k == 0)
		{
			LA.Insert(n, x);
			n++;
		}
	}
}*/
void Intersection(SeqList<int>& LA, SeqList<int>& LB)//交集LA和LB，存于A
{
	int n = LA.Length(), m = LB.Length(), i=1, k, x;
	while (i < n)
	{
		LA.getData(i, x);
		k = LB.Search(x);
		if (k == 0)
		{
			LA.Remove(i, x);
			n--;
		}
		else
			i++;
	}
}


























