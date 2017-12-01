#include "stack.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
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

//判断运算符优先级的
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
			
			//结束时，退栈到全空
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

}

//后缀表达式求值
void PostfixEval() {

}

int main()
{

	InfixEval();

	system("pause");
	return 0;
}