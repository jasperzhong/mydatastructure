//这是顺序表ADT的实现文件
#include "sequence_list.h"
#include <iostream>
#include <cstring>

namespace datastructure {
	//C++版realloc
	template<typename T>
	T* Realloc(T* oldptr, int oldsize, int newsize) {
		//重新申请内存
		T* newptr = new T[newsize];
		//内存移动
		memmove(newptr, oldptr, oldsize*sizeof(T));
		//释放原内存
		delete[]oldptr;
		return newptr;
	}

	//默认构造函数，顺序表的初始化
	SequenceList::SequenceList() {
		this->list_ptr_ = new ElementType[LIST_INIT_SIZE_];
		this->list_size_ = 0;
		this->list_max_size_ = LIST_INIT_SIZE_;
	}

	//构造函数，给定最大个数n
	SequenceList::SequenceList(int n) {
		this->list_ptr_ = new ElementType[n + LIST_INC_SIZE];
		for (int i = 0; i < n; ++i)
			std::cin >> this->list_ptr_[i];

		this->list_size_ = n;
		this->list_max_size_ = n + LIST_INC_SIZE;
		Display();
	}

	//赋值运算符重载（深拷贝）
	SequenceList & SequenceList::operator=(const SequenceList& s) {
		//如果等于自己，直接返回
		if (this == &s)
			return *this;
		//先释放原内存
		delete[]this->list_ptr_;
		//申请新的内存
		this->list_ptr_ = new ElementType[s.list_max_size_];
		//内存移动
		memmove(this->list_ptr_, s.list_ptr_, s.list_max_size_*sizeof(ElementType));
		this->list_max_size_ = s.list_max_size_;
		this->list_size_ = s.list_size_;
		return *this;
	}

	//复制构造函数（深拷贝）
	SequenceList::SequenceList(const SequenceList& s) {
		this->list_ptr_ = new ElementType[s.list_max_size_];
		memmove(this->list_ptr_, s.list_ptr_, s.list_max_size_*sizeof(ElementType));
		this->list_max_size_ = s.list_max_size_;
		this->list_size_ = s.list_size_;
	}

	//在第i个元素前插入，时间复杂度为O(n)
	Status SequenceList::InsertWithPos(ElementType elem, int pos) {
		//合法值在 1 <= i <= list_size_ + 1
		if (pos < 1 || pos > this->list_size_ + 1)
			return ERROR;
		//超过大小，增大容量
		if (this->list_size_ >= this->list_max_size_) {
			this->list_max_size_ += LIST_INC_SIZE;
			this->list_ptr_ = Realloc(this->list_ptr_, this->list_size_, this->list_max_size_);

			if (this->list_ptr_ == nullptr)
				return OVER_FLOW;
		}
		//移动
		for (int i = list_size_ - 1; i >= pos- 1; --i) {
			list_ptr_[i+1] = list_ptr_[i];
		}
		list_ptr_[pos-1] = elem;
		++list_size_;
		return OK;
	}

	//删除第i个元素，时间复杂度为O(n)
	Status SequenceList::DeleteWithPos(int pos, ElementType& elem) {
		//合法值在 1 <= i <= list_size_
		if (pos < 1 || pos > this->list_size_)
			return ERROR;
		//将被删除的值传给elem
		elem = list_ptr_[pos - 1];
		//移动
		for (int i = pos - 1; i < list_size_ - 1; ++i) {
			list_ptr_[i] = list_ptr_[i + 1];
		}

		--list_size_;
		return OK;
	}

	//根据值查找某个元素，返回第一次出现的位置，若没有，则返回-1.时间复杂度为O(n)
	int SequenceList::SearchWithValue(ElementType elem) {
		for (int i = 0; i < list_size_; ++i) {
			if (elem == list_ptr_[i])
				return i + 1;
		}
		return -1;
	}

	//非递减插入一个元素，返回插入的位置，若溢出，则返回-2.时间复杂度为O(n)
	int SequenceList::InsertWithOrder(ElementType elem) {
		//如果表满了，重新申请更大的内存
		if (this->list_size_ >= this->list_max_size_) {
			this->list_max_size_ += LIST_INC_SIZE;
			this->list_ptr_ = Realloc(this->list_ptr_, this->list_size_, this->list_max_size_);

			if (this->list_ptr_ == nullptr)
				return OVER_FLOW;
		}

		int i;
		//顺序遍历
		for (i = 0; i < this->list_size_; ++i) {
			//找到第一个比它大的元素，在其之前插入
			if (elem <= this->list_ptr_[i]) {
				for (int j = this->list_size_ - 1; j >= i; --j)
					this->list_ptr_[j + 1] = this->list_ptr_[j];
				break;
			}
		}

		this->list_ptr_[i] = elem;
		++list_size_;
		//返回插入的位置
		return i + 1;
	}

	//顺序查找，删除第一个元素e，返回其位置，若没有，则返回-1.时间复杂度为O(n)
	int SequenceList::DeleteFirstElemWithValue(ElementType elem, int begin) {
		//初始默认为未找到
		int pos = -1;
		//顺序遍历
		for (int i = begin; i < this->list_size_; ++i) {
			//找到第一个相等的元素，同时设置pos
			if (elem == this->list_ptr_[i]) {
				pos = i + 1;
				for (int j = i; j < this->list_size_ - 1; ++j)
					this->list_ptr_[j] = this->list_ptr_[j + 1];
				--list_size_;
				break;
			}
		}
		//返回位置
		return pos;
	}

	//顺序查找，删除所有为e的元素，若成功，则返回1，若没有，返回-1.时间复杂度O(n)
	Status SequenceList::DeleteAllElemWithValue(ElementType elem, int begin) {
		//思路：只遍历一次，遇到e就将prev指向e的位置，然后继续遍历，如果碰到下一个e或者是顺序表末尾，
		//那么就把从prev到当前段向前移动.重复该过程直到遍历完毕.遍历的时间复杂度为O(n)，而移动的复杂度最坏也为O(n)
		//所以总时间复杂度仍为O(n)
		int prev = begin, q = begin + 1, ok = 0;
		int size = this->list_size_;
		for (int cur = begin; cur < size; ++cur) {
			//如果找到
			if (elem == this->list_ptr_[cur]) {
				//判断前面是否找到了，如果是第一次遇到不必做移动
				if (ok) {
					//移动
					for (; q < cur && q < size; ++prev, ++q) {
						this->list_ptr_[prev] = this->list_ptr_[q];
					}
					//elem下一个位置才是有效的
					q = cur + 1;
				}
				else {
					//第一次未移动，所以不需要减一
					prev = cur;
					q = cur + 1;
					ok = 1;
				}

				--this->list_size_;
			}

		}
		//到了边界还需做一次
		for (;ok && q < size; ++prev, ++q) {
			this->list_ptr_[prev] = this->list_ptr_[q];
		}
		
		return OK;
	}

	//逆转顺序表，时间复杂度为O(n)
	const SequenceList& ReverseList(const SequenceList& s) {
		ElementType temp;
		//只需要到list_size_/2就行了
		for (int i = 0; i < s.list_size_ / 2; ++i) {
			//元素交换
			temp = s.list_ptr_[i];
			s.list_ptr_[i] = s.list_ptr_[s.list_size_ - i - 1];
			s.list_ptr_[s.list_size_ - i - 1] = temp;
		}
		return s;
	}

	//删除多余元素，时间复杂度O(n^2)
	Status SequenceList::Deduplicate() {
		//思路：每次都调用删除所有值为elem的元素的函数，从当前位置的下一位置作为起始点（这样保证不会删光）
		//因为每次调用删除函数都为O(n)，调用n次，故总复杂度为O(n^2)
		for (int i = 0; i < this->list_size_ - 1; ++i) {
			DeleteAllElemWithValue(this->list_ptr_[i], i+1);
		}
		return OK;
	}

	//合并两个有序表，时间复杂度为O(n1+n2)
	SequenceList MergeOrderedLists(const SequenceList& s1, const SequenceList& s2) {
		SequenceList newlist;
		//如果新的表长度不够，那么重新申请更大的内存
		if (newlist.list_max_size_ <= s1.list_size_ + s2.list_size_) {
			newlist.list_max_size_ = s1.list_size_ + s2.list_size_ + 1;
			newlist.list_ptr_ = Realloc(newlist.list_ptr_, newlist.list_size_, newlist.list_max_size_);
		}
		
		
		int i, j, k;
		//把两个有序的表，合并成一个有序的表
		for (i = 0, j = 0, k = 0; i < s1.list_size_ && j < s2.list_size_; ++k) {
			if (s1.list_ptr_[i] < s2.list_ptr_[j])
				newlist.list_ptr_[k] = s1.list_ptr_[i++];
			else
				newlist.list_ptr_[k] = s2.list_ptr_[j++];
			
		}

		while (i < s1.list_size_) {
			newlist.list_ptr_[k] = s1.list_ptr_[i];
			++i, ++k;
		}

		while (j < s2.list_size_) {
			newlist.list_ptr_[k] = s2.list_ptr_[j];
			++j, ++k;
		}
		newlist.list_size_ = k;
		//返回新的表，会调用复制构造函数，若有赋值操作，还会调用赋值重载函数
		return newlist;
	}

	//清空顺序表，时间复杂度O(1)
	Status SequenceList::ClearList() {
		list_size_ = 0;
		list_max_size_ = 0;
		return OK;
	}

	//析构函数
	SequenceList::~SequenceList() {
		delete[]this->list_ptr_;
		ClearList();
	}

	//显示顺序表的函数
	Status SequenceList::Display()const {
		if (this->list_size_ > 0) {
			std::cout << "顺序表为：" << std::endl;
			for (int i = 0; i < this->list_size_; ++i) {
				std::cout << this->list_ptr_[i] << " ";
				//每输出20个换行
				if ((i + 1) % 20 == 0)
					std::cout << std::endl;
			}
			return OK;
		}
		else {
			std::cout << "顺序表为空！\n";
			return ERROR;
		}
		
	}

}