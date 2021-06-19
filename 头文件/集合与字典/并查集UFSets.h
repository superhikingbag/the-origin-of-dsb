#include <iostream>
#define DefaultSize 10;
using namespace std;
class UFSets
{
private:
	int* parent;
	int size;
public:
	UFSets(int sz = 10);
	~UFSets()
	{
		delete[]parent;
	}
	UFSets& operator=(UFSets& R);
	void Union(int Root1, int Root2);
	int Find(int x);
	void WeightUnion(int Root1, int Root2);
};
UFSets::UFSets(int sz)
{
	size = sz;
	parent = new int[size];
	for (int i = 0; i < size; i++)
		parent[i] = -1;
}
int UFSets::Find(int x)
{
	while (parent[x] >= 0)x = parent[x];
	return x;
}
void UFSets::Union(int Root1, int Root2)
{
	parent[Root1] += parent[Root2];
	parent[Root2] = Root1;
}