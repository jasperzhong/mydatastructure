#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <vector>
#include <string>

namespace datastructure {

	//二叉树的节点结构
	struct BTNode {
		char data;
		BTNode *left, *right;
		BTNode() {
			left = right = nullptr;
		}
	};

	//二叉树
	class BinaryTree {
	public:
		BinaryTree();   //默认构造函数  auto family_tree = new BinaryTree();
		
		BinaryTree(const BinaryTree& bt);  //复制构造函数  auto another_family_tree = new Binary(family_tree);

		BinaryTree& operator=(const BinaryTree& bt)=delete;  //禁止直接赋值 因为构造的时候肯定要建树,所以赋值没意义

		void PreOrder()const;  //先序遍历

		void InOrder()const;	 //中序遍历

		void PostOrder()const;  //后序遍历

		void LevelOrder()const;  //层次遍历

		unsigned int Depth()const; //深度

		unsigned int NodesNum()const; //节点个数

		unsigned int LeavesNum()const; //叶子个数

		void Display()const;   //显示

		~BinaryTree();

	protected:
		typedef BTNode* BTree;

		void _CreateBTree(BTree& p);   //建树

		void _CopyBTree(BTree& p,const BTree& p2);   //复制树

		void _PreOrder(BTree p)const; //内部实现

		void _InOrder(BTree p)const; //内部实现

		void _PostOrder(BTree p)const; //内部实现

		unsigned int _Depth(BTree p)const; //内部实现

		unsigned int _NodesNum(BTree p)const;  //内部实现

		unsigned int _LeavesNum(BTree p)const;  //内部实现

		void _Display(BTree p, int n)const;   //内部实现

		void _DestroyBtree(BTree& p);
	private:
		
		BTree head_;
	};

	//N叉树的节点结构
	struct NTNode {
		std::string data;
		std::vector<NTNode*> children;
	};

	//推广：n叉树
	class Tree {
	public:
		Tree();

		Tree(const Tree& t);

		Tree& operator=(const Tree& t)=delete;

		void Bfs()const; //广度优先遍历

		void Dfs()const;  //深度优先遍历

		unsigned int Depth()const; //深度

		unsigned int NodesNum()const; //节点个数

		unsigned int LeavesNum()const; //叶子个数

		void Display()const;   //显示

		~Tree();
	protected:
		typedef NTNode* NTree;
		void _CopyTree(NTree& t, const NTree& t2);

		unsigned int _Depth(NTree t)const;

		unsigned int _NodesNum(NTree t)const;

		unsigned int _LeavesNum(NTree t)const;

		void _Display(NTree p, int n)const;   //内部实现

		void _DestroyTree(NTree& t);
	private:
		NTNode* head_;
	};
}

#endif // BINARY_TREE_H_

