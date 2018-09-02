#include <iostream>
#include "RedBlackTree.h"
using std::cout;
using std::endl;

namespace datastructure {
	// default constructor
	RedBlackTree::RedBlackTree()
		: nil_(new Node[1]) {
		this->root_ = this->nil_;

		// left, right and parent all point to itself
		this->nil_->left = this->nil_->right = this->nil_->parent = this->nil_;

		// its color is black
		this->nil_->color = BLACK;
	}

	// destructor
	RedBlackTree::~RedBlackTree() {
		// delete all nodes
		_Destroy(this->root_);

		// delete nil_
		delete[]this->nil_;
	}

	void RedBlackTree::_Destroy(Node* p) {
		if (p != this->nil_) {
			_Destroy(p->left);
			_Destroy(p->right);
			delete[]p;
		}
	}


	void RedBlackTree::Insert(const Type& key) {
		Node* y = this->nil_;
		Node* x = this->root_;

		// bi-search
		while (x != this->nil_) {
			y = x;
			if (key < x->key)
				x = x->left;
			else
				x = x->right;
		}
		// create a new node
		Node* z = new Node[1];
		z->key = key;
		z->parent = y;

		// empty
		if (y == this->nil_)
			this->root_ = z;
		else if (z->key < y->key)
			y->left = z;
		else
			y->right = z;

		z->left = this->nil_;
		z->right = this->nil_;
		z->color = RED;

		// for balance
		_InsertFixup(z);
	}

	void RedBlackTree::_InsertFixup(Node* z) {
		Node* y;
		while (z->parent->color == RED) {
			// left
			if (z->parent == z->parent->parent->left) {
				// uncle node
				y = z->parent->parent->right;
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else if (z == z->parent->right) {
					z = z->parent;
					_LeftRotate(z);
				}
				else {
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					_RightRotate(z->parent->parent);
				}
			}
			else { // right
				// uncle node
				y = z->parent->parent->left;
				if (y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else if (z == z->parent->left) {
					z = z->parent;
					_RightRotate(z);
				}
				else {
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					_LeftRotate(z->parent->parent);
				}
			}
		}
		this->root_->color = BLACK;
	}


	void RedBlackTree::_LeftRotate(Node* x) {
		// set y
		Node* y = x->right;

		// turn y's left subtree into x's right subtree
		x->right = y->left;

		if (y->left != this->nil_) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == this->nil_) {
			this->root_ = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void RedBlackTree::_RightRotate(Node* x) {
		// set y
		Node* y = x->parent;

		y->left = x->right;

		if (x->right == this->nil_) {
			x->right->parent = y;
		}
		x->parent = y->parent;
		if (y->parent == this->nil_) {
			this->root_ = x;
		}
		else if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = x;
		}
		x->right = y;
		y->parent = x;
	}

	void RedBlackTree::Print() const {
		_Display(this->root_, 0);
	}

	void RedBlackTree::_Display(Node* p, int n)const {
		if (p != this->nil_) {
			_Display(p->right, n + 1);
			for (int i = 0; i < 10 * n; ++i)
				cout << " ";
			cout << p->key << "|" << p->color << endl << endl;
			_Display(p->left, n + 1);
		}
	}

	// search a node  
	Node* RedBlackTree::Search(const Type& key) const {
		Node* p = this->root_;

		while (p != this->nil_) {
			if (key < p->key)
				p = p->left;
			else if (key > p->key)
				p = p->right;
			else 
				break;
		}

		return p;
	}


	void RedBlackTree::Delete(const Type& key) {
		Node* z = this->Search(key);
		if (z == this->nil_)
			return;
		Node* y = z, *x;
		Color y_original_color = y->color;
		if (z->left == this->nil_) {
			x = z->right;
			this->_Transplant(z, z->right);
		}
		else if (z->right == this->nil_) {
			x = z->left;
			this->_Transplant(z, z->left);
		}
		else {
			y = this->Minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				this->_Transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			this->_Transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (y_original_color == BLACK)
			this->_DeleteFixup(x);
	}


	Node* RedBlackTree::Minimum(Node* z) const {
		Node* p = z;
		if (p == this->nil_) {
			return this->nil_;
		}
		else {
			while (p->left != this->nil_)
				p = p->left;
			return p;
		}
	}

	void RedBlackTree::_Transplant(Node* u, Node* v) {
		if (u->parent == this->nil_)
			this->root_ = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	void RedBlackTree::_DeleteFixup(Node* x) {
		Node* w;
		while (x != this->root_ && x->color == BLACK) {
			if (x == x->parent->left) {
				w = x->parent->right;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					this->_LeftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					this->_RightRotate(w);
					w = x->parent->right;
				}
				else {
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					this->_LeftRotate(x->parent);
					x = this->root_;
				}
			}
			else {
				w = x->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					this->_RightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					this->_LeftRotate(w);
					w = x->parent->left;
				}
				else {
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					this->_RightRotate(x->parent);
					x = this->root_;
				}
			}
		}
		x->color = BLACK;
	}
}



