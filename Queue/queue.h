#ifndef QUEUE_H_
#define QUEUE_H_

namespace datastructure {

	//返回状态
	enum Status {
		OVER_FLOW = -2,
		INFEASIBLE = -1,
		ERROR = 0,
		OK = 1
	};

	typedef int ElementType;

	struct Node {
		ElementType data;
		Node* next;
	};

	class SequenceQueue {
	public:
		SequenceQueue();    //默认构造函数
		Status Push(ElementType x); //入队
		Status Pop(ElementType& x);	 //出队
		ElementType Front()const;	 //取队头
		ElementType Rear()const;	//取队尾
		bool Empty()const;			//是否为空
		int Size()const;			//大小
		~SequenceQueue();			//析构函数
	private:
		enum {
			QUEUE_INIT_SIZE = 100,
			QUEUEINCREMENT = 10,
		};
		ElementType* base_;
		int front_;
		int rear_;
		int queue_size_;
	};


	class LinkedQueue {
	public:
		LinkedQueue();
		Status Push(ElementType x); //入队
		Status Pop(ElementType& x);	 //出队
		ElementType Front()const;	 //取队头
		ElementType Rear()const;	//取队尾
		bool Empty()const;			//是	否为空
		int Size()const;			//取大小
		~LinkedQueue();				//析构函数
	private:
		Node* front_;
		Node* rear_;
	};
}

#endif 

