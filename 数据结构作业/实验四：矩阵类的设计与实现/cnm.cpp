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
#include"CMatrix.h"
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
int main()
{
    CMatrix ml(4, 4), mr(4, 4);
    ml.setUnitMartix();
    ml = ml.operator*(2.0f);
    mr.setUnitMartix();
    cout << "myML:\a\n" << ml << endl;
    cout << "myMR:\a\n" << mr << endl;
    CMatrix r = ml.operator+(mr);
    cout << "myML+myMR:\a\n" << r << endl;
    r = ml.operator-(mr);
    cout << "myML-myMR:\a\n" << r << endl;
    r = ml.operator*(mr);
    cout << "myML*myMR:\a\n" << r << endl;
    r = ml.inverse();
    cout<< "myML^(-1):\a\n" << r << endl;
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
