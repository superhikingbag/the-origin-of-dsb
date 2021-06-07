#include <iostream>
#include<assert.h>
#include"List.h"//使用时带上单链表List.h
using namespace std;
const int maxSize = 50;
//enum bool{ true,false };
template <class T>
class Queue//队列抽象基类
{
public:
	Queue() {};
	~Queue() {};
	virtual void EnQueue(const T& x) = 0;
	virtual bool DeQueue(T& x) = 0;
	virtual bool getFront(T& x) = 0;
	virtual bool IsEmpty()const=0;
	virtual bool IsFull()const = 0;
	virtual int getSize()const = 0;
};
template <class T>
class SeqQueue :public Queue<T>//顺序队列
{
protected:
	int rear, front;
	T* elements;
	int maxSize;
public:
	SeqQueue(int sz = 10);
	~SeqQueue() { delete[]elements; }
	bool EnQueue(const T& x);
	bool DeQueue(T& x);
	bool getFront(T& x)const;
	void makeEmpty() { front = rear = 0; }
	bool IsEmpty()const { return(front == rear) ? true : false; }
	bool IsFull()const { return((rear+1)%maxSize==front) ? true : false; }
	int getSize()const { return(rear - front + maxSize) & maxSize; }
	friend ostream& operator<<(ostream& os, SeqQueue<T>& Q) ; 
};
template <class T>
SeqQueue<T>::SeqQueue(int sz):front(0), rear(0), maxSize(sz)
{
	elements = new T[maxSize];
	assert(elements != NULL);
}
template <class T>
bool SeqQueue<T>::EnQueue(const T& x)
{
	if (IsFull() == true)return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}
template <class T>
bool SeqQueue<T>::DeQueue(T& x)
{
	if (IsEmpty() == true)return false;
	x = elements[front];
	front = (front + 1) % maxSize;
	return true;
}
template <class T>
bool SeqQueue<T>::getFront(T& x)const
{
	if (IsEmpty() == true)return false;
	x = elements[front];
	return true;
}
template <class T>
ostream& operator << (ostream & os, SeqQueue<T>& Q)
{
	os << "front=" << Q.front << ",rear=" << Q.rear << endl;
	for (int i =Q.front; i != Q.rear; i = (i + 1) % maxSize)
		os << i << ":" << Q.elements[i] << endl;
	return os;
}
template <class T>
class LinkedQueue :public Queue<T>//链式队列
{
protected:
	LinkNode<T>* front, * rear;
public:
	LinkedQueue():rear(NULL),front(NULL){}
	~LinkedQueue() { makeEmpty(); };
	bool EnQueue(const T& x);
	bool DeQueue(T& x);
	bool getFront(T& x)const;
	void makeEmpty();
	bool IsEmpty()const { return(front == NULL) ? true : false; }
	int getSize()const;
	friend ostream& operator<<(ostream& os, LinkedQueue<T>& Q);
};
template <class T>
void LinkedQueue<T>::makeEmpty()
{
	LinkNode<T>* p;
	while (front != NULL)
	{
		p = front;
		front = front->link;
		delete p;
	}
}
template <class T>
bool LinkedQueue<T>::EnQueue(const T& x)
{
	if (front == NULL)
	{
		front = rear = new LinkNode<T>(x);
		if (front == NULL)return false;
	}
	else
	{
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL)return false;
		rear = rear->link;
	}
	return true;
}
template <class T>
bool LinkedQueue<T>::DeQueue(T& x)
{
	if (IsEmpty() == true)return false;
	LinkNode<T>* p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}
template <class T>
bool LinkedQueue<T>::getFront(T& x)const
{
	if (IsEmpty() == true)return false;
	x = front->data;
	return true;
}
template <class T>
int LinkedQueue<T>::getSize()const
{
	LinkNode<T>* p = front;
	int k = 0;
	while (p != NULL)
	{
		p = p->link;
		k++;
	}
	return k;
}
template <class T>
ostream& operator<<(ostream& os, LinkedQueue<T>& Q)
{
	os << "队列中元素个数有" << Q.getSize << endl;
	LinkNode<T>* p = Q.front;
	int i = 0;
	while (p!= NULL)
	{
		os << ++i << "i" << p->data << endl;
		p = p->link;
	}
	return os;
}
































