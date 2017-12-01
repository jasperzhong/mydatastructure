#include "static_linked_list.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using datastructure::StaticLinkedList;
using datastructure::Node;
using datastructure::Status;

int main()
{
	int pos;
	string str;
	cout << "1) 按输入序列： Jan、Feb、Mar、Apr、May建立初始链表。\n";
	StaticLinkedList s(7);
	string tmp[] = { "Jan","Feb","Mar","Apr","May" };
	for (int i = 0; i < 5; ++i) {
		s.Append(tmp[i]);
	}
	cout << endl;
	s.DisplayAll();
	cout << endl;
	cout << "当前链表为：";
	s.Display();

	cout << "2)在Feb之前，May之后，先后输入Jun、Oct\n";
	s.Append("Jun");
	s.Append("Oct");
	cout << endl;
	s.DisplayAll();
	cout << endl;
	cout << "当前链表为：";
	s.Display();

	cout << "3)先后删除Mar和Jan\n";
	pos = s.Search("Mar");
	s.Remove(pos, str);
	pos = s.Search("Jan");
	s.Remove(pos, str);
	cout << endl;
	s.DisplayAll();
	cout << endl;
	cout << "当前链表为：";
	s.Display();

	cout << "4)在Apr之前插入Dec\n";
	pos = s.Search("Apr");
	s.Insert(pos, "Dec");
	cout << endl;
	s.DisplayAll();
	cout << endl;
	cout << "当前链表为：";
	s.Display();


	system("pause");
	return 0;
}