#include "polynomial.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using datastructure::Polynomial;
using datastructure::Node;

int main()
{
	int m, n;
	int x;
	cout << "请输入第一个一元多项式的大小：";
	cin >> m;
	cout << "请输入" << m << "个数对（系数，指数）\n";
	Polynomial p1(m);

	cout << "请输入第二个一元多项式的大小：";
	cin >> n;
	cout << "请输入" << n << "个数对（系数，指数）\n";
	Polynomial p2(n);

	cout << "请输入一个整数，作为x求值\n";
	cin >> x;
	Polynomial a;
	a = p1 + p2;
	cout << "两个多项式相加结果为:";
	a.Display();
	cout << "其值为：" << a.Eval(x) << endl;

	a = p1 - p2;
	cout << "两个多项式相减结果为:";
	a.Display();
	cout << "其值为：" << a.Eval(x) << endl;

	a = p1*p2;
	cout << "两个多项式相乘结果为:";
	a.Display();
	cout << "其值为：" << a.Eval(x) << endl;
	
	
	system("pause");
	return 0;
}

/*
测试输入:
2
1 0
2 1
3
2 0
3 1
4 2
7

*/