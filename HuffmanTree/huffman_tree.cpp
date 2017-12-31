#include "huffman_tree.h"
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::endl;

namespace datastructure {

	HuffmanTree::HuffmanTree(const std::string& s) 
		:original_string_(s){
		std::unordered_map<char, int> um;
		std::unordered_map<char, int>::iterator it;
		int size = s.size();
		for (int i = 0; i < size; ++i)
			if(s[i] != '\n')
				um[s[i]]++;     //各个字符出现次数
			
		std::priority_queue<HTNode> pq;  //小顶堆
		HTNode temp;
	
		for (it = um.begin(); it != um.end();++it) {
			pq.push(HTNode(it->first,it->second));
		}

		HTNode *pa, *pb;
		while (pq.size() > 1) {
			pa = new HTNode[1];
			*pa = pq.top();
			pq.pop();
			pb = new HTNode[1];
			*pb = pq.top();
			pq.pop();

			temp.w = pa->w + pb->w;
			temp.left = pa;
			temp.right = pb;
			pq.push(temp);
		}
		temp = pq.top();
		pq.pop();
		this->head_ = new HTNode[1];
		this->head_->w = temp.w;
		this->head_->left = temp.left;
		this->head_->right = temp.right;


	}

	unsigned int HuffmanTree::WPL()const {
		unsigned int sum = 0;
		__WPL(this->head_, 0, sum);
		return sum;
	}

	void HuffmanTree::__WPL(HTree t, int depth, unsigned int& sum)const {
		if (t && (t->left || t->right)) {
			__WPL(t->left, depth + 1, sum);
			__WPL(t->right, depth + 1, sum);
		}
		else
			sum += t->w*depth;
	}

	std::string HuffmanTree::Encode() {
		std::string result;
		char code[1000];
		cout << "每个字符的编码为：" << endl;
		//先编码
		__Encode(this->head_, '0', code, -1);
		//再翻译
		int size = original_string_.size();
		cout << endl;
		cout << "翻译后的编码为：";
		result = "";
		for (int i = 0; i < size; ++i) {
			cout << hash_table_[original_string_[i]];
			result += hash_table_[original_string_[i]];
		}
		cout << endl;
		return result;
	}

	void HuffmanTree::__Encode(HTree t, char ch, char* code, int depth) {
		if (t && (t->left || t->right)) {
			if (depth >= 0)
				code[depth] = ch;
			
			__Encode(t->left, '0', code, depth + 1);
			__Encode(t->right, '1', code, depth + 1);
		}
		else if (t) {
			code[depth] = ch;
			code[depth + 1] = '\0';
			cout << t->ch << " " << code << endl;
			hash_table_[t->ch] = code;
		}
	}

	void HuffmanTree::Decode(const std::string& s)const {
		int pos = 0;
		int size = s.size();
		do {
			__Decode(this->head_, s, pos);
		} while (pos < size);
	}

	void HuffmanTree::__Decode(HTree t, const std::string&s, int&pos)const {
		if (t && (t->left || t->right)) {
			if (s[pos] == '0')
				__Decode(t->left, s, ++pos);
			else if (s[pos] == '1')
				__Decode(t->right, s, ++pos);
		}
		else if (t) {
			cout << t->ch;
		}
	}


	void HuffmanTree::Print()const {
		__Print(this->head_, 0);
	}

	void HuffmanTree::__Print(HTree t, int depth)const {
		if (t) {
			for (int i = 0; i < 5 * depth; ++i)
				cout << " ";
			cout << t->w << endl;
			__Print(t->left, depth + 1);
			__Print(t->right, depth + 1);
		}
	}

	HuffmanTree::~HuffmanTree() {
		__Destroy(this->head_);
	}

	void HuffmanTree::__Destroy(HTree& t) {
		if (t) {
			__Destroy(t->left);
			__Destroy(t->right);
			delete[]t;
		}
	}
}