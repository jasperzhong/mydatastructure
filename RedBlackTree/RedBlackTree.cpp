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
			cout << p->key << "|" <<  p->color << endl << endl;
			_Display(p->left, n + 1);
		}
	}
}



