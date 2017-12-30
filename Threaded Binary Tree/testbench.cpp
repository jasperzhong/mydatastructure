#include "threaded_binary_tree.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using datastructure::Tag;
using datastructure::BTNode;
using datastructure::ThreadedBinaryTree;

int main()
{
	auto tree = new ThreadedBinaryTree();
	tree->PreThreading();

	tree->Display();

	tree->PreOrder();

	system("pause");

	return 0;
}