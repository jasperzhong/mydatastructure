#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <string>
#include <unordered_map>

namespace datastructure {
	
	struct HTNode {
		int w;
		char ch;
		HTNode* left;
		HTNode* right;
		HTNode(char c, int ww)
			:ch(c),w(ww) {
			this->left = nullptr;
			this->right = nullptr;
		}
		HTNode() {}
		bool operator < (const HTNode& n)const {
			return w > n.w;
		}
	};

	class HuffmanTree {
	public:
		HuffmanTree(const std::string& s);      //建树

		unsigned int WPL()const;

		std::string  Encode();       //编码

		void Decode(const std::string& s)const;   //解码

		void Print()const;

		~HuffmanTree();
	private:
		typedef HTNode* HTree;

		void __WPL(HTree t, int depth, unsigned int& sum)const;

		void __Encode(HTree t, char ch, char* code, int depth);

		void __Decode(HTree t, const std::string&s, int&pos)const;

		void __Print(HTree t, int depth)const;

		void __Destroy(HTree& t);

		HTree head_;

		std::unordered_map<char, std::string> hash_table_;

		const std::string original_string_;
	};
	
}

#endif // !HUFFMAN_TREE_H_
