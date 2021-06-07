// cnm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
 
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <cmath>
#include <string>	
#include <cstdlib>
#include <ctime>
#include<vector>
#include<algorithm>
#include<cctype>
#include"List.h"
#include"SeqList.h"
using namespace std;

using namespace std;

/*int glob = 10;  // global variable

void access_global();
void hide_global();
void change_global();

int main()
{
    cout << "In main() glob is: " << glob << "\n\n";
    access_global();

    hide_global();
    cout << "In main() glob is: " << glob << "\n\n";

    change_global();
    cout << "In main() glob is: " << glob << "\n\n";

    return 0;
}

void access_global()
{
    cout << "In access_global() glob is: " << glob << "\n\n";
}

void hide_global()
{
    int glob = 0;  // hide global variable glob
    cout << "In hide_global() glob is: " << glob << "\n\n";
}

void change_global()
{
    glob = -10;  // change global variable glob
    cout << "In change_global() glob is: " << glob << "\n\n";
}
*/
void Jion(SeqList<int>& A, SeqList<int>& B, SeqList<int>& R)
{
    R = A;
    Intersection(R, B);
}
void Merge(SeqList<int>& A,SeqList<int>& B)
{
    int n = A.Length(), m = B.Length(), i, k, x;
    for (int i=1; i <=m; ++i)
    {
        B.getData(i, x);
        k = A.Search(x);
        if (k == 0)
        {
            A.Insert(n, x);
            n++;
        }
    }
}
int main(int argc, char* argv[])
{
    SeqList <int>A(20);
    SeqList<int> B(20);
    for (int i = 0; i < 14; i++)
        A.Insert(i, i);
    for (int i = 7; i < 19; i++)
    {
        int j = (i - 7);
        B.Insert(j, i);
    }
    cout<<"A:"<< endl;
    for (int i = 0; i <A.Length(); i++)
    {
        int x;
        A.getData(i+1, x);
        cout << x << " ";
    }
    cout<<endl;
    cout << "B:" << endl;
    for(int i=0;i<B.Length();i++)
    {
        int x;
        B.getData(i+1, x);
        cout << x << " ";
    }
    SeqList <int>R=A;
    Intersection(R,B);
    cout <<endl<< "the result of jion is:" << endl;
    for(int i=0;i<R.Length();i++)
    {
        int x;
        R.getData(i+1, x);
        cout << x << " ";
    }
    cout << endl;
    Merge(A, B);
    cout << "the result of Merge is:" << endl;
    for (int i = 0; i < A.Length(); i++)
    {
        int x;
        A.getData(i+1, x);
        cout << x << " ";
    }
    cout << endl;
    cout << "the result of template:\a\n";
    //cout << A << endl << B << endl << R << endl;
    A.output();
    B.output();
    R.output();
    List<int> myList;
    for (int i = 0; i <=10; ++i)
    {
        myList.Insert(i,i);
    }
    cout << "第一次输出myList\a\n";
    myList.output();
    int x = 4;
    myList.Remove(x,x);
    cout << "第2次输出myList\a\n";
    myList.output();
    x = 114514;
    myList.Insert(4, x);
    cout << "第3次输出myList\a\n";
    myList.output();
    return 0;
}








// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
