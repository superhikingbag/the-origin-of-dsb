#include <iostream>
using namespace std;
class UFSets
{
private:
	int* parent;
	int size;
public:
	UFSets(int sz = 12)
	{
		size = sz;
		parent = new int[size];
		for (int i = 0; i < size; i++)
			parent[i] = -1;
	}
	~UFSets()
	{
		delete[]parent;
	}
	void Union(int Root1, int Root2) {
		parent[Root1] += parent[Root2];
		parent[Root2] = Root1;
	}
	int Find(int x) {
		while (parent[x] >= 0)x = parent[x];
		return x;
	}
};
