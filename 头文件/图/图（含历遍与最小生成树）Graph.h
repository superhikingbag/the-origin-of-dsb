#include <iostream>
#include"Queue.h"//使用时带上Queue.h(在广度优先搜索时用到了队列)
#include"MinHeap.h"//使用时带上MinHeap.h（在最小生成树时Krusal()和Prim()使用)
#include"UFSets.h"//使用时带上UFSets.h(在最小生成树时Prim()使用)
using namespace std;
const int DefaultVertices = 30;
template<class T, class E>
class Graph//图的类定义
{
protected:
	int maxVertices;
	int numEdges;
	int numVertices;
	virtual int getVertexPos(T vertex);
public:
	const E maxWeight = 1145141919810;//代表无穷大的值（仅仅是暂时定义）
	Graph(int sz = DefaultVertices);
	~Graph();
	bool GraphEmpty()const
	{
		if (numEdges == 0)return true;
		else return false;
	}
	bool GraphFull()const
	{
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)return true;
		else return false;
	}
	int NumberOfVertices() { return numVertices; }
	int NumOfEdges() { return numEdges; }
	virtual T getValue(int i);
	virtual E getWeigth(int v1, int v2);
	virtual int getFirstNeighbor(int v);
	virtual int getNextNeighbor(int v, int  w);
	virtual bool insertVertex(const T& vertex);
	virtual bool insertEdge(int v1, int v2, E cost);
	virtual bool removeVertex(int v);
	virtual bool removeEdge(int v1, int v2);
};
/*************图的邻接矩阵表示**************/
template<class T, class E>
class Graphmtx :public Graph<T, E>//图的邻接矩阵类定义（要用到seqList.h）（带权无向图）
{
	friend istream& operator>>(istream& in, Graphmtx<T, E>& G);
	friend ostream& operator<<(ostream& out, Graphmtx<T, E>& G);
private:
	T* VerticesList;//顶点表（使用时换成顺序表类型）
	E** Edge;//一个数组（二维）
	int getVertexPos(T vertex);
	/*{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)return i;
		return -1;
	}*/
public:
	Graphmtx(int sz = DefaultVertices);
	~Graphmtx() { delete[]VerticesList; delete[]Edge; }
	T getValue(int i)
	{
		return (i >= 0 && i <= this->numVertices) ? VerticesList[i] : NULL;
	}
	E getWeight(int v1, int v2)
	{
		return (v1 != -1 && v2 != -1) ? Edge[v1][v2] : 0;
	}
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
};
template<class T, class E>
int Graphmtx<T, E>::getVertexPos(T vertex)
{
	for (int i = 0; i < this->numVertices; i++)
		if (VerticesList[i] == vertex)return i;
	return -1;
}
template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz)
{
	this->maxVertices = sz;
	this->numVertices = 0;
	this->numEdges = 0;
	int i, j;
	VerticesList = new T[this->maxVertices];
	Edge = (E**)new E * [this->maxVertices];
	for (i = 0; i < this->maxVertices; i++)
		Edge[i] = new E[this->maxVertices];
	for (i = 0; i < this->maxVertices; i++)
		for (j = 0; j < this->maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : this->maxWeight;
}
template<class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < this->numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < this->maxWeight)return col;
	}
	return -1;
}
template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < this->numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < this->maxWeight)return col;
	}
	return -1;
}
template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex)
{
	if (this->numVertices == this->maxVertices)return false;
	VerticesList[this->numVertices++] = vertex;
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v)
{
	if (v < 0 || v >= this->numVertices)return false;
	if (this->numVertices == 1)return false;
	int i, j;
	VerticesList[v] = VerticesList[this->numVertices - 1];//用最后一个来填补被删除的
	for (i = 0; i < this->numVertices; i++)
		if (Edge[i][v] > 0 && Edge[i][v] < this->maxWeight)this->numEdges--;
	for (i = 0; i < this->numVertices; i++)
		Edge[i][v] = Edge[i][this->numVertices - 1]; //用最后一列来填补第v列
	this->numVertices--;
	for (j = 0; j < this->numVertices; j++)
		Edge[v][j] = Edge[this->numVertices][j];// 用最后一行来填补第v行
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 > -1 && v1<this->numVertices && v2>-1 && v2 < this->numVertices && Edge[v1][v2] == this->maxWeight)//插入条件的最后一个maxWeight为无穷大值，可以考虑删去该条件
	{
		Edge[v1][v2] == Edge[v2][v1] = cost;
		this->numEdges++;
		return true;
	}
	return false;
}
template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2)
{
	if (v1 > -1 && v1<this->numVertices && v2>-1 && v2 < this->numVertices && Edge[v1][v2]>0 && Edge[v1][v2] < this->maxWeight)//插入条件的最后两个maxWeight为无穷大值，可以考虑删去该条件
	{
		Edge[v1][v2] == Edge[v2][v1] = this->maxWeight;
		this->numEdges--;
		return true;
	}
	return false;
}
template<class T, class E>
istream& operator>>(istream& in, Graphmtx<T, E>& G)
{
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	in >> n >> m;
	for (i = 0; i < n; i++)
	{
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2 >> weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "NMSL边两端点信息有误，重新输入" << endl;
		else
		{
			G.insertEdge(j, k, weight);
			i++;
		}
	}
	return in;
}
template<class T, class E>
ostream& operator<<(ostream& out, Graphmtx<T, E>& G)
{
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumOfEdges();
	cout << n << "," << m << endl;//输出定点数和边数
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			w = G.getWeight(i, j);
			if (w > 0 && w < G.maxWeight)
			{
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
}
/***************************************************************************************/
/**********用邻接表表示图************/
template<class T, class E>
struct Edge//边结点的定义
{
	int dest;
	E cost;
	Edge<T, E>* link;
	Edge() {}
	Edge(int num, E weight) :dest(num), cost(weight), link(NULL) {}
	bool operator!=(Edge<T, E>& R)const
	{
		return (dest != R.dest) ? true : false;
	}
};
template<class T, class E>
struct Vertex
{
	T data;
	Edge<T, E>* adj;//边链表的头指针
};
template<class T, class E>
class Graphlnk :public Graph<T, E>//图的类定义（链表型）
{
	friend istream& operator>>(istream& in, Graphlnk<T, E>& G);
	friend ostream& operator<<(ostream& out, Graphlnk<T, E>& G);
private:
	Vertex<T, E>* NodeTable;
	int getVertexPos(const T vertex);
public:
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
	T getValue(int i)
	{
		return (i >= 0 && i < this->numVertices) ? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);
	bool insertVertex(const T& vertex);
	bool removeVertex(int v);
	bool insertEdge(int v1, int v2, E cost);
	bool removeEdge(int v1, int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
};
template<class T, class E>
int Graphlnk<T, E>::getVertexPos(const T vertex)
{
	for (int i = 0; i < this->numVertices; i++)
		if (NodeTable[i].data == Vertex)return i;
	return -1;
}
template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)
{
	this->maxVertices = sz;
	this->numVertices = 0;
	this->numEdges = 0;
	NodeTable = new Vertex<T, E>[this->maxVertices];
	if (NodeTable == NULL)
	{
		cerr << "NMSL内存分配错误" << endl;
		exit(1);
	}
	for (int i = 0; i < this->maxVertices; i++)NodeTable[i]->adj = NULL;
}
template<class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
	for (int i = 0; i < this->numVertices; i++)
	{
		Edge<T, E>* p = NodeTable[i]->adj;
		while (p != NULL)
		{
			NodeTable[i]->adj = p->link;
			delete p;
			p = NodeTable[i]->adj;
		}
	}
	delete[]NodeTable;
}
template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		Edge<T, E>* p = NodeTable[v]->adj;
		if (p != NULL)return p->dest;
	}
	return -1;
}
template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
	if (v != -1)
	{
		Edge<T, E>* p = NodeTable[v]->adj;
		while (p != NULL && p->dest != w)
		{
			p = p->dest;
		}
		if (p != NULL && p->link != NULL)
			return p->link->dest;
	}
	return -1;
}
template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E>* p = NodeTable[v1]->adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
			if (p != NULL)return p->cost;
		}
	}
	return 0;
}
template<class T, class E>
bool Graphlnk<T, E>::insertVertex(const T& vertex)
{
	if (this->numVertices == this->maxVertices)return false;
	NodeTable[this->numVertices]->data = vertex;
	this->numVertices++;
	return true;
}
template<class T, class E>
bool Graphlnk<T, E>::removeVertex(int v)
{
	if (this->numVertices == 1 || v < 0 || v >= this->numVertices)return false;
	Edge<T, E>* p, * s, * t;
	int i, k;
	while (NodeTable[i]->adj != NULL)
	{
		p = NodeTable[v]->adj;
		k = p->dest;
		s = NodeTable[k]->adj;
		t = NULL;
		while (s != NULL && s->dest != v)
		{
			t = s;
			s = s->link;
		}
		if (s != NULL)
		{
			if (t == NULL)NodeTable[k]->adj = s->link;
			else t->link = s->link;
			delete s;
		}
		NodeTable[v]->adj = p->link;
		delete p;
		this->numEdges--;
	}
	this->numVertices--;
	NodeTable[v]->data = NodeTable[this->numVertices]->data;//填补（用最后一个结点）
	p = NodeTable[v]->adj = NodeTable[this->numVertices]->adj;
	while (p != NULL)
	{
		s = NodeTable[p->dest]->adj;
		while (s != NULL)
		{
			if (s->dest == this->numVertices) { s->dest = v; break; }
			else s = s->link;
		}
	}
	return true;
}
template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)//对于非带权图，其中的weight不要，相应的语句也不要
{
	if (v1 >= 0 && v1 < this->numVertices && v2 >= 0 && v2 < this->numVertices)
	{
		Edge<T, E>* q, * p = NodeTable[v1]->adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL)return false;//找到此边，不插入新边
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1]->adj;
		NodeTable[v1]->adj = p;
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2]->adj;
		NodeTable[v2]->adj = q;
		this->numEdges++;
		return true;
	}
	return false;
}
template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E>* p = NodeTable[v1]->adj, * q = NULL, * s = p;
		while (p != NULL && p->dest != v2)
		{
			q = p;
			p = p->link;
		}
		if (p != NULL)
		{
			if (p == s)NodeTable[v1]->adj = p->link;
			else q->link = p->link;
			delete p;
		}
		else return false;
		p = NodeTable[v2]->adj;
		q = NULL;
		s = p;
		while (p->dest != v1)
		{
			q = p;
			p = p->link;
		}
		if (p == s)NodeTable[v2]->adj = p->link;
		else q->link = p->link;
		delete p;
		return true;
	}
	return false;
}
template<class T, class E>
istream& operator>>(istream& in, Graphlnk<T, E>& G)
{
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	in >> n >> m;
	for (i = 0; i < n; i++)
	{
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2 >> weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "NMSL边两端点信息有误，重新输入" << endl;
		else
		{
			G.insertEdge(j, k, weight);
			i++;
		}
	}
	return in;
}
template<class T, class E>
ostream& operator<<(ostream& out, Graphlnk<T, E>& G)
{
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumOfEdges();
	cout << n << "," << m << endl;//输出定点数和边数
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			w = G.getWeight(i, j);
			if (w > 0 && w < G.maxWeight)
			{
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
	return out;
}
/**********************图的遍历*********************************/
/***深度优先*****/
template<class T, class E>
void DFS(Graph<T, E>& G, const T& v)//深度优先搜索的递归算法（主过程）
{
	int i, loc, n = G.NumberOfVertices();
	bool* visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	loc = G.getVertexPos(v);
	DFS(G, loc, visited);
	delete[]visited;
}
template<class T, class E>
void DFS(Graph<T, E>& G, int v, bool visited[])//深度优先搜索的递归算法（子过程）
{
	cout << G.getValue(v) << " ";
	visited[v] = true;
	int w = G.getFirstNeighbor(v);
	while (w != -1)
	{
		if (visited[w] == false)DFS(G, w, visited);
		w = G.getNextNeighbor(v, w);
	}
}
/****广度优先******/
template<class T, class E>
void BFS(Graph<T, E>& G, const T& v)
{
	int i, w, n = G.NumberOfVertices();
	bool* visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	int loc = G.getVertexPos(v);
	cout << G.getValue(loc) << " ";
	visited[loc] = true;
	Queue<int>Q; Q.EnQueue(loc);
	while (!Q.IsEmpty())
	{
		Q.DeQueue(loc);
		w = G.getFirstNeighbor(loc);
		while (w != -1)
		{
			if (visited[w] == false)
			{
				cout << G.getValue(w) <<" ";
				visited[w] = true;
				Q.EnQueue(w);
			}
			w = G.getNextNeighbor(loc, w);
		}
	}
	delete[]visited;
}
/******************最小生成树*******************/
const double maxValue = 1145141919810;//FLOAT_MAX(暂时定义)机器中可表示的、问题中不可能出现的大数
template<class T, class E>
struct MSTEdgeNode//最小生成树边结点的类定义
{
	int tail, head;
	E key;
	MSTEdgeNode():tail(-1),head(-1),key(0){}
	bool operator <=(MSTEdgeNode<T, E>& R) { return key <= R.key; }
	bool operator >(MSTEdgeNode<T, E>& R) { return key > R.key; }
};
template<class T, class E>
class MinSpanTree//最小生成树的类定义
{
protected:
	MSTEdgeNode<T, E>* edgevalue;
	int maxSize, n;
public:
	MinSpanTree(int sz = DefaultVertices - 1) :maxSize(sz), n(0) { edgevalue = new MSTEdgeNode<T, E>[sz]; }
	int Insert(MSTEdgeNode<T,E>& item);
	friend ostream& operator<<(ostream& out, MSTEdgeNode<T, E>& G);
};
template<class T, class E>
ostream& operator<<(ostream& out, MinSpanTree<T, E>& G)
{
	for (int i = 0; i <= G.n; i++)
		cout << G.edgevalue->head;
}
template<class T, class E>
int MinSpanTree<T, E>::Insert(MSTEdgeNode<T, E>& item)
{
	edgevalue[n + 1] = item;
	n++;
}
template<class T, class E>
void Kruskal(Graph<T, E>& G, MinSpanTree<T, E>& MST)//Krusal算法
{
	MSTEdgeNode<T, E>ed;
	int u, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumberOfVertices();
	MinHeap<MSTEdgeNode<T, E>>H(m);//最小堆，关键码类型为E
	UFSets F(n);//查并集
	for(u=0;u<n;u++)
		for(v=u+1;v<n;v++)
			if (G.getWeigth(u, v) != maxValue)
			{
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeigth(u, v);
				H.Insert(ed);
			}
	count = 1;
	while (count<n)
	{
		H.RemoveMin(ed);
		u = F.Find(ed.tail);
		v = F.Find(ed.head);
		if (u != v)
		{
			F.Union(u, v);
			MST.Insert(ed);
			count++;
		}
	}
}
template<class T, class E>
void Prim(Graph<T, E>& G, const T u0, MinSpanTree<T, E>& MST)
{
	MSTEdgeNode<T, E>ed;
	int i, u, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumOfEdges();
	int u = G.getVertexPos(u0);
	MinHeap<MSTEdgeNode<T, E>>H(m);
	bool Vmst = new bool[n];
	for (i = 0; i < n; i++)Vmst[i] = false;
	Vmst[u] = true;
	count = 1;
	do
	{
		v = G.getFirstNeighbor(u);
		while (v!=-1)
		{
			if (Vmst[v] == false)
			{
				ed.tail = u;
				ed.head = v;
				ed.key = G.getNextNeighbor(u, v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count < n)
		{
			H.RemoveMin(ed);
			if (Vmst[ed.head] == false)
			{
				MST.Insert(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	 }while (count < n);
}





