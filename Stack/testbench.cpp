#include <iostream>
#include <cstring>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace datastructure {
	//����״̬
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


	//˳��ջ
	class SequenceStack {
	public:
		SequenceStack();  //ֻ�ṩĬ�Ϲ���
		Status Push(ElementType x);  //��ջ
		Status Pop(ElementType& x);  //��ջ
		ElementType Top()const;  //ȡջ��Ԫ��
		bool Empty()const;  //�Ƿ�Ϊ��
		int Size()const;  //���ж��ٸ�Ԫ��
		~SequenceStack();
	private:
		enum {
			STACK_INIT_SIZE = 100,
			STACKINCREMENT = 10,
		};
		ElementType* top_;
		ElementType* base_;
		int stack_size_;  //�������
	};

	typedef int ElementType2;
	struct Node2 {
		ElementType2 data;
		Node2* next;
	};
	//��ջ
	class LinkedStack {
	public:
		LinkedStack();  //ֻ�ṩĬ�Ϲ���
		Status Push(ElementType2 x);  //��ջ
		Status Pop(ElementType2& x);  //��ջ
		ElementType2 Top()const;  //ȡջ��Ԫ��
		bool Empty()const;  //�Ƿ�Ϊ��
		int Size()const;  //���ж��ٸ�Ԫ��
		~LinkedStack();
	private:
		Node2* top_; //ջ������Ϊ��ͷ
	};
}


namespace datastructure {

	//C++��realloc
	template<typename T>
	T* Realloc(T* oldptr, int oldsize, int newsize) {
		//���������ڴ�
		T* newptr = new T[newsize];
		//�ڴ��ƶ�
		memmove(newptr, oldptr, oldsize * sizeof(T));
		//�ͷ�ԭ�ڴ�
		delete[]oldptr;
		return newptr;
	}

	//Ĭ�Ϲ���
	SequenceStack::SequenceStack() {
		this->base_ = new ElementType[STACK_INIT_SIZE];
		this->top_ = this->base_;
		this->stack_size_ = STACK_INIT_SIZE;
	}

	//���ж��ٸ�Ԫ��
	int SequenceStack::Size()const {
		return this->top_ - this->base_;
	}

	//�Ƿ�Ϊ��
	bool SequenceStack::Empty()const {
		return this->top_ == this->base_;
	}

	//��ջ
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

	//��ջ
	Status SequenceStack::Pop(ElementType& x) {
		if (Empty()) {
			return ERROR;
		}
		x = *(this->top_-1);
		--this->top_;
		return OK;
	}

	//ȡջ��Ԫ��
	ElementType SequenceStack::Top()const {
		return *(this->top_ - 1);	
	}

	SequenceStack::~SequenceStack() {
		delete[]this->base_;
	}

	//<------------------------------------->
	
	//Ĭ�Ϲ���
	LinkedStack::LinkedStack() {
		this->top_ = new Node2[1];
		this->top_->next = nullptr;
	}

	//�Ƿ�Ϊ��
	bool LinkedStack::Empty()const {
		return this->top_->next == nullptr;
	}

	//���ж��ٸ�Ԫ��
	int LinkedStack::Size()const {
		int cnt = 0;
		Node2* p = this->top_->next;
		while (p) {
			++cnt;
			p = p->next;
		}
		return cnt;
	}

	//��ջ
	Status LinkedStack::Push(ElementType2 x) {
		Node2* temp;
		temp = new Node2[1];
		temp->data = x;
		temp->next = this->top_->next;
		this->top_->next = temp;
		return OK;
	}

	//��ջ
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

	//ȡջ��Ԫ��
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

//����ƥ��
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
					cout << file[i] << "�ڴ�������\n";
					return;
				}
				s.Pop(c);
				if (c == '{') {
					if (file[i] == '}')
						continue;
					else {
						cout << "no\n";
						cout << "{�ڴ�������\n";
						return;
					}
				}
				else if (c == '[') {
					if (file[i] == ']')
						continue;
					else {
						cout << "no\n";
						cout << "[�ڴ�������\n";
						return;
					}
				}
				else if (c == '(') {
					if (file[i] == ')')
						continue;
					else {
						cout << "no\n";
						cout << "(�ڴ�������\n";
						return;
					}
				}

			}
		}
	}
	if (!s.Empty()) {
		cout << "no\n";
		cout << s.Top() << "�ڴ�������\n";
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

//��׺���ʽ��ֵ(������ȷ�)
void InfixEval() {
	char input;
	char x;
	int num;
	int arr[10];
	int cnt = 0;
	int pow = 1;
	int a, b, c;
	SequenceStack optr; //������
	LinkedStack opnd;  //������
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

			//������ջΪ��ֱ�Ӳ���
			if (optr.Empty()) {
				optr.Push(input);
				continue;
			}
			
			//��ջ���Ĳ��������ȼ���������ģ���ô�ȵ���ջ�����������㣬�ٽ���������ŵ�������ջ����push���������
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
				//�ͱ����㵽������
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

//��׺���ʽת��׺���ʽ
void Infix2Postfix() {
	char input;
	char x;
	int num;
	int arr[10];
	int cnt = 0;
	int pow = 1;
	int a, b, c;
	SequenceStack optr; //������
	LinkedStack opnd;  //������
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

//��׺���ʽ��ֵ
void PostfixEval() {
	char input;
	char x;
	int num;
	int arr[10];
	int cnt = 0;
	int pow = 1;
	int a, b, c;
	SequenceStack optr; //������
	LinkedStack opnd;  //������
	
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
