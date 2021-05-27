#pragma once
#include <iostream>
using namespace std;
template<class T>
struct DblNode
{
	T data;
	DblNode<T>* lLink, * rLink;
	DblNode(DblNode<T>* left = NULL, DblNode<T>* right = NULL) :lLink(left),rLink(right){}
	DblNode(T value,DblNode<T>* left = NULL, DblNode<T>* right = NULL):data(value), lLink(left), rLink(right) {}
};
template<class T>
class DblList :public LinearList<T>
{
private:
	DblNode<T>* first;
public:
	DblList(T uniqueVal);
	~DblList();
	int Length()const;
	bool IsEmpty() { return first->rLink == first;}
	DblNode<T>* Search(const T& x);
	DblNode<T>* Located(int i, int d);
	bool Insert(int i, const T& x, int d);
	bool Remove(int i, T& x, int d);
};
template<class T>
DblList<T>::DblList(T uniqueVal)
{
	first = new DblList<T>(uniqueVal);
	if (first == NULL)
	{
		cerr << "NMSLÄÚ´æ·ÖÅä´íÎó" << endl;
		exit(1);
	}
	first->rLink = first->lLink = first;
}
template<class T>
int DblList<T>::Length()const
{
	DblNode<T>* current = first->rLink;
	int count = 0;
	while (current!=first)
	{
		current = current->rLink;
		count++;
	}
	return current;
}
template<class T>
DblNode<T>* DblList<T>::Search(const T& x)
{
	DblNode<T>* current = first->rLink;
	while (current != first && current->data != x)current = current->rLink;
	if (current != first)return current;
	else return NILL;
}
template<class T>
DblNode<T>* DblList<T>::Located(int i, int d)
{
	if (first->rLink == first || i == 0)return first;
	DblNode<T>* current;
	if (d == 0)current = first->lLink;
	else current = first->rLink;
	for(int j=1;j<i;j++)
	{
		if (current == first)break;
		else if (d == 0)current = current->lLink;
		else current = current->rLink;
	}
	if (current != first)return current;
	else return NULL;
}
template<class T>
bool DblList<T>::Insert(int i, const T& x, int d)
{
	DblNode<T>current = Located(i, d);

	if (current == NULL)return false;
	DblNode<T>* newNode = new DblNode<T>(x);
	if (d == 0)
	{
		newNode->lLink = current.lLink;
		current.lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink=current£»
	}
	else 
	{
		newNode->rLink = current.rLink;
		current.rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
}
template<class T>
bool DblList<T>::Remove(int i, T& x, int d)
{
	DblNode<T>current = Located(i, d);
	if (current == NULL)return false;
	current.rLink->lLink = current.lLink;
	current.lLink->rLink = current.rLink;
	x = current.data;
	delete current;
	return true;
}













































































































