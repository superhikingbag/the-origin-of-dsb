#include <iostream>
#include"Stack.h"//使用时带上stack.h
//visit函数未定义
using namespace std;
template<class T>
struct BinTreeNode//二叉树节点类定义
{
	T data;
	BinTreeNode<T>* leftChild, * rightChild;
	BinTreeNode():leftChild(NULL),rightChild(NULL){}
	BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode* r = NULL) :data(x), leftChild(l), rightChild(r) {}
};
template<class T>
class BinaryTree//二叉树
{
protected:
	BinTreeNode<T>root;
	T RefValue;//数据输入停止标志
	void CreateBinTree(istream& in, BinTreeNode<T>*& subTree);//从文件读入建树
	void CreateBinTree(istream& in, BinTreeNode<char>*& BT);//从文件读入建树(使用栈输入广义表char类 )
	void CreateBinTree(ifstream& in, BinTreeNode<T>*& subTree);//以fstream 文件读入前序遍历建树
	bool Insert(BinTreeNode<T>*& subTree, const T& x);
	void destory(BinTreeNode<T>* subTree);
	bool Find(BinTreeNode<T>* subTree,const T& x)const;
	BinTreeNode<T>* Copy(BinTreeNode<T>* orignode);
	int Height(BinTreeNode<T>* subTree);//这个函数和下面在使用上不知道有没有区别
	int Height(BinTreeNode<T>* subTree)const;
	int Size(BinTreeNode<T>* subTree);//这个函数和下面在使用上不知道有没有区别
	int Size(BinTreeNode<T>* subTree)const;
	BinTreeNode<T>* Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current);
	BinTreeNode<T>* Find(BinTreeNode<T>* subTree, const T& x)const;
	void Traverse(BinTreeNode<T>* subTree, ostream& out);//前序遍历输出
	void preOrder(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>* p));//这个函数和下面在使用上不知道有没有区别
	void preOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T>* p));
	void inOrder(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>* p));//这个函数和下面在使用上不知道有没有区别
	void inOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T>* p));
	void postOrder(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>* p));//这个函数和下面在使用上不知道有没有区别
	void postOrder(BinTreeNode<T>& subTree, void(*visit)(BinTreeNode<T>* p));
	friend istream& operator>>(istream& in, BinaryTree<T>& Tree);
	friend ostream& operator<<(ostream& out, BinaryTree<T>& Tree);
	friend int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t);
	friend bool Equal(BinTreeNode<T>* a, BinTreeNode<T>* b);
public:
	BinaryTree():root(NULL){}
	BinaryTree(T value):RefValue(value),root(NULL){}
	BinaryTree(BinaryTree<T>& s);
	BinaryTree(const BinaryTree<T>& s);
	~BinaryTree() { destory(); }
	bool IsEmpty() { return(root == NULL) ? true : false; }
	BinTreeNode<T>* Parent(BinTreeNode<T>* current)
	{
		return(root= NULL||root=current) ?  NULL:Parent(root,current);
	}
	BinTreeNode<T>* LeftChild(BinTreeNode<T>* current)
	{
		return(current != NULL) ? current->leftChild : NULL;
	}
	BinTreeNode<T>* RightChild(BinTreeNode<T>* current)
	{
		return(current != NULL) ? current->rightChild : NULL;
	}
	int Height() { return Height(); }
	int Size() { return Size(root); }
	BinTreeNode<T>* getRoot()const { return root; }
	void preOrder(void(*visit)(BinTreeNode<T>* p)) { preOrder(root, visit); }
	void inOrder(void(*visit)(BinTreeNode<T>* p)) { inOrder(root, visit); }
	void postOrder(void(*visit)(BinTreeNode<T>* p)) { postOrder(root, visit); }
	void levelOrder(void(*visit)(BinTreeNode<T>* p));
	int Insert(const T& item);
	BinTreeNode<T>* Find(T& item)const;
	friend void PrintBTree(BinTreeNode<T>* BT);//前序遍历广义表输出二叉树（递归）
};
template<class T>
void Visit(BinTreeNode<T>* p)//visit函数临时定义
{
	cout << p->data;
}
template<class T>
void BinaryTree<T>::destory(BinTreeNode<T>* subTree)
{
	if (subTree != NULL)
	{
		destory(subTree->leftChild);
		destory(subTree->rightChild);
		delete subTree;
	}
}
template<class T>
BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current)
{
	if (subTree == NULL)return NULL;
	if (subTree->leftChild == current || subTree->rightChild == current)return subTree;
	BinTreeNode<T>* p;
	if ((p = Parent(subTree->leftChild, current)) != NULL)return p;
	else return Parent(subTree->rightChild, current);
}
template<class T>
void BinaryTree<T>::Traverse(BinTreeNode<T>* subTree, ostream& out)
{
	if (subTree != NULL)
	{
		out << subTree->data << " ";
		Traverse(subTree->leftChild, out);
		Traverse(subTree->rightChild, out);
	}
}
template<class T>
istream& operator>>(istream& in, BinaryTree<T>& Tree)
{
	CreateBinTree(in, Tree.root);
	return in;
}
template<class T>
ostream& operator<<(ostream& out, BinaryTree<T>& Tree)
{
	out << "二叉树前序历遍\n";
	Tree.Traverse(Tree.root, out);
	out << endl;
	return out;
}
template<class T>
void BinaryTree<T>::CreateBinTree(istream& in, BinTreeNode<char>*& BT)//从文件读入建树(使用栈输入广义表)
{
	Stack<BinTreeNode<char>*>s;
	BT = NULL;
	BinTreeNode<char>* p, * t;
	int k;//k为处理左右子树的标记
	char ch;
	in >> ch;
	while (ch!=RefValue)
	{
		switch (ch)
		{
		case'(':s.Push(p); k = 1; break;
		case')':s.Pop(t); break;
		case',':k = 2; break;
		default:p = new BinTreeNode(ch);
			if (BT = NULL)BT = p;
			else if (k == 1)
			{
				s.getTop(t);
				t->leftChild = p;
			}
			else
			{
				s.getTop(t);
				t->rightChild = p;
			}
		}
		in >> ch;
	}
}
/**************************************以下仅为伪代码定义（已在类中定义但无法实现【visit/Visit函数】）*********************************************/
template<class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>* p))//递归中序历遍
{
	if (subTree != NULL)
	{
		visit = Visit;//Visit与Visit函数还没搞明白
		inOrder(subTree->leftChild, visit);
		visit(subTree);
		inOrder(subTree->rightChild, visit);
	}
}
template<class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>* p))//递归前序历遍
{
	if (subTree != NULL)
	{
		visit = Visit;//Visit与Visit函数还没搞明白
		visit(subTree);
		preOrder(subTree->leftChild, visit);
		preOrder(subTree->rightChild, visit);
	}
}
template<class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>* p))//递归后序历遍
{
	if (subTree != NULL)
	{
		visit = Visit;//Visit与Visit函数还没搞明白
		preOrder(subTree->leftChild, visit);
		preOrder(subTree->rightChild, visit);
		visit(subTree);
	}
}
/***************************************************************************************************************************************/
template<class T>
int BinaryTree<T>::Size(BinTreeNode<T>* subTree)const
{
	if (subTree == NULL)return 0;
	else return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
}
template<class T>
int BinaryTree<T>::Height(BinTreeNode<T>* subTree)const
{
	if (subTree == NULL)return 0;
	else 
	{
		int i = Height(subTree->leftChild);
		int j = Height(subTree->rightChild);
		return (i < j) ? j + 1 : i + 1;
	}
}
template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s)
{
	root = Copy(root);
}
template<class T>
BinTreeNode<T>* BinaryTree<T>::Copy(BinTreeNode<T>* orignode)
{
	if (orignode == NULL)return NULL;
	BinTreeNode<T>* temp = new BinTreeNode<T>;
	temp->data = orignode->data;
	temp->leftChild = Copy(orignode->leftChild);
	temp->rightChild = Copy(orignode->rightChild);
	return temp;
}
template<class T>
int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t)
{
	return (Equal(s.root, t.root) )? true : false;
}
template<class T>
bool Equal(BinTreeNode<T>* a, BinTreeNode<T>* b)
{
	if (a == NULL && b == NULL)return true;
	if (a != NULL && b = NULL && a->data == b->data && Equal(a->leftChild, b->leftChild) && Equal(a->rightChild, b->rightChild))
		return true;
	else return false;
}
template<class T>
void BinaryTree<T>::CreateBinTree(ifstream& in, BinTreeNode<T>*& subTree)//以fstream 文件读入前序遍历建树
{
	T item;
	if (!in.eof())
	{
		in >> item;
		if (item != RefValue)
		{
			subTree = new BinTreeNode<T>(item);
			if (subTree == NULL)
			{
				cerr << "NMSl" << endl;
				exit(1);
			}
			CreateBinTree(in, subTree->leftChild);
			CreateBinTree(in, subTree->rightChild);
		}
		else subTree = NULL;
	}
}
template<class T>
void PrintBTree(BinTreeNode<T>* BT)//前序遍历广义表输出二叉树（递归）
{
	if (BT != NULL)
	{
		cout << BT->data;
		if (BT->leftChild != NULL || BT->rightChild != NULL)
		{
			cout << '(';
			PrintBTree(BT->leftChild);
			cout << ',';
			if (BT->rightChild！ = NULL)PrintBTree(BT->rightChild);
			cout << ')';
		}
	}
}
/*二叉树前序历遍（非递归）
template<class T>
void BinaryTree<T>::preOrder(void(*visit)(BinTreeNode<T>* p))//一般型
{
	Stack<BinTreeNode<T>*>S;
	BinTreeNode<T>* p = root;
	S.Push(NULL);
	while (p!=NULL)
	{
		visit(p);
		if (p->rightChild != NULL)S.Push(p->rightChild);
		if (p->leftChild != NULL)p = p->leftChild;
		else S.Pop(p);
	}
}
template<class T>
void BinaryTree<T>::preOrder(void(*visit)(BinTreeNode<T>* p))//保证先左子树后右子树
	Stack<BinTreeNode<T>*>S;
	BinTreeNode<T>* p = root;
	S.Push(NULL);
	while (!S.IsEmpty())
	{
		S.Pop(p);
		visit(p);
		if (p->rightChild != NULL)S.Push(p->rightChild);
		if (p->leftChild != NULL)p = p->leftChild;
	}
}
*/
















