#include "polynomial.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

namespace datastructure {
	const double EPS = 1e-6;

	static unsigned long long QuickPower(int x, int n) {
		if (n == 0)
			return 1;
		else if (n == 1)
			return x;
		else if (n & 1) //奇数
			return QuickPower(x*x, n / 2)*x;
		else //偶数
			return QuickPower(x*x, n / 2);
	}

	Status Polynomial::Insert(Node* n) {
		Node *p = this->head_;
		//按照expn升序
		while (p->next && p->next->term.expn < n->term.expn)
			p = p->next;
		n->next = p->next;	
		p->next = n;
		return OK;
	}

	//按照expn升序插入
	Polynomial::Polynomial(int n) {
		double coef;
		int expn;
		this->head_ = new Node[1];
		this->head_->next = nullptr;
		Node *temp;
		for (int i = 0; i < n; ++i) {
			cin >> coef >> expn;
			temp = new Node[1];
			temp->term.coef = coef;
			temp->term.expn = expn;
			Insert(temp);
		}
	}

	Polynomial::Polynomial(const Polynomial& p) {
		this->head_ = new Node[1];
		this->head_->next = nullptr;
		Node* p1 = this->head_, *s;
		Node* p2 = p.head_->next;
		while (p2) {
			s = new Node[1];
			s->term = p2->term;
			s->next = nullptr;
			p1->next = s;
			p1 = s;
			p2 = p2->next;
		}
	}

	Polynomial& Polynomial::operator=(const Polynomial& p) {
		if (this == &p)
			return *this;
		if(this->head_ != nullptr)
			Clear(*this);
		this->head_ = new Node[1];
		this->head_->next = nullptr;
		Node* p1 = this->head_, *s;
		Node* p2 = p.head_->next;
		while (p2) {
			s = new Node[1];
			s->term = p2->term;
			s->next = nullptr;
			p1->next = s;
			p1 = s;
			p2 = p2->next;
		}
		return *this;
	}

	//相加
	Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
		Polynomial p;
		Node *pa, *pb, *pc, *temp;
		pa = p1.head_->next;
		pb = p2.head_->next;
		p.head_ = new Node[1];
		p.head_->next = nullptr;
		pc = p.head_;

		while (pa && pb) {
			if (pa->term.expn < pb->term.expn) {
				temp = new Node[1];
				temp->term = pa->term;
				temp->next = nullptr;
				pc->next = temp;
				pc = temp;
				pa = pa->next;
			}
			else if (pa->term.expn > pb->term.expn) {
				temp = new Node[1];
				temp->term = pb->term;
				temp->next = nullptr;
				pc->next = temp;
				pc = temp;
				pb = pb->next;
			}
			else {
				if (abs(pa->term.coef + pb->term.coef) > EPS) {
					temp = new Node[1];
					temp->term.coef = pa->term.coef + pb->term.coef;
					temp->term.expn = pa->term.expn;
					temp->next = nullptr;
					pc->next = temp;
					pc = temp;
				}
				pa = pa->next;
				pb = pb->next;
			}
		}

		while (pa) {
			temp = new Node[1];
			temp->term = pa->term;
			temp->next = nullptr;
			pc->next = temp;
			pc = temp;
			pa = pa->next;
		}

		while (pb) {
			temp = new Node[1];
			temp->term = pb->term;
			temp->next = nullptr;
			pc->next = temp;
			pc = temp;
			pb = pb->next;
		}

		return p;
	}

	//相减
	Polynomial operator-(const Polynomial& p1, const Polynomial& p2) {
		Polynomial p;
		Node *pa, *pb, *pc, *temp;
		pa = p1.head_->next;
		pb = p2.head_->next;
		p.head_ = new Node[1];
		p.head_->next = nullptr;
		pc = p.head_;

		while (pa && pb) {
			if (pa->term.expn < pb->term.expn) {
				temp = new Node[1];
				temp->term = pa->term;
				temp->next = nullptr;
				pc->next = temp;
				pc = temp;
				pa = pa->next;
			}
			else if (pa->term.expn > pb->term.expn) {
				temp = new Node[1];
				temp->term.coef = - pb->term.coef;
				temp->term.expn = pb->term.expn;
				temp->next = nullptr;
				pc->next = temp;
				pc = temp;
				pb = pb->next;
			}
			else {
				if (abs(pa->term.coef - pb->term.coef) > EPS) {
					temp = new Node[1];
					temp->term.coef = pa->term.coef - pb->term.coef;
					temp->term.expn = pa->term.expn;
					temp->next = nullptr;
					pc->next = temp;
					pc = temp;
				}
				pa = pa->next;
				pb = pb->next;
			}
		}

		while (pa) {
			temp = new Node[1];
			temp->term = pa->term;
			temp->next = nullptr;
			pc->next = temp;
			pc = temp;
			pa = pa->next;
		}

		while (pb) {
			temp = new Node[1];
			temp->term.coef = -pb->term.coef;
			temp->term.expn = pb->term.expn;
			temp->next = nullptr;
			pc->next = temp;
			pc = temp;
			pb = pb->next;
		}

		return p;
	}
	
	//相乘 
	Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
		Polynomial p;
		Node *pa, *pb, *pc, *s;
		pa = p1.head_->next;
		pb = p2.head_->next;
		p.head_ = new Node[1];
		p.head_->next = nullptr;
		pc = p.head_;

		while (pa) {
			while (pb) {
				s = new Node[1];
				s->term.coef = pa->term.coef * pb->term.coef;
				s->term.expn = pa->term.expn + pb->term.expn;
				s->next = nullptr;

				pc = p.head_;
				while (pc->next && pc->next->term.expn < s->term.expn) 
					pc = pc->next;

				if (!pc->next) {
					pc->next = s;
				}
				else if (pc->next->term.expn == s->term.expn) {
					if (abs(pc->next->term.coef + s->term.coef) > EPS) {
						pc->next->term.coef += s->term.coef;
						delete[]s;
					}
					else {
						delete[]s;
						s = pc->next->next;
						delete[]pc->next;
						pc->next = s;
					}
				}

				pb = pb->next;
			}
			pa = pa->next;
			pb = p2.head_->next;
		}

		return p;
	}


	//由于不是双向链表，无法用秦九韶算法，只能用快速幂优化
	double Polynomial::Eval(double x)const {
		double sum = 0, pow;
		Node *p = this->head_->next;

		while (p) {
			pow = QuickPower(x, p->term.expn);
			sum += p->term.coef*pow;
			p = p->next;
		}
		return sum;
	} 

	void Polynomial::Display()const {
		Node* p = this->head_->next;
		if (p && p->term.coef < 0)
			cout << "-";
		while (p) {
			cout << abs(p->term.coef) << "x^" << p->term.expn;
			if (p->next)
				if (p->next->term.coef > 0)
					cout << " + ";
				else
					cout << " - ";
			p = p->next;
		}
		cout << endl;
	}

	void Polynomial::Clear(Polynomial& p) {
		Node *temp = p.head_->next;
		while (temp) {
			temp = p.head_->next;
			delete[] p.head_;
			p.head_ = temp;
		}
	}

	Polynomial::~Polynomial() {
		Clear(*this);
	}
}