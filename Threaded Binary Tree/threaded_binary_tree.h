#ifndef THREADED_BINARY_TREE_H_
#define THREADED_BINARY_TREE_H_

namespace datastructure {

	enum Tag {
		LINK = 0,
		Thread = 1,
	};

	struct BTNode {
		char data;
		BTNode* left, *right;
		Tag ltag, rtag;  // 0 指向 孩子， 1 指向前驱/后继
		
		BTNode() {
			left = right = nullptr;
			ltag = rtag = LINK;
		}
	};

	class ThreadedBinaryTree {
	public:
		ThreadedBinaryTree();   //构造函数

		ThreadedBinaryTree(const ThreadedBinaryTree& t);   //复制构造函数

		void PreThreading();      //先序线索化

		void InThreading();       //中序线索化

		void PreOrder()const;    //先序遍历

		void InOrder()const;    //中序遍历

		void InOrderSearch(char ch)const;  //查找

		void Display()const;   //显示

		~ThreadedBinaryTree();

	private:
		typedef BTNode* BTree;

		void __CreateTBTree(BTree& t);

		void __CopyTBTree(BTree& t, const BTree& t2);

		void __PreThreading(BTree& t);

		void __InThreading(BTree& t);

		void __Display(BTree t, int n)const;

		void __DestroyTBTree(BTree& t);

		BTree head_;

		BTree pre_;
	};


}
#endif // !THREADED_BINARY_TREE_H_

