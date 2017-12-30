#include "threaded_binary_tree.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

namespace datastructure {

	//输入先序序列
	ThreadedBinaryTree::ThreadedBinaryTree() {
		this->head_ = nullptr;
		__CreateTBTree(this->head_);
	}

	void ThreadedBinaryTree::__CreateTBTree(BTree& t) {
		char ch;
		cin.get(ch);

		if (ch != '#') {
			t = new BTNode[1];
			t->data = ch;

			__CreateTBTree(t->left);
			__CreateTBTree(t->right);
		}
		else
			return;
	}


	ThreadedBinaryTree::ThreadedBinaryTree(const ThreadedBinaryTree& t) {
		this->head_ = nullptr;
		__CopyTBTree(this->head_, t.head_);
	}

	void ThreadedBinaryTree::__CopyTBTree(BTree& t, const BTree& t2) {
		if (t2) {
			t = new BTNode[1];
			t->data = t2->data;

			__CopyTBTree(t->left, t2->left);
			__CopyTBTree(t->right, t2->right);
		}
	}


	void ThreadedBinaryTree::PreThreading() {
		this->pre_ = nullptr;
		__PreThreading(this->head_);
	}

	void ThreadedBinaryTree::InThreading() {
		this->pre_ = nullptr;
		__InThreading(this->head_);
	}

	void ThreadedBinaryTree::__PreThreading(BTree& t) {
		if (t) {
			//如果左孩子为空,应该指向前驱
			if (!t->left) {
				t->ltag = Thread;
				t->left = pre_;
			}

			//如果右孩子为空，指向后继，由于后继还不知道是谁，先设置为thread
			if (!t->right)
				t->rtag = Thread;

			//如果前驱的右孩子指向后继，那么就应该指向当前位置
			if (pre_ && pre_->rtag == Thread)
				pre_->right = t;

			//更新前驱
			pre_ = t;

			//递归遍历左右子树
			if (t->ltag == LINK)
				__PreThreading(t->left);

			if (t->rtag == LINK)
				__PreThreading(t->right);
		}
	}

	void ThreadedBinaryTree::__InThreading(BTree& t) {
		if (t) {

			//递归遍历左子树
			if (t->ltag == LINK)
				__InThreading(t->left);

			//如果左孩子为空,应该指向前驱
			if (!t->left) {
				t->ltag = Thread;
				t->left = pre_;
			}

			//如果右孩子为空，指向后继，由于后继还不知道是谁，先设置为thread
			if (!t->right)
				t->rtag = Thread;

			//如果前驱的右孩子指向后继，那么就应该指向当前位置
			if (pre_ && pre_->rtag == Thread)
				pre_->right = t;

			//更新前驱
			pre_ = t;

			//递归遍历右子树
			if (t->rtag == LINK)
				__InThreading(t->right);
		}
	}

	void ThreadedBinaryTree::PreOrder()const {
		BTNode* p = this->head_;
		cout << p->data;
		//不管怎样 right都是后继啊
		while (p->right) {
			if (p->ltag == LINK)
				p = p->left;
			else
				p = p->right;
			cout << p->data;
		}
		cout << endl;
	}


	void ThreadedBinaryTree::InOrder()const {
		BTNode* p = this->head_;
		while (p->ltag == LINK) p = p->left;
		cout << p->data;

		while (p->right) {
			//是thread的后直接就是后继
			if (p->rtag == Thread) {
				p = p->right;
			}
			else {
				//中序下，右孩子不是其直接后继
				p = p->right;
				//先访问左孩子
				while (p->ltag == LINK) p = p->left;
			}
			cout << p->data;
		}
	}


	//查找中序遍历中前驱和后继的
	void ThreadedBinaryTree::InOrderSearch(char ch)const {
		char str[1000];
		int ltag[1000];
		int rtag[1000];
		int cnt = 0, pos = -1;
		
		BTNode* p = this->head_;
		while (p->ltag == LINK) p = p->left;

		if (p->data == ch)
			pos = cnt;
		str[cnt] = p->data;
		ltag[cnt] = p->ltag;
		rtag[cnt] = p->rtag;
		++cnt;
		while (p->right) {
			//是thread的后直接就是后继
			if (p->rtag == Thread) {
				p = p->right;
			}
			else {
				//中序下，右孩子不是其直接后继
				p = p->right;
				//先访问左孩子
				while (p->ltag == LINK) p = p->left;
			}
			if (p->data == ch)
				pos = cnt;
			str[cnt] = p->data;
			ltag[cnt] = p->ltag;
			rtag[cnt] = p->rtag;
			++cnt;
		}

		if (pos == -1) {
			cout << "Not found" << endl;
			return;
		}
		str[cnt] = '\0';
		cout << str << endl;

		if (pos == cnt - 1) {
			cout << "succ is NULL" << endl;
		}
		else {
			cout << "succ is " << str[pos + 1] << rtag[pos + 1] << endl;
		}

		if (pos > 0) {
			cout << "prev is " << str[pos - 1] << ltag[pos - 1] << endl;
		}
		else {
			cout << "prev is NULL" << endl;
		}
	}



	void ThreadedBinaryTree::__Display(BTree t, int n)const {
		if (t) {
			if(t->rtag == LINK)
				__Display(t->right, n + 1);
			for (int i = 0; i < 5 * n; ++i)
				cout << " ";
			cout << t->data << t->ltag << t->rtag << endl;
			if(t->ltag == LINK)
				__Display(t->left, n + 1);
		}
	}

	void ThreadedBinaryTree::Display()const {
		__Display(this->head_, 0);
	}


	ThreadedBinaryTree::~ThreadedBinaryTree() {
		__DestroyTBTree(this->head_);
	}

	void ThreadedBinaryTree::__DestroyTBTree(BTree& t) {
		if (t) {
			if (t->ltag == LINK)
				__DestroyTBTree(t->left);
			if (t->rtag == LINK)
				__DestroyTBTree(t->right);
			delete[]t;
		}
	}

}