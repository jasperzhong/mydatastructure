//这是顺序表ADT的测试文件
#include "sequence_list.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using datastructure::Status;
using datastructure::SequenceList;
using datastructure::MergeOrderedLists;
using datastructure::ReverseList;

int main()
{

	{
		
		int n;
		cout << "测试开始，请用debug模式运行程序" << endl;
		cout << "首先请输入顺序表的大小：";
		cin >> n;
		cout << "请输入" << n << "个整数：" << endl;
		SequenceList s_list_1(n);
		system("pause");
		system("cls");

		int elem, pos;
		cout << "初始化功能正常，下面进入插入功能测试" << endl;
		cout << "请输入插入的位置和数值：";
		cin >> pos >> elem;
		while (s_list_1.InsertWithPos(elem, pos) == Status::ERROR) {
			cout << "您输入的位置超出了范围，请重新输入插入的位置和数值：";
			cin >> pos >> elem;
		}
		cout << "插入成功" << endl;
		s_list_1.Display();
		system("pause");
		system("cls");

		cout << "下面进入删除测试" << endl;
		cout << "请输入删除的位置：";
		cin >> pos;
		while (s_list_1.DeleteWithPos(pos, elem) == Status::ERROR) {
			cout << "您输入的位置超出了范围，请重新输入插入的位置和数值：";
			cin >> pos;
		}
		cout << "删除成功，您删除了" << elem << "元素" << endl;
		s_list_1.Display();
		system("pause");

		cout << "下面是按值删除测试，请输入要删除的元素：";
		cin >> elem;
		pos = s_list_1.DeleteFirstElemWithValue(elem);
		if (pos == -1) {
			cout << "未找到该元素" << endl;
		}
		else {
			cout << "删除成功！被删除的元素出现在" << pos << "的位置上" << endl;
		}
		s_list_1.Display();
		system("pause");


		cout << "在进行去掉所有某元素测试前，请输入5个元素使得元素重复" << endl;
		for (int i = 0; i < 5; ++i) {
			cin >> elem;
			s_list_1.InsertWithOrder(elem);
		}
		system("pause");

		cout << "下面是删除所有元素为xxx的测试，请输入要删除的要素" << endl;
		cin >> elem;
		if (s_list_1.DeleteAllElemWithValue(elem) == Status::ERROR) {
			cout << "未找到该元素" << endl;
		}
		else {
			cout << "删除成功" << endl;
		}
		s_list_1.Display();
		system("pause");
		system("cls");

		cout << "下面进入查找测试" << endl;
		cout << "请输入查找的值：";
		cin >> elem;
		pos = s_list_1.SearchWithValue(elem);
		if (pos == -1) {
			cout << "未找到该元素" << endl;
		}
		else {
			cout << "查找成功！该元素出现在" << pos << "的位置上" << endl;
		}
		system("pause");
		system("cls");

		cout << "下面进入逆置测试" << endl;
		cout << "逆置前" << endl;
		s_list_1.Display();
		s_list_1 = ReverseList(s_list_1);
		cout << "逆置后" << endl;
		s_list_1.Display();
		system("pause");
		system("cls");

		cout << "在进行去重测试前，请输入5个元素使得元素重复" << endl;
		for (int i = 0; i < 5; ++i) {
			cin >> elem;
			s_list_1.InsertWithOrder(elem);
		}
		cout << "去重前 ";
		s_list_1.Display();
		s_list_1.Deduplicate();
		cout << "去重后 ";
		s_list_1.Display();
		system("pause");
		system("cls");

		
		cout << "建立两个新的顺序表，并采用有序插入" << endl;
		cout << "请输入第一个新的顺序表大小：";
		cin >> n;
		cout << "请输入" << n << "个整数：" << endl;
		SequenceList s_list_2;
		for (int i = 0; i < n; ++i) {
			cin >> elem;
			s_list_2.InsertWithOrder(elem);
		}
		cout << "输入完毕" << endl;
		s_list_2.Display();
		system("pause");
		cout << "请输入第二个新的顺序表大小：";
		cin >> n;
		cout << "请输入" << n << "个整数：" << endl;
		SequenceList s_list_3;
		for (int i = 0; i < n; ++i) {
			cin >> elem;
			s_list_3.InsertWithOrder(elem);
		}
		cout << "输入完毕" << endl;
		s_list_3.Display();
		system("pause");
		system("cls");


		cout << "下面开始合并两个有序表" << endl;
		SequenceList s_list_4;
		s_list_4 = MergeOrderedLists(s_list_2, s_list_3);
		cout << "下面是合并后的顺序表 ";
		s_list_4.Display();
		cout << "合并功能正常" << endl;
		system("pause");
		system("cls");

		cout << "最后一项测试：销毁所有顺序表" << endl;
	}
	cout << "销毁成功" << endl;
	system("pause");
	system("cls");


	cout << "测试全部结束，功能一切正常" << endl;
	system("pause");
	return 0;
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
56 
13 41 23 23 23
23

41

41 13 41 78 24

5 
6 8 5 2 10
7
7 4 3 6 5 2 1

测试输入2：
100
0 7 12 15 16 15 12 7 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3 4 7 12 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3 4 7 12 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3 4 7 12 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3 4 7 12 0 9 1 14 10 8 8 10 14 1 9 0 12 7 4 3

102 1000
101 1000

101
0
0 1 2 3 4
0

1

1000 1000 100 1000 10000

15
0 7 12 15 16 15 12 7 0 9 1 14 10 8 8
15
0 11 16 15 8 15 16 11 0 3 0 11 16 15 8
*/