#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

namespace datastructure {

	//返回状态
	enum Status {
		OVER_FLOW = -2,
		INFEASIBLE = -1,
		ERROR = 0,
		OK = 1
	};

	struct ElemType {
		double coef;
		int expn;
	};

	struct Node {
		ElemType term;
		Node* next;
	};

	//一元多项式，单链表实现
	class Polynomial {
	public:	

		Polynomial() {};

		//创建
		explicit Polynomial(int n);

		Polynomial(const Polynomial& p);

		Polynomial& operator=(const Polynomial& p);

		Status Insert(Node* n);

		//只需返回链表的头指针即可

		//相加
		friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);

		//相减
		friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2);

		//相乘
		friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);


		//求值
		double Eval(double x)const; 
		
		void Display()const;
		//清空
		void Clear(Polynomial& p);

		//析构
		~Polynomial();
	private:
		Node* head_;  //链表
	};
}

#endif // !POLYNOMIAL_H_

