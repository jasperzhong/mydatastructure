#include "huffman_tree.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using datastructure::HTNode;
using datastructure::HuffmanTree;

int main()
{
	string str;
	cout << "请输入一句话:";
	getline(cin, str);
	auto code = new HuffmanTree(str);

	str = code->Encode();
	
	cout << "下面是将上面的编码进行解码：" << endl;
	code->Decode(str);
	cout << endl;
	system("pause");
	return 0;
}


