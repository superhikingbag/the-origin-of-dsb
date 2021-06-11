#include <iostream>
#include<vector>
#include"Stack.h"//使用时带上stack.h
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
public:
	BinTreeNode<T>*root;
	vector<int>xArray;
	void CreateBinTree(vector<int>& xArray);
	void Insert(BinTreeNode<T>*& an, BinTreeNode<T>*& root);
	friend istream& operator>>(istream& in, BinaryTree<T>& Tree);
	friend ostream& operator<<(ostream& out, BinaryTree<T>& Tree);
	friend int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t);
	friend bool Equal(BinTreeNode<T>* a, BinTreeNode<T>* b);
public:
	BinaryTree():root(NULL){}
	~BinaryTree() { xArray.clear(); }
	/*BinTreeNode<T>* Parent(BinTreeNode<T>* current)
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
	}*/
	void preOrder(BinTreeNode<T>*& root);
	void inOrder(BinTreeNode<T>*& root);
	void postOrder(BinTreeNode<T>*& root);
};
/*template<class T>
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
}*/
template<class T>
int operator==(const BinaryTree<T>& s, const BinaryTree<T>& t)
{
	return (Equal(s.root, t.root) )? true : false;
}
/*template<class T>
bool Equal(BinTreeNode<T>* a, BinTreeNode<T>* b)
{
	if (a == NULL && b == NULL)return true;
	if (a != NULL && b = NULL && a->data == b->data && Equal(a->leftChild, b->leftChild) && Equal(a->rightChild, b->rightChild))
		return true;
	else return false;
}*/
template<class T>
void BinaryTree<T>::CreateBinTree(vector<int>& xArray)
{
	for (vector<int>::iterator iter = xArray.begin(); iter != xArray.end(); ++iter)
	{
		BinTreeNode<int>* an = new BinTreeNode<int>;
		an->data = *iter;
		an->leftChild = NULL;
		an->rightChild = NULL;
		Insert(an, root);
	}
}
template<class T>
void BinaryTree<T>::Insert(BinTreeNode<T>*& an, BinTreeNode<T>*& root)
{
	if (root == NULL)root = an;
	else 
	{
		if (an->data > root->data)Insert(an, root->rightChild);
		else Insert(an,root->leftChild);
	}
}
template<class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>*& root)
{
	if (root == NULL)return;
	else
	{
		cout << root->data<<" ";
		inOrder(root->leftChild);
		inOrder(root->rightChild);
	}
}
template<class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>*& root)
{
	if (root == NULL)return;
	else
	{
		inOrder(root->leftChild);
		cout << root->data << " ";
		inOrder(root->rightChild);
	}
}
template<class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>*& root)
{
	if (root == NULL)return;
	else
	{
		inOrder(root->leftChild);
		inOrder(root->rightChild);
		cout << root->data << " ";
	}
}

















