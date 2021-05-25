#pragma once
#include <iostream>
using namespace std;

 template<class T>
struct LinkNode
{
	T data;
	LinkNode<T>* link;
	LinkNode(LinkNode<T>* ptr = NULL){link = ptr;}
	LinkNode(const T& item, LinkNode<T>* ptr = NULL)
	{
		data = item;
		link = ptr;
	}
};
template<class T>
class List :public LinearList<>
{
private:
	LinkNode<T>* first;
public:
	List(){first = new LinkNode<T>;}
	List(const T& x){first = new LinkNode<T>(x);}
	List(List<T>& L);
	~List() { makeEmpty(); }
	void makeEmpty();
	int Length()const;
	LinkNode<T>* getHead()const { return first; }
	LinkNode<T>* Search(T x);
	LinkNode<T>* Locate(int i);
	bool getData(int i, T& x)const;
	void setData(int i, T& x);
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty()const
	{
		return first->link == NULL ? true : false;
	}
	bool IsEmpty()const
	{
		return false;
    }
	void Sort();
	void inputFront(T endTag);//前插法建新表，每次插入新结点于表的最前端
	void inputRear(T endTag);//后插法建新表，每次插入新结点于表的最后端
	void output();
	List<T>& operator=(List<T>& L);
	};
template<class T>
List<T>::List(List<T>& L)
{
	T value;
	LinkNode<T>* scrptr = L.getHead();
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (scrptr->link != NULL)
	{
		value = scrptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		scrptr = scrptr->link;
	}
	destptr->link = NULL;
}
template<class T>
void List<T>::makeEmpty()
{
	LinkNode<T>* q;
	while (first->link!=NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
}
template<class T>
int List<T>::Length()const
{
	LinkNode<T>* p = first->link;
	int count = 0;
	while(p!=NULL)
	{
		p = p->link;
		count++;
	}
	return count;
}
template<class T>
LinkNode<T>* List<T>::Search(T x)
{
	LinkNode<T>* current = first->link;
	while (current!=NULL)
	{
		if (current->data == x)break;
		else
			current = current->link;
	}
	return current;
}
template<class T>
LinkNode<T>* List<T>::Locate(int)
{
	if (i < 0)return NULL;
	LinkNode<T>* current = first;
	int k = 0;
	while (current != NULL && k < i)
	{
		current = current->link;
		k++;
	}
	return current;
}
template<class T>
bool List<T>::getData(int i, T& x)const
{
	if (i <= 0)return NULL;
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return false;
	else
	{
		x = current->data;
		return true;
	}
}
template<class T>
void List<T>::setData(int i, T& x)
{
	if (i <= 0)return;
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return;
	else current->data = x;
}
template<class T>
bool List<T>::Insert(int i, T& x)
{
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return false;
	LinkNode<T>* newNode = new LinkNode<T>(x);
	if (newNode == NULL)
	{
		cerr << "NMSL内存分配错误" << endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
}
template<class T>
bool List<T>::Remove(int i, T& x)
{
	LinkNode<T>* current = Locate(i-1);
	if (current == NULL || current->link == NULL)return false;
	LinkNode<T>* del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}
template<class T>
void List<T>::output()
{
	LinkNode<T>* current = first->link;
	while (current!=NULL)
	{
		cout << current->data << endl; 
		current = current->link;
	}
}
template<class T>
List<T>& List<T>::operator=(List<T>& L)
{
	T value;
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link!=NULL)
	{
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
	return *this;
}
template<class T>
void List<T>::inputFront(T endTag)//前插法建新表，每次插入新结点于表的最前端
{
	LinkNode<T>* newNode;
	T val;
	makeEmpty();
	cin >> val;
	while (val != endTag)
	{
		newNode = new LinkNode<T>(val);
		if (newNode == NULL)
		{
			cerr << "NMSL内存分配错误" << endl;
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		cin >> val;
	}
}
template<class T>
void inputRear(T endTag)//后插法建新表，每次插入新结点于表的最后端
{
	LinkNode<T>* newNode,*last;
	T val;
	makeEmpty();
	cin >> val;
	last = first;
	while (val != endTag)
	{
		newNode = new LinkNode<T>(val);
		if (newNode == NULL)
		{
			cerr << "NMSL内存分配错误" << endl;
			exit(1);
		}
		last->link = newNode;
		last = newNode;
		cin >> val;
	}
	last->link=NULL:
}
template<class T>
struct CircLinkNode
{
	T data;
	CircLinkNode<T>* link;
	CircLinkNode(CircLinkNode<T>* next = NULL) :link(next){}
	CircLinkNode(T d, CircLinkNode<T>* next = NULL) :data(d), link(next) {}
};
template<class T>
class CircList :public LinearList<T>
{
	private
		CircLinkNode<T>* first, * last;
public:
	CircList(const T& x);
	CircList(CircList<T>& L);
	~CircList();
	int Length()const;
	bool IsEmpty() { return first->link == first ? true : false; }
	CircLinkNode<T>* getHead()const;
	void setHead(CircLinkNode<T>* p);
	CircLinkNode<T>* search(T x);
	CircLinkNode<T>* Locate(int i);
	T* getData(int i);
	void setData(int i, T& x);
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
};














