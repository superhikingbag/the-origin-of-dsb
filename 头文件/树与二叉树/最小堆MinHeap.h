#include <iostream>
#define DefaultSize 10;
using namespace std;
template<class E>
class MinHeap
{
private:
	E* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
public:
	MinHeap(int sz = 10);
	//还少了一种构造函数
	~MinHeap()
	{
		delete[]heap;
	}
	bool Insert(const E& x);
	bool RemoveMin(E& x);
	bool IsEmpty()const
	{
		return(currentSize == 0) ? true : false;
	}
	bool IsFull()const
	{
		return(currentSize == maxHeapSize) ? true : false;
	}
	bool MakeEmpty() { currentSize = 0; }
};
template<class E>
MinHeap<E>::MinHeap(int sz)
{
	maxHeapSize = (10 < sz) ? sz : 10;
	heap = new E[maxHeapSize];
	if (heap == NULL) 
	{
		cout << "NMSL堆内存分配错误" << endl;
		exit(1);
	}
	currentSize = 0;
}
template<class E>
void MinHeap<E>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;//j为左子女位置
	E temp = heap[i];
	while (j < m)
	{
		if (j<m && heap[j]>heap[j + 1])j++;
		if (temp <= heap[j])break;
		else 
		{
			heap[i] = heap[j];
			i = j; 
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}
template<class E>
void MinHeap<E>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	E temp = heap[j];
	while (j>0)
	{
		if (heap[i] <= temp)break;
		else 
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}
template<class E>
bool MinHeap<E>::Insert(const E& x)
{
	if (currentSize == maxHeapSize)
	{
		cerr << "挺萌的，堆满了" << endl;
		return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}
template<class E>
bool MinHeap<E>::RemoveMin(E& x)
{
	if (!currentSize) 
	{
		cout << "堆空了，删了个寂寞" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}