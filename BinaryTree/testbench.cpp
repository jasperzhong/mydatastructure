#include "binary_tree.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using datastructure::BTNode;
using datastructure::BinaryTree;
using datastructure::NTNode;
using datastructure::Tree;

int main()
{
	//二叉树
	cout << "建立二叉树——请输入字符序列：";
	auto tree = new BinaryTree();
	
	tree->Display();

	cout << "先序：";
	tree->PreOrder();
	cout << endl;

	cout << "中序：";
	tree->InOrder();
	cout << endl;

	cout << "后序：";
	tree->PostOrder();
	cout << endl;

	cout << "层次：";
	tree->LevelOrder();
	cout << endl;
	
	cout << "深度：";
	cout << tree->Depth() << endl;

	cout << "节点个数：";
	cout << tree->NodesNum() << endl;

	cout << "叶子个数：";
	cout << tree->LeavesNum() << endl;

	cout << "二叉树测试完毕." << endl;

	system("pause");
	system("cls");

	cout << "请输入组织结构，输入0代表结束" << endl;
	auto family_tree = new Tree();

	family_tree->Display();

	cout << "bfs：";
	family_tree->Bfs();
	cout << endl;

	cout << "dfs：";
	family_tree->Dfs();
	cout << endl;

	cout << "深度：";
	cout << family_tree->Depth() << endl;

	cout << "节点个数：";
	cout << family_tree->NodesNum() << endl;

	cout << "叶子个数：";
	cout << family_tree->LeavesNum() << endl;

	cout << "树测试完毕." << endl;

	system("pause");
	return 0;
}