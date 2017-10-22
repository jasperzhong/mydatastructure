//这是链表ADT测试文件
#include "linked_list.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using datastructure::Status;
using datastructure::NodeType;
using datastructure::BasicLinkedList;
using datastructure::SinglyLinkedList;
using datastructure::SinglyCircularLinkedList;
using datastructure::DoublyCircularLinkedList;

//共用测试函数
void testbench(BasicLinkedList& b);

int main()
{
	{
		int n, pos, elem;
		cout << "测试开始，请用debug模式运行程序" << endl;

		//	<--------单链表测试-------->
		cout << "首先进行的是单链表的测试" << endl;
		cout << "请输入单链表的元素数目大小" << endl;
		cin >> n;
		cout << "请输入" << n << "个整数:" << endl;
		SinglyLinkedList s_list_1(n);


		testbench(s_list_1);

		cout << "下面进入逆置测试" << endl;
		cout << "逆置前" << endl;
		s_list_1.Display();
		s_list_1.ReverseList();
		cout << "逆置后" << endl;
		s_list_1.Display();
		system("pause");
		system("cls");

		cout << "在进行去重测试前，请输入5个元素使得元素重复" << endl;
		for (int i = 0; i < 5; ++i) {
			cin >> elem;
			s_list_1.InsertWithPos(i+1,elem);
		}
		cout << "去重前 ";
		s_list_1.Display();
		s_list_1.Deduplicate();
		cout << "去重后 ";
		s_list_1.Display();

		cout << "单向链表测试结束" << endl;
		system("pause");
		system("cls");


		//	<--------单向循环链表测试-------->
		cout << "接着进行的是单向循环链表的测试" << endl;
		cout << "请输入单向循环链表的元素数目大小" << endl;
		cin >> n;
		cout << "请输入" << n << "个整数:" << endl;
		SinglyCircularLinkedList c_list_1(n);


		testbench(c_list_1);



		cout << "单向循环链表测试结束" << endl;

		//	<--------双向循环链表测试-------->
		cout << "接着进行的是双向循环链表的测试" << endl;
		cout << "请输入双向循环链表的元素数目大小" << endl;
		cin >> n;
		cout << "请输入" << n << "个整数:" << endl;
		SinglyCircularLinkedList d_list_1(n);
		
		testbench(d_list_1);

		cout << "双向循环链表测试结束" << endl;

		// 检测是否是循环链表
		cout << "检测单链表是否是循环链表:";
		if (IsCircularList(s_list_1) == true)
			cout << "是" << endl;
		else
			cout << "否" << endl;

		cout << "检测单向循环链表是否是循环链表:";
		if (IsCircularList(c_list_1) == true)
			cout << "是" << endl;
		else
			cout << "否" << endl;

		cout << "检测双向循环链表是否是循环链表:";
		if (IsCircularList(d_list_1) == true)
			cout << "是" << endl;
		else
			cout << "否" << endl;

		system("pause");
		system("cls");
		//检测链表是否相交
		cout << "判断链表相交测试" << endl;
		cout << "单链表:";
		s_list_1.Display();
		cout << "单向循环链表：";
		c_list_1.Display();
		cout << "双向循环链表：";
		d_list_1.Display();

		cout << endl;

		cout << "检测单链表和单向循环链表是否相交:" << endl;
		if (IsIntersecting(s_list_1, c_list_1) == true)
			cout << "是" << endl;
		else
			cout << "否" << endl;

		cout << "检测单链表和双向循环链表是否相交:" << endl;
		if (IsIntersecting(s_list_1, d_list_1) == true)
			cout << "是" << endl;
		else
			cout << "否" << endl;

		cout << "检测单向链表和双向循环链表是否相交:" << endl;
		if (IsIntersecting(c_list_1, d_list_1) == true)
			cout << "是" << endl;
		else
			cout << "否" << endl;
	}


	cout << "销毁成功" << endl;
	system("pause");
	system("cls");


	cout << "测试全部结束，功能一切正常" << endl;
	system("pause");
	return 0;
}

void testbench(BasicLinkedList& b) {
	int pos, elem;
	cout << "您输入的的链表是：" << endl;
	b.Display();
	system("pause");
	system("cls");

	cout << "初始化功能正常,下面进入插入功能测试" << endl;
	cout << "请输入插入的位置和数值：" << endl;
	cin >> pos >> elem;
	while (b.InsertWithPos(pos, elem) == Status::ERROR) {
		cout << "您输入的位置超出了范围，请重新输入插入的位置和数值：";
		cin >> pos >> elem;
	}
	cout << "插入成功" << endl;
	b.Display();
	system("pause");
	system("cls");

	cout << "下面进入删除测试" << endl;
	cout << "请输入删除的位置：";
	cin >> pos;
	while (b.DeleteWithPos(pos, elem) == Status::ERROR) {
		cout << "您输入的位置超出了范围，请重新输入插入的位置和数值：";
		cin >> pos;
	}
	cout << "删除成功，您删除了" << elem << "元素" << endl;
	b.Display();
	system("pause");
	system("cls");


	cout << "下面进入查找测试" << endl;
	cout << "请输入查找的值：";
	cin >> elem;
	pos = b.SearchWithValue(elem);
	if (pos == -1) {
		cout << "未找到该元素" << endl;
	}
	else {
		cout << "查找成功！该元素出现在" << pos << "的位置上" << endl;
	}
	system("pause");
	system("cls");
}

/*
测试输入1：

10
13 41 56 78 89 43 24 47 75 64

0 12
12 12
11 23

0
12
5

41

//仅用于单链表去重测试
24 47 41 78 69

测试输入2：
15
99 78 97 96 92 90 88 75 64 79 82 85 87 100 78 

-1 92
20 99
1 100

10000
100
15

99

测试输入3：
100
0 7 12 15 16 15 12 7 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3 4 7 12 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3 4 7 12 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3 4 7 12 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3 4 7 12 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3

102 1000
101 1000

101

1

*/


