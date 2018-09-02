#include <iostream>
#include "RedBlackTree.h"

using namespace datastructure;
using std::cout;
using std::endl;

int main()
{
	auto* rbtree = new RedBlackTree;

	rbtree->Insert(1);
	rbtree->Insert(2);
	rbtree->Insert(4);
	rbtree->Insert(5);
	rbtree->Insert(7);
	rbtree->Insert(8);
	rbtree->Insert(11);
	rbtree->Insert(14);
	rbtree->Insert(15);


	rbtree->Print();
	rbtree->Delete(5);

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	rbtree->Print();
	delete rbtree;

	system("pause");
}