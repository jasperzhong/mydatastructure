#include "stack.h"
#include <cstring>

namespace datastructure {

	//C++版realloc
	template<typename T>
	T* Realloc(T* oldptr, int oldsize, int newsize) {
		//重新申请内存
		T* newptr = new T[newsize];
		//内存移动
		memmove(newptr, oldptr, oldsize * sizeof(T));
		//释放原内存
		delete[]oldptr;
		return newptr;
	}

	//默认构造
	SequenceStack::SequenceStack() {
		this->base_ = new ElementType[STACK_INIT_SIZE];
		this->top_ = this->base_;
		this->stack_size_ = STACK_INIT_SIZE;
	}

	//共有多少个元素
	int SequenceStack::Size()const {
		return this->top_ - this->base_;
	}

	//是否为空
	bool SequenceStack::Empty()const {
		return this->top_ == this->base_;
	}

	//入栈
	Status SequenceStack::Push(ElementType x) {
		if (Size() >= this->stack_size_) {
			this->base_ = Realloc(this->base_, this->stack_size_, this->stack_size_ + STACKINCREMENT);
			this->top_ = this->base_ + this->stack_size_;
			this->stack_size_ += STACKINCREMENT;
			if (this->base_ == nullptr)
				return OVER_FLOW;
		}
		*this->top_ = x;
		++this->top_;
		return OK;
	}

	//出栈
	Status SequenceStack::Pop(ElementType& x) {
		if (Empty()) {
			return ERROR;
		}
		x = *(this->top_-1);
		--this->top_;
		return OK;
	}

	//取栈顶元素
	ElementType SequenceStack::Top()const {
		return *(this->top_ - 1);	
	}

	SequenceStack::~SequenceStack() {
		delete[]this->base_;
	}

	//<------------------------------------->
	
	//默认构造
	LinkedStack::LinkedStack() {
		this->top_ = new Node2[1];
		this->top_->next = nullptr;
	}

	//是否为空
	bool LinkedStack::Empty()const {
		return this->top_->next == nullptr;
	}

	//共有多少个元素
	int LinkedStack::Size()const {
		int cnt = 0;
		Node2* p = this->top_->next;
		while (p) {
			++cnt;
			p = p->next;
		}
		return cnt;
	}

	//入栈
	Status LinkedStack::Push(ElementType2 x) {
		Node2* temp;
		temp = new Node2[1];
		temp->data = x;
		temp->next = this->top_->next;
		this->top_->next = temp;
		return OK;
	}

	//出栈
	Status LinkedStack::Pop(ElementType2& x) {
		if (Empty()) {
			return ERROR;
		}
		Node2* temp = this->top_->next->next;
		x = this->top_->next->data;
		delete[]this->top_->next;
		this->top_->next = temp;
		return OK;
	}

	//取栈顶元素
	ElementType2 LinkedStack::Top()const {
		return this->top_->next->data;
	}

	LinkedStack::~LinkedStack() {
		Node2* p = this->top_->next;
		while (p) {
			p = this->top_->next;
			delete[]this->top_;
			this->top_= p;
		}
	}
}