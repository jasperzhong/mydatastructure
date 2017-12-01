#include "static_linked_list.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace datastructure {

	StaticLinkedList::StaticLinkedList() {
		this->space_ = nullptr;
		this->max_size_ = 0;
	}

	//初始化
	StaticLinkedList::StaticLinkedList(int size) {
		space_ = new Node[size+2]; // 第0个放链表的头指针，第1个放闲置聊表的头指针
		this->max_size_ = size;

		space_[0].cur = -1;   //链表
		space_[1].cur = 2;	  //闲置链表
		for (int i = 2; i < size+1; ++i) {
			space_[i].cur = i + 1;
		}
		space_[size + 1].cur = -1;//无后继节点
	}

	//返回静态链表的大小 O(n)
	int StaticLinkedList::Size()const {
		int p = space_[0].cur;
		int j = 0;
		while (p != -1) {
			p = space_[p].cur;
			++j;
		}
			
		return j;
	}

	//返回静态链表是否满了 O(n)
	bool StaticLinkedList::IsFull()const {
		if (Size() == max_size_)
			return true;
		return false;
	}

	//返回静态链表是否为空
	bool StaticLinkedList::IsEmpty()const {
		if (Size() == 0)
			return true;
		return false;
	}

	//清空链表
	void StaticLinkedList::Clear() {
		delete[]space_;  //简单粗暴
		this->max_size_ = 0;
	}

	//模拟分配内存，返回位置，-1代表满了
	int StaticLinkedList::Malloc() {
		int i = space_[1].cur;
		if (i != -1)
			space_[1].cur = space_[i].cur;
		return i;
	}

	//模拟释放内存，将第k个放入闲置链表中
	void StaticLinkedList::Free(int k) {
		space_[k].cur = space_[1].cur;
		space_[1].cur = k;
	}

	
	//返回指定位置的元素
	Status StaticLinkedList::Retrieve(int position, std::string& x)const  {
		int p = space_[0].cur;
		int j = 0;
		while (p != -1) {
			if (++j == position) {
				x = space_[p].str;
				return OK;
			}
			p = space_[p].cur;
		}
		return ERROR;
	}

	//寻找元素，返回其位置
	int StaticLinkedList::Search(const std::string &x)const {
		int p = space_[0].cur;
		int j = 0;
		while (p != -1) {
			++j;
			if (space_[p].str == x) {
				return j;
			}
			p = space_[p].cur;
		}
		return -1;
	}


	//在指定位置插入元素，如果满了就为-1
	Status StaticLinkedList::Insert(int position, const std::string &x) {
		int p = 0;
		int j = 0;

		if (position > max_size_ || position < 1)
			return INFEASIBLE;
		
		int pos = Malloc();
		//满了
		if (pos == -1 )
			return ERROR;
		
		while (space_[p].cur != -1) {
			//插入
			if (++j == position) {
				space_[pos].cur = space_[p].cur;
				space_[p].cur = pos;
				space_[pos].str = x;
				return OK;
			}
			p = space_[p].cur;
		}
		
		if (position - j == 1) {
			space_[pos].cur = space_[p].cur;
			space_[p].cur = pos;
			space_[pos].str = x;
			return OK;
		}
		//应该不会到这里吧
		
	}

	//替换指定位置的元素
	Status StaticLinkedList::Replace(int position, const std::string &x) {
		int p = space_[0].cur;
		int j = 0;
		while (p != -1) {
			if (++j == position) {
				space_[p].str = x;
				return OK;
			}
			p = space_[p].cur;
		}
		return ERROR;
	}

	//删除指定位置的元素
	Status StaticLinkedList::Remove(int position, std::string &x) {
		int p = 0;
		int j = 0;
		int temp;
		if (space_[0].cur == -1)
			return INFEASIBLE;
		while (space_[p].cur != -1) {
			if (++j == position) {
				temp = space_[p].cur;
				x = space_[space_[p].cur].str;
				space_[p].cur = space_[space_[p].cur].cur;
				Free(temp);
				return OK;
			}

			p = space_[p].cur;
		}
		return ERROR;
	}

	//在末尾插入元素
	Status StaticLinkedList::Append(const std::string &x) {
		int p = 0;
		int pos = Malloc();
		if (pos == -1)
			return ERROR;

		while (space_[p].cur != -1) {
			p = space_[p].cur;
		}

		space_[pos].cur = space_[p].cur;
		space_[p].cur = pos;
		space_[pos].str = x;
		return OK;
	}
	
	void StaticLinkedList::DisplayAll() const{
		for (int i = 0; i < max_size_ + 2; ++i) {
			if (space_[i].str == "")
				space_[i].str = "N/A";
			cout << i << " : " << space_[i].str << " : " << space_[i].cur << "        ";
			if ((i + 1) % 3 == 0)
				cout << "\n";
		}
	}

	void StaticLinkedList::Display()const {
		int p = space_[0].cur;
		while (p != -1) {
			cout << space_[p].str << " ";
			p = space_[p].cur;
		}
		cout << "\n";
	}

	//析构函数
	StaticLinkedList::~StaticLinkedList() {
		Clear();
	}

}