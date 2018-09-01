#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

namespace datastructure {
	// RB Tree only has RED and BLACK
	enum Color {
		RED,
		BLACK
	};

	typedef int Type;

	// tree node
	struct Node {
		Node *left, *right, *parent;
		Type key;
		Color color;
	};

	
	class RedBlackTree {
		public:
			// default constructor
			RedBlackTree();

			// destructor
			~RedBlackTree();

			// insert a new node
			void Insert(const Type& key);

			// search a node  
			Node* Search(const Type& key) const;

			// delete a node
			void Delete(const Type& key);

			// in order traversal
			// it should print an increasing sequence
			void Print() const;

		private:
			// tree root
			Node* root_;
			
			// nil_ points to an empty Node 
			// all nil children point to nil_
			Node* nil_;

			void _InsertFixup(Node* z);

			void _LeftRotate(Node* x);

			void _RightRotate(Node* x);

			void _Destroy(Node* p);

			void _Display(Node* p, int n)const;
	};

}

#endif //REDBLACKTREE_H_
