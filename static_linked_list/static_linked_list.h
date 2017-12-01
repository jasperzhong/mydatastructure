#ifndef STATIC_LINKED_LIST_H_
#define STATIC_LINKED_LIST_H_
#include <string>

namespace datastructure {
	// 返回状态
		enum Status {
		OVER_FLOW = -2,
		INFEASIBLE = -1,
		ERROR = 0,
		OK = 1
	};

	typedef int ElementType;

	struct Node {
		std::string str;
		int cur;
	};
	
	typedef Node* List;

	class StaticLinkedList {
	public:
		StaticLinkedList();

		//初始化大小为size的静态链表
		StaticLinkedList(int size);

		//返回静态链表的大小
		int Size()const;

		//返回静态链表是否满了
		bool IsFull()const;

		//返回静态链表是否为空
		bool IsEmpty()const;

		//清空链表
		void Clear();

		//返回指定位置的元素
		Status Retrieve(int position, std::string& x)const;

		//替换指定位置的元素
		Status Replace(int position, const std::string &x);

		//删除指定位置的元素
		Status Remove(int position, std::string &x);

		//在指定位置插入元素
		Status Insert(int position, const std::string &x);

		//寻找元素，返回其位置,-1代表没找到
		int Search(const std::string &x)const;

		//在末尾插入元素
		Status Append(const std::string &x);

		void DisplayAll()const;

		void Display()const;
		//析构函数
		~StaticLinkedList();

	private:
		//模拟分配内存
		int Malloc();
		
		//模拟释放内存
		void Free(int k);

		List space_;
		int max_size_;
	};
}
#endif // !STATIC_LINKED_LIST_H_
