#include <iostream>
#include <cstring>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

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




using datastructure::LinkedStack;
using datastructure::SequenceStack;
using datastructure::Status;
using datastructure::Node;

const char* OPTR = "+-*/()=";

//括弧匹配
void BracketsMatching() {
	SequenceStack s;
	string file;
	char c;
	while (getline(cin, file)) {

		int size = file.size();
		for (int i = 0; i < size; ++i) {
			if (file[i] == '{' || file[i] == '[' || file[i] == '(') {
				s.Push(file[i]);
			}
			else if (file[i] == '}' || file[i] == ']' || file[i] == ')') {
				if (s.Empty()) {
					cout << "no\n";
					cout << file[i] << "期待左括号\n";
					return;
				}
				s.Pop(c);
				if (c == '{') {
					if (file[i] == '}')
						continue;
					else {
						cout << "no\n";
						cout << "{期待右括号\n";
						return;
					}
				}
				else if (c == '[') {
					if (file[i] == ']')
						continue;
					else {
						cout << "no\n";
						cout << "[期待右括号\n";
						return;
					}
				}
				else if (c == '(') {
					if (file[i] == ')')
						continue;
					else {
						cout << "no\n";
						cout << "(期待右括号\n";
						return;
					}
				}

			}
		}
	}
	if (!s.Empty()) {
		cout << "no\n";
		cout << s.Top() << "期待右括号\n";
		return;
	}

	cout << "yes\n";
}


bool isHigh(char top, char op) {
	if ((top == '+') && (op == '+')) return true;
	if ((top == '+') && (op == '+')) return true;
	if ((top == '-') && (op == '+')) return true;
	if ((top == '-') && (op == '-')) return true;
	if ((top == '*') && (op == '+')) return true;
	if ((top == '*') && (op == '-')) return true;
	if ((top == '*') && (op == '*')) return true;
	if ((top == '*') && (op == '/')) return true;
	if ((top == '/') && (op == '+')) return true;
	if ((top == '/') && (op == '-')) return true;
	if ((top == '/') && (op == '*')) return true;
	if ((top == '/') && (op == '/')) return true;
	if (top == ')') return true;
	return false;
}

//中缀表达式求值(算符优先法)
void InfixEval() {
	char input;
	char x;
	int num;
	int arr[10];
	int cnt = 0;
	int pow = 1;
	int a, b, c;
	SequenceStack optr; //操作符
	LinkedStack opnd;  //操作数
	while (cin >> input) {
		if (input >= '0' && input <= '9') {
			arr[cnt++] = static_cast<int>(input - '0');
		}
		else {
			if (!strchr(OPTR,input)) {
				cout << "ERROR\n";
				return;
			}
			num = 0;
			pow = 1;
			for (int i = cnt-1; i >=0; --i) {
				num += arr[i] * pow;
				pow *= 10;
			}
			if (cnt) {
				cnt = 0;
				opnd.Push(static_cast<int>(num));
			}
			
			
			if (input == '=') {
				while (!optr.Empty()) {
					optr.Pop(x);
					if (x == '+') {
						if (!opnd.Pop(b)) {
							cout << "ERROR\n";
							return;
						}
						if (!opnd.Pop(a)) {
							cout << "ERROR\n";
							return;
						}
						opnd.Push(static_cast<int>(a + b));
					}
					else if (x == '-') {
						if (!opnd.Pop(b)) {
							cout << "ERROR\n";
							return;
						}
						if (!opnd.Pop(a)) {
							cout << "ERROR\n";
							return;
						}
						opnd.Push(static_cast<int>(a - b));
					}
					else if (x == '*') {
						if (!opnd.Pop(b)) {
							cout << "ERROR\n";
							return;
						}
						if (!opnd.Pop(a)) {
							cout << "ERROR\n";
							return;
						}
						opnd.Push(static_cast<int>(a * b));
					}
					else if (x == '/') {
						if (!opnd.Pop(b)) {
							cout << "ERROR\n";
							return;
						}
						if (!opnd.Pop(a)) {
							cout << "ERROR\n";
							return;
						}
						if (b != 0)
							opnd.Push(static_cast<int>(a / b));
						else {
							cout << "ERROR\n";
							return;
						}
					}
					else if (x == ')')
						continue;
				}
				cout << opnd.Top() << endl;
				return;
			}

			//操作符栈为空直接插入
			if (optr.Empty()) {
				optr.Push(input);
				continue;
			}
			
			//若栈顶的操作符优先级高于输入的，那么先弹出栈顶，进行运算，再将运算结果存放到操作数栈，再push这个操作符
			if (isHigh(optr.Top(), input)) {
				optr.Pop(x);
				optr.Push(input);
				if (x == '+') {
					if (!opnd.Pop(b)) {
						cout << "ERROR\n";
						return;
					}
					if (!opnd.Pop(a)) {
						cout << "ERROR\n";
						return;
					}
					opnd.Push(static_cast<int>(a + b));
				}
				else if (x == '-') {
					if (!opnd.Pop(b)) {
						cout << "ERROR\n";
						return;
					}
					if (!opnd.Pop(a)) {
						cout << "ERROR\n";
						return;
					}
					opnd.Push(static_cast<int>(a - b));
				}
				else if (x == '*') {
					if (!opnd.Pop(b)) {
						cout << "ERROR\n";
						return;
					}
					if (!opnd.Pop(a)) {
						cout << "ERROR\n";
						return;
					}
					opnd.Push(static_cast<int>(a * b));
				}
				else if (x == '/') {
					if (!opnd.Pop(b)) {
						cout << "ERROR\n";
						return;
					}
					if (!opnd.Pop(a)) {
						cout << "ERROR\n";
						return;
					}
					if (b != 0)
						opnd.Push(static_cast<int>(a / b));
					else {
						cout << "ERROR\n";
						return;
					}
				}
				else if (x == ')')
					continue;

			}
			else {
				//就必须算到‘（’
				if (input == ')') {
					while (optr.Top() != '(') {
						optr.Pop(x);
						
						if (x == '+') {
							if (!opnd.Pop(b)) {
								cout << "ERROR\n";
								return;
							}
							if (!opnd.Pop(a)) {
								cout << "ERROR\n";
								return;
							}
							opnd.Push(static_cast<int>(a + b));
						}
						else if (x == '-') {
							if (!opnd.Pop(b)) {
								cout << "ERROR\n";
								return;
							}
							if (!opnd.Pop(a)) {
								cout << "ERROR\n";
								return;
							}
							opnd.Push(static_cast<int>(a - b));
						}
						else if (x == '*') {
							if (!opnd.Pop(b)) {
								cout << "ERROR\n";
								return;
							}
							if (!opnd.Pop(a)) {
								cout << "ERROR\n";
								return;
							}
							opnd.Push(static_cast<int>(a * b));
						}
						else if (x == '/') {
							if (!opnd.Pop(b)) {
								cout << "ERROR\n";
								return;
							}
							if (!opnd.Pop(a)) {
								cout << "ERROR\n";
								return;
							}
							if (b != 0)
								opnd.Push(static_cast<int>(a / b));
							else {
								cout << "ERROR\n";
								return;
							}
						}
					}
					optr.Pop(x);
					continue;
				}
				optr.Push(input);
			}
		}
	}
}

//中缀表达式转后缀表达式
void Infix2Postfix() {
	char input;
	char x;
	int num;
	int arr[10];
	int cnt = 0;
	int pow = 1;
	int a, b, c;
	SequenceStack optr; //操作符
	LinkedStack opnd;  //操作数
	while (cin >> input) {
		if (input >= '0' && input <= '9') {
			arr[cnt++] = static_cast<int>(input - '0');
		}
		else {

			num = 0;
			pow = 1;
			for (int i = cnt-1; i >=0; --i) {
				num += arr[i] * pow;
				pow *= 10;
			}
			if (cnt) {
				cnt = 0;
				cout << static_cast<int>(num) << " ";
			}
			
			if(input == '=')
				break;
				
			if(optr.Empty()){
				optr.Push(input);
				continue;
			}
			if(input == ')'){
				while(!optr.Empty()){
					optr.Pop(x);
					if(x == '(')
						break;
					cout << x << " ";
				}	
				continue;
			}
			
			while(isHigh(optr.Top(), input) && !optr.Empty()){
				optr.Pop(x);
				cout << x << " ";		
			}
			optr.Push(input);
		}
		
	}
	
	while(!optr.Empty()){
		optr.Pop(x);
		cout << x << " ";
	}
}

//后缀表达式求值
void PostfixEval() {
	char input;
	char x;
	int num;
	int arr[10];
	int cnt = 0;
	int pow = 1;
	int a, b, c;
	SequenceStack optr; //操作符
	LinkedStack opnd;  //操作数
	
	while ((input = cin.get()) != '=') {
		if (input >= '0' && input <= '9') {
			arr[cnt++] = static_cast<int>(input - '0');
		}
		else {
			if (!(strchr(OPTR,input) || input == ' ')){
				cout << "ERROR\n";
				return;
			}
			num = 0;
			pow = 1;
			for (int i = cnt-1; i >=0; --i) {
				num += arr[i] * pow;
				pow *= 10;
			}
			if (cnt) {
				cnt = 0;
				opnd.Push(static_cast<int>(num));
			}
			
			if(input == ' ')
				continue;
						
			
			if(input == '+'){
				opnd.Pop(a);
				opnd.Pop(b);
				opnd.Push(b+a);
			} 
			else if(input == '-'){
				opnd.Pop(a);
				opnd.Pop(b);
				opnd.Push(b-a);
			}
			else if(input == '*'){
				opnd.Pop(a);
				opnd.Pop(b);
				opnd.Push(b*a);
			}
			else if(input == '/'){
				opnd.Pop(a);
				opnd.Pop(b);
				opnd.Push(b/a);
			}
			
		}
	}	
	if(input == '='){
		cout << opnd.Top() << endl;
		return;
	}
}

int main()
{

	PostfixEval();

	return 0;
}
