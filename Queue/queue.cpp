#include "queue.h"
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

	SequenceQueue::SequenceQueue() {
		this->base_ = new ElementType[QUEUE_INIT_SIZE];
		this->front_ = this->rear_ = 0;
		this->queue_size_ = QUEUE_INIT_SIZE;
	}

	int SequenceQueue::Size()const {
		return this->rear_ - this->front_;
	}

	bool SequenceQueue::Empty()const {
		return this->rear_ == this->front_;
	}

	Status SequenceQueue::Push(ElementType x) {
		if (Size() >= this->queue_size_) {
			this->base_ = Realloc(this->base_, this->queue_size_, this->queue_size_ + QUEUEINCREMENT);
			this->queue_size_ += QUEUEINCREMENT;
			if (this->base_ == nullptr)
				return OVER_FLOW;
		}
		this->base_[rear_++] = x;
		return OK;
	}

	Status SequenceQueue::Pop(ElementType& x) {
		if (Empty()) {
			return ERROR;
		}
		x = this->base_[front_++];
		return OK;
	}

	ElementType SequenceQueue::Front()const {
		return this->base_[front_];
	}

	ElementType SequenceQueue::Rear()const {
		return this->base_[rear_-1];
	}

	SequenceQueue::~SequenceQueue() {
		delete[] this->base_;
	}


	LinkedQueue::LinkedQueue() {
		this->front_ = this->rear_ = new Node[1];
		this->front_->next = nullptr;
	}

	bool LinkedQueue::Empty()const {
		return this->front_->next == nullptr;
	}

	int LinkedQueue::Size()const {
		int cnt = 0;
		Node* p = this->front_->next;
		while (p) {
			++cnt;
			p = p->next;
		}
		return cnt;
	}

	Status LinkedQueue::Push(ElementType x) {
		Node* temp;
		temp = new Node[1];
		temp->data = x;
		temp->next = this->rear_->next;
		this->rear_->next = temp;
		this->rear_ = temp;
		return OK;
	}


	Status LinkedQueue::Pop(ElementType& x) {
		if (Empty()) {
			return ERROR;
		}
		Node* temp;
		x = this->front_->next->data;
		temp = this->front_->next->next;
		delete[]this->front_->next;
		this->front_->next = temp;
		return OK;
	}

	ElementType LinkedQueue::Front()const {
		return this->front_->next->data;
	}

	ElementType LinkedQueue::Rear()const {
		return this->rear_->data;
	}

	LinkedQueue::~LinkedQueue() {
		Node* p = this->front_->next;
		while (p) {
			p = this->front_->next;
			delete[]this->front_;
			this->front_ = p;
		}
	}


}