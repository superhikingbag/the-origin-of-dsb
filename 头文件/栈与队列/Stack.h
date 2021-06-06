#include<assert.h>
#include <iostream>
#include<string>
#include<stdio.h>
#include"List.h"//��ʱ����List.h���ͷ�ļ�
using namespace std;
template<class T>
class Stack 
{public:
	Stack() {};
	virtual void Push(const T& x) = 0;
	virtual bool Pop(T& x) = 0;
	virtual bool getTop(T& x)const = 0;
	virtual bool IsEmpty()const = 0;
	virtual bool IsFull()const = 0;
	virtual int getSzie()const = 0;
};
const int stackIncreament = 20;
template<class T>
class SeqStack :public Stack<T>//˳��ջ
{
private:
	T* elements;
	int top;
	int maxSize;
	void overflowProcess();
public:
	SeqStack(int sz = 50);
	~SeqStack() { delete[]elements; }
	void Push(const T& x);
	bool Pop(T& x);
	bool getTop(T& x);
	bool IsEmpty()const { return (top == -1) ? true : false; }
	bool IsFull()const { return(top == maxSize - 1) ? true : false; }
	int getSize()const{return top + 1;}
	friend ostream& operator<<(ostream& os, SeqStack<T>& s) {}
};
template<class T>
SeqStack<T>::SeqStack(int sz) :top(-1),maxSize(sz)
{
	elements = new T[maxSize];
	assert(elements != NULL);
}
template<class T>
void SeqStack<T>::overflowProcess()
{
	T* newarry = new T[maxSize + stackIncreament];
	if(newarry==NULL)
	{
		cerr << "NMSL�ڴ����ʧ��" << endl;
		exit(1);
	}
	for (int i = 0; i <= top; i++)newarry[i] == elements[i];
	maxSize = maxSize + stackIncreament;
	delete[]elements;
	return newarry;
}
template<class T>
void SeqStack<T>::Push(const T& x)
{
	if (IsFull() == true)overflowProcess();
	elements[++top] = x;
}
template<class T>
bool SeqStack<T>::Pop(T& x)
{
	if (IsEmpty() == true)return false;
	x = elements[top--];
	return true;
}
template<class T>
bool SeqStack<T>::getTop(T& x)
{
	if (IsEmpty() == true)return false;
	x = elements[top];
	return true;
}
template<class T>
ostream& operator<<(ostream& os, SeqStack<T>& s)
{
	os << "top=" << s.top << endl;
	for (int i = 0; i < s.top; i++)
		os << i << ":" << s.elements[i] << endl;
	return os;
}
/*******˫ջ�Ĳ�����ɾ����δ���壩*******/
/*
template<class T>
bool push(DualStack& DS, T x, intd)
{
	if (DS.t[0] + 1 == DS.t[1])return false;
	if (d == 0)DS.t[0]++;
	else DS.t[1]--;
	DS.Vector[DS.[0]++] = x;
	return true;
}
template<class T>
bool POp(DualStack& DS, T x, intd)
{
	if (DS.t[d] == DS.b[d])return false;
	x = DS.Vector[DS.t[d]];
	if (d == 0)DS.t[0]--;
	return true;
}*/
/*****************************************/
template<class T>
class LinkedStack :public Stack<T>
{
private:
	LinkNode<T>* top;
public:
	LinkedStack() :top(NULL) {}
	~LinkedStack() { makeEmpty(); };//������Ҫ�ӣ����𣿣���
	void makeEmpty();
	void Push(const T& x);
	bool Pop(T& x);
	bool getTop(T& x)const;
	bool IsEmpty()const { return(top == NULL) ? true : false; }
	int getSize()const;
	void makeEmpty();
	friend ostream& operator<<(ostream& os, SeqStack<T>& s);
};
template<class T>
void LinkedStack<T>::makeEmpty()
{
	LinkNode<T>* p;
	while (top != NULL)
	{
		p = top;
		top = top->link;
		delete p;
	}
}
template<class T>
void LinkedStack<T>::Push(const T& x)
{
	top = new LinkNode<T>(x, top);
	assert(top != NULL);
}
template<class T>
bool LinkedStack<T>::Pop(T& x)
{
	if (IsEmpty() == true)return false;
	LinkNode<T>* p = top;
	top = top->link;
	x = p->data;
	delete p;
	return true;
}
template<class T>
bool LinkedStack<T>::getTop(T& x)const
{
	if (IsEmpty() == true)return false;
	x = top->data;
	return true;
}
template<class T>
int LinkedStack<T>::getSize()const
{LinkNode<T>* p = top;
int k = 0;
while (top!=NULL)
{
	top = top->link;
	k++;
}
return k;
}
template<class T>
ostream& operator<<(ostream& os, SeqStack<T>& s)
{
	os << "ջ��Ԫ�ظ���=" << s.getSize() << endl;
	LinkNode<T>* p = s.top;
	int i = 0;
	while (P!=NULL)
	{
		os << ++i << ":" << p->data << endl;
		p = p->link;
	}
	return os;
}























































































