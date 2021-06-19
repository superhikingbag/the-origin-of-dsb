#include <iostream>
#include"Queue.h"//使用时带上Queue.h(在广度优先搜索时用到了队列)
#include"MinHeap.h"//使用时带上MinHeap.h（在最小生成树时Krusal()和Prim()使用)//
#include"UFSets.h"//使用时带上UFSets.h(在最小生成树时Prim()使用)
#include<set>
#include<vector>
#include<map>
#include<deque>
using namespace std;
const int DefaultVertices = 300;
/*class Graph//图的类定义
{
public:
	int maxVertices;
	int numEdges;
	int numVertices;
	virtual int getVertexPos(double vertex);
public:
	const double maxWeight = 1145141919810;//代表无穷大的值（仅仅是暂时定义）
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
	virtual double getValue(int i);
	virtual double getWeigth(int v1, int v2);
	virtual int getFirstNeighbor(int v);
	virtual int getNextNeighbor(int v, int  w);
	virtual bool insertVertex(const double& vertex);
	virtual bool insertEdge(int v1, int v2, double cost);
	virtual bool removeVertex(int v);
	virtual bool removeEdge(int v1, int v2);
};*/
class Graphmtx //:public Graph//图的邻接矩阵类定义（要用到seqList.h）（带权无向图）
{
	friend istream& operator>>(istream& in, Graphmtx& G);
	friend ostream& operator<<(ostream& out, Graphmtx& G);
protected:
	int maxVertices;
	int numEdges;
	int numVertices;
public:
	const double maxWeight = 1145141919810;
	int NumberOfVertices() { return numVertices; }
	int NumOfEdges() { return numEdges; }

	double* VerticesList;//顶点表（使用时换成顺序表类型）
	double** Edge;//一个数组（二维）
	int getVertexPos(double vertex);
	/*{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)return i;
		return -1;
	}*/
public:
	Graphmtx(int sz = DefaultVertices);
	~Graphmtx() { delete[]VerticesList; delete[]Edge; }
	double getValue(int i)
	{
		return (i >= 0 && i <= this->numVertices) ? VerticesList[i] : NULL;
	}
	double getWeight(int v1, int v2)
	{
		return (v1 != -1 && v2 != -1) ? Edge[v1][v2] : 0;
	}
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const double& vertex);
	bool insertEdge(int v1, int v2, double cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
	//void Prim();
	//void Kruskal();
};

int Graphmtx::getVertexPos(double vertex)
{
	for (int i = 0; i < this->numVertices; i++)
		if (VerticesList[i] == vertex)return i;
	return -1;
}
Graphmtx::Graphmtx(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new double[maxVertices];
	Edge = (double**)new double* [maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new double[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
	
}
int Graphmtx::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < this->numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < this->maxWeight)return col;
	}
	return -1;
}
int Graphmtx::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < this->numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < this->maxWeight)return col;
	}
	return -1;
}
bool Graphmtx::insertVertex(const double& vertex)
{
	if (this->numVertices == this->maxVertices)return false;
	VerticesList[this->numVertices++] = vertex;
	return true;
}

bool Graphmtx::removeVertex(int v)
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
bool Graphmtx::insertEdge(int v1, int v2, double cost)
{
	if (v1 > -1 && v1<this->numVertices && v2>-1 && v2 < this->numVertices && Edge[v1][v2] == this->maxWeight)//插入条件的最后一个maxWeight为无穷大值，可以考虑删去该条件
	{
		Edge[v1][v2] = Edge[v2][v1] = cost;
		this->numEdges++;
		return true;
	}
	return false;
}
bool Graphmtx::removeEdge(int v1, int v2)
{
	if (v1 > -1 && v1<this->numVertices && v2>-1 && v2 < this->numVertices && Edge[v1][v2]>0 && Edge[v1][v2] < this->maxWeight)//插入条件的最后两个maxWeight为无穷大值，可以考虑删去该条件
	{
		Edge[v1][v2] = Edge[v2][v1] = this->maxWeight;
		this->numEdges--;
		return true;
	}
	return false;
}
template<class T, class E>
istream& operator>>(istream& in, Graphmtx& G)
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
ostream& operator<<(ostream& out, Graphmtx& G)
{
	int i, j, n, m;
	double e1, e2;
	double w;
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
void DFS(Graphmtx& G, int v, bool visited[]);
void DFS(Graphmtx& G, const double& v)//深度优先搜索的递归算法（主过程）
{
	int i, loc, n = G.NumberOfVertices();
	bool* visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	loc = G.getVertexPos(v);
	DFS(G, loc, visited);
	delete[]visited;
}
void DFS(Graphmtx& G, int v, bool visited[])//深度优先搜索的递归算法（子过程）
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
void BFS(Graphmtx& G, const double& v)
{
	int i, w, n = G.NumberOfVertices();
	bool* visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	int loc = G.getVertexPos(v);
	cout << G.getValue(loc) << " ";
	visited[loc] = true;
	SeqQueue<int> Q;
	Q.EnQueue(loc);
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
struct MSTEdgeNode//最小生成树边结点的类定义
{
	int tail, head;
	double key;
	MSTEdgeNode() :tail(-1), head(-1), key(0) {}
	bool operator <=(MSTEdgeNode& R) { return key <= R.key; }
	bool operator >(MSTEdgeNode& R) { return key > R.key; }
};
class MinSpanTree//最小生成树的类定义
{
public:
	MSTEdgeNode* edgevalue;
	int maxSize, n;
public:
	MinSpanTree(int sz = DefaultVertices - 1) :maxSize(sz), n(0) { edgevalue = new MSTEdgeNode[sz]; }
	int Insert(MSTEdgeNode& item);
	friend ostream& operator<<(ostream& out, MinSpanTree& G);
};
ostream& operator<<(ostream& out, MinSpanTree& G)
{
	for (int i = 0; i <G.n ; i++)
		cout <<"第"<<i+1<<"条边:" << G.edgevalue[i].head+9<<" ->"<<G.edgevalue[i].tail+9<<" \a\n";
	return out;
}
int MinSpanTree::Insert(MSTEdgeNode& item)
{
	edgevalue[n ] = item;
	n++;
	return 1;
}
void Kruskal(Graphmtx& G, MinSpanTree& MST,double g[8][8])//Krusal算法
{
	MSTEdgeNode ed;
	int u, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumOfEdges();
	//cout << n << ' ' << m << endl;
	MinHeap<MSTEdgeNode>H(m);//最小堆，关键码类型为E
	UFSets F(n);//查并集
	for (u = 0; u < n; u++)
		for (v = u + 1; v < n; v++)
			if (G.getWeight(u, v) != maxValue)
			{
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
	count = 1;
	//int cnm = -1;
	while (count < n)
	{
		H.RemoveMin(ed);
		u = F.Find(ed.tail);
		v = F.Find(ed.head);
		if (u != v)
		{
			F.Union(u, v);
			MST.Insert(ed);
			//cout << "#" << ed.key << " ";
			/*for (int kk = 0; kk<8; kk++)
				for (int ss = kk; ss < 8; ss++)
				{
					if (g[kk][ss] == ed.key)
					{
						if (cnm != ed.head)
							cout << kk+9 << " ";
						else cout << ss+9<< " ";
						cnm = ed.head;
					}
				}*/
			count++;
		}
	}
}
void Prim(Graphmtx& G, const double u0, MinSpanTree& MST)
{
	MSTEdgeNode ed;
	int i, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumOfEdges();
	int u = G.getVertexPos(u0);
	MinHeap<MSTEdgeNode>H(m);
	bool Vmst[100];
	for ( i = 0; i < n; i++)
		Vmst[i] = false;
	Vmst[u] = true;
	count = 1;
	do
	{
		v = G.getFirstNeighbor(u);
		while (v != -1)
		{
			if (Vmst[v] == false)
			{
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				//cout <<"#" << ed.head+8 << " ";
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count < n)
		{
			H.RemoveMin(ed);
			if (Vmst[ed.head] == false)/***********************/
			{
				MST.Insert(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	} while (count < n);
}
/*void Graphmtx::Prim()
{
	int start = 9;
	int s1;
	set<double> mtSet;
	mtSet.insert(start);
	double weight;
	while (1)
	{
		weight = 100000.0f;
		start = 8;
		s1 = 8;
		for (set<double>::iterator iter = mtSet.begin(); iter != mtSet.end(); iter++)
		{map<double, double>::iterator curlter=
		}
	}
}*/
