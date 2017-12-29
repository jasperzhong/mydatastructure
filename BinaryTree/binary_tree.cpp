#include "binary_tree.h"
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::queue;
using std::stack;

namespace datastructure {

	template<typename T>
	T Max(T lhs, T rhs) {
		return lhs > rhs ? lhs : rhs;
	}


	//<---------------二叉树----------------->
	BinaryTree::BinaryTree() {
		_CreateBTree(this->head_);
	}

	BinaryTree::BinaryTree(const BinaryTree& bt) {
		_CopyBTree(this->head_, bt.head_);
	}

	void BinaryTree::PreOrder()const {
		_PreOrder(this->head_);
	}


	void BinaryTree::InOrder()const {
		_InOrder(this->head_);
	}


	void BinaryTree::PostOrder()const {
		_PostOrder(this->head_);
	}

	void BinaryTree::LevelOrder()const {
		queue<BTNode*> q;
		BTNode* p = this->head_;
		q.push(p);
		//bfs
		while (!q.empty()) {
			p = q.front();
			q.pop();
			if (p) {
				cout << p->data << " ";
				q.push(p->left);
				q.push(p->right);
			}
		}
	}

	unsigned int BinaryTree::Depth()const {
		return _Depth(this->head_);
	}

	unsigned int BinaryTree::NodesNum()const {
		return _NodesNum(this->head_);
	}

	unsigned int BinaryTree::LeavesNum()const {
		return _LeavesNum(this->head_);
	}

	void BinaryTree::Display()const {
		_Display(this->head_, 0);
	}

	BinaryTree::~BinaryTree() {
		_DestroyBtree(this->head_);
	}


	void BinaryTree::_CreateBTree(BTree& p) {
		char ch;
		cin.get(ch);

		if (ch != '#') {
			p = new BTNode[1];
			p->data = ch;

			_CreateBTree(p->left);
			_CreateBTree(p->right);
		}
		else
			return;
	}


	void BinaryTree::_CopyBTree(BTree& p,const BTree& p2) {
		if (p2) {
			p = new BTNode[1];
			p->data = p2->data;

			_CopyBTree(p->left, p2->left);
			_CopyBTree(p->right, p2->right);
		}
	}


	void BinaryTree::_PreOrder(BTree p)const {
		if (p) {
			cout << p->data << " ";
			_PreOrder(p->left);
			_PreOrder(p->right);
		}
	}

	void BinaryTree::_InOrder(BTree p)const {
		if (p) {
			_InOrder(p->left);
			cout << p->data << " ";
			_InOrder(p->right);
		}
	}

	void BinaryTree::_PostOrder(BTree p)const {
		if (p) {	
			_PostOrder(p->left);
			_PostOrder(p->right);
			cout << p->data << " ";
		}
	}

	unsigned int BinaryTree::_Depth(BTree p)const {
		unsigned int left, right;
		if (p) {
			left = _Depth(p->left);
			right = _Depth(p->right);
			return Max(left, right) + 1;    //取左右子树中较大的，加上这一层
		}
		else
			return 0;    
	}

	unsigned int BinaryTree::_NodesNum(BTree p)const {
		unsigned int left, right;
		if (p) {
			left = _NodesNum(p->left);
			right = _NodesNum(p->right);
			return left + right + 1;    //子树节点数 = 左+右+1
		}
		else
			return 0;    //最后一个
	}

	unsigned int BinaryTree::_LeavesNum(BTree p)const {
		unsigned int left, right;
		if (p && (p->left || p->right)) {
			left = _LeavesNum(p->left);
			right = _LeavesNum(p->right);
			return left + right;    //子树叶子数 = 左子树叶子数+右子树叶子数
		}
		else if (p)
			return 1;
		else
			return 0;
	}

	void BinaryTree::_Display(BTree p, int n)const {
		if (p) {
			_Display(p->right, n + 1);
			for (int i = 0; i < 5 * n; ++i)
				cout << " ";
			cout << p->data << endl;
			_Display(p->left, n + 1);
		}
	}

	void BinaryTree::_DestroyBtree(BTree& p) {
		if (p) {
			_DestroyBtree(p->left);
			_DestroyBtree(p->right);
			delete[]p;
		}
	}


	//<---------------树----------------->
	//每次按文件地址那样输入，如 A/B/C/D  0代表结束
	Tree::Tree() {
		string str, temp;
		int size;
		char name[100];
		int cnt = 0;
		this->head_ = new NTNode[1];
		NTNode* p , *pt = this->head_;
		int flag = 0;

		while(true) {
			cin >> str;
			if (str == "0")
				break;
			size = str.size();
			cnt = 0;
			pt = this->head_;
			for (int i = 0; i < size; ++i) {
				if (str[i] == '/' || i == size - 1) {
					if (i == size - 1) {
						if (str[i] != '/') {
							name[cnt] = str[i];
							++cnt;
						}
					}

					name[cnt] = '\0';
					temp = name;
					
					int ok = 0;
					p = new NTNode[1];
					p->data = temp;			

					for (auto ele : pt->children) {
						if (temp == ele->data) {
							pt = ele;
							ok = 1;
							break;
						}
					}

					if (!ok) {
						pt->children.push_back(p);
						pt = p;
					}

					cnt = 0;
					continue;
				}
				else {
					name[cnt] = str[i];
					++cnt;
				}
			}
		}

	}

	Tree::Tree(const Tree& t) {
		_CopyTree(this->head_, t.head_);
	}

	void Tree::_CopyTree(NTree& t, const NTree& t2) {
		if (t2) {
			t = new NTNode[1];
			t->data = t2->data;
			int size = t2->children.size();
			t->children.resize(size);

			for (int i = 0; i < size; ++i)
				_CopyTree(t->children[i],t2->children[i]);

		}
	}

	void Tree::Bfs()const {
		queue<NTNode*> q;
		NTNode* temp = this->head_;
		q.push(temp);
		while (!q.empty()) {
			temp = q.front();
			q.pop();
			if (temp) {
				cout << temp->data << " ";
				for (auto ele : temp->children) {
					q.push(ele);
				}
			}
		}
	}

	void Tree::Dfs()const {
		stack<NTNode*> s;
		NTNode* temp = this->head_;
		s.push(temp);
		while (!s.empty()) {
			temp = s.top();
			s.pop();
			if (temp) {
				cout << temp->data << " ";
				for (auto ele : temp->children) {
					s.push(ele);
				}
			}
		}
	}

	unsigned int Tree::Depth()const {
		return _Depth(this->head_) - 1;
	}

	unsigned int Tree::_Depth(NTree t)const {
		vector<unsigned int> v;
		int size = t->children.size();
		v.resize(size);
		unsigned int max = 0;
		if (t) {
			for (int i = 0; i < size; ++i) {
				v[i] = _Depth(t->children[i]);
			}
			
			for (int i = 0; i < size; ++i) {
				if (v[i] > max)
					max = v[i];
			}

			return max + 1;   //孩子中最大的层数 + 1
		}
		else
			return 0;    
	}

	unsigned int Tree::NodesNum()const {
		return _NodesNum(this->head_) - 1;
	}

	unsigned int Tree::_NodesNum(NTree t)const {
		vector<int> v;
		int size = t->children.size();
		v.resize(size);
		unsigned int sum = 0;
		if (t) {
			for (int i = 0; i < size; ++i) {
				v[i] = _NodesNum(t->children[i]);
			}

			for (int i = 0; i < size; ++i) {
				sum += v[i];
			}

			return sum + 1;   //孩子中所有节点 + 自己
		}
		else
			return 0;    
	}

	unsigned int Tree::LeavesNum()const {
		return _LeavesNum(this->head_);
	}

	unsigned int Tree::_LeavesNum(NTree t)const {
		vector<int> v;
		int size = t->children.size();
		v.resize(size);
		unsigned int sum = 0;
		if (t && (t->children.size() > 0)) {
			for (int i = 0; i < size; ++i) {
				v[i] = _LeavesNum(t->children[i]);
			}

			for (int i = 0; i < size; ++i) {
				sum += v[i];
			}

			return sum;   //孩子中所有叶子
		}
		else if (t)
			return 1;
		else
			return 0;
	}

	void Tree::Display()const {
		_Display(this->head_, -1);
	}

	void Tree::_Display(NTree p, int n)const {
		if (p) {
			for (int i = 0; i < 5 * n; ++i)
				cout << " ";
			cout << p->data << endl;
			for (auto ele : p->children)
				_Display(ele, n + 1);		
		}
	}
	

	Tree::~Tree() {
		_DestroyTree(this->head_);
	}

	void Tree::_DestroyTree(NTree& t) {
		if (t) {
			for (auto ele : t->children)
				_DestroyTree(ele);
			delete[]t;
		}
	}


}