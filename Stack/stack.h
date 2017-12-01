#ifndef STACK_H_
#define STACK_H_

namespace datastructure {
	//返回状态
	enum Status {
		OVER_FLOW = -2,
		INFEASIBLE = -1,
		ERROR = 0,
		OK = 1
	};

	typedef char ElementType;

	struct Node {
		ElementType data;
		Node* next;
	};


	//顺序栈
	class SequenceStack {
	public:
		SequenceStack();  //只提供默认构造
		Status Push(ElementType x);  //入栈
		Status Pop(ElementType& x);  //出栈
		ElementType Top()const;  //取栈顶元素
		bool Empty()const;  //是否为空
		int Size()const;  //共有多少个元素
		~SequenceStack();
	private:
		enum {
			STACK_INIT_SIZE = 100,
			STACKINCREMENT = 10,
		};
		ElementType* top_;
		ElementType* base_;
		int stack_size_;  //最大容量
	};

	typedef int ElementType2;
	struct Node2 {
		ElementType2 data;
		Node2* next;
	};
	//链栈
	class LinkedStack {
	public:
		LinkedStack();  //只提供默认构造
		Status Push(ElementType2 x);  //入栈
		Status Pop(ElementType2& x);  //出栈
		ElementType2 Top()const;  //取栈顶元素
		bool Empty()const;  //是否为空
		int Size()const;  //共有多少个元素
		~LinkedStack();
	private:
		Node2* top_; //栈顶，亦为表头
	};
}
#endif // !STACK_H_
