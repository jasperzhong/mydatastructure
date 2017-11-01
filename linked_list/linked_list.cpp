//这是链表ADT实现文件
#include "linked_list.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

namespace datastructure {
	//  <--------基础链表-------->
	BasicLinkedList::BasicLinkedList(NodeType nodetype)
		:node_type_(nodetype)
	{
		this->L = new Head[1];
	}

	BasicLinkedList::~BasicLinkedList() {
		delete[]this->L;
	}

	//判断是否是循环链表
	bool IsCircularList(const BasicLinkedList& b) {
		//如果是单链表
		if (b.node_type_ == SINGLE) {
			SNode * p = b.L->shead->next;
			while (p != nullptr) {
				if (p == b.L->shead)
					return true;
				p = p->next;
			}
			return false;
		}
		//如果是双链表
		else {
			DNode * p = b.L->dhead->next;
			while (p != nullptr) {
				if (p == b.L->dhead)
					return true;
				p = p->next;
			}
			return false;
		}
	}

	//判断两个链表是否相交
	bool IsIntersecting(const BasicLinkedList& b1, const BasicLinkedList& b2) {

		if (b1.node_type_ == SINGLE && b2.node_type_ == SINGLE) {
			SNode *p1 = b1.L->shead->next, *p2 = b2.L->shead->next;
			while (p1 != nullptr) {
				if (p1 == b1.L->shead)
					break;
				p2 = b2.L->shead->next;
				while (p2 != nullptr ) {
					if (p2 == b2.L->shead)
						break;
					if (p2->element == p1->element)
						return true;
					p2 = p2->next;
				}
				p1 = p1->next;
			}
			return false;
		}
		else if (b1.node_type_ == DOUBLE && b2.node_type_ == SINGLE) {
			DNode *p1 = b1.L->dhead->next;
			SNode *p2 = b2.L->shead->next;
			while (p1 != nullptr) {
				if (p1 == b1.L->dhead)
					break;
				p2 = b2.L->shead->next;
				while (p2 != nullptr) {
					if (p2 == b2.L->shead)
						break;
					if (p2->element == p1->element)
						return true;
					p2 = p2->next;
				}
				p1 = p1->next;
			}
			return false;
		}
		else if (b1.node_type_ == SINGLE && b2.node_type_ == DOUBLE) {
			SNode *p1 = b1.L->shead->next;
			DNode *p2 = b2.L->dhead->next;
			while (p1 != nullptr) {
				if (p1 == b1.L->shead)
					break;
				p2 = b2.L->dhead->next;
				while (p2 != nullptr) {
					if (p2 == b2.L->dhead)
						break;
					if (p2->element == p1->element)
						return true;
					p2 = p2->next;
				}
				p1 = p1->next;
			}
			return false;
		}
		else {
			DNode *p1 = b1.L->dhead->next;
			DNode *p2 = b2.L->dhead->next;
			while (p1 != nullptr) {
				if (p1 == b1.L->dhead)
					break;
				p2 = b2.L->dhead->next;
				while (p2 != nullptr) {
					if (p2 == b2.L->dhead)
						break;
					if (p2->element == p1->element)
						return true;
					p2 = p2->next;
				}
				p1 = p1->next;
			}
			return false;
		}
	}

	//	<--------单链表-------->
	//默认构造函数,创建元素个数为n的链表
	SinglyLinkedList::SinglyLinkedList(int n)
		:BasicLinkedList(SINGLE)		
	{
		this->L->shead = new SNode[1];
		this->L->shead->next = nullptr;

		int elem;
		SNode* temp;
		//头插法
		for (int i = 0; i < n; ++i) {
			cin >> elem;
			temp = new SNode[1];
			temp->element = elem;
			temp->next = this->L->shead->next;
			this->L->shead->next = temp;
		}
	}
	
	//在第i个元素前插入，时间复杂度为O(n)
	Status SinglyLinkedList::InsertWithPos(int i, ElementType elem) {
		SNode* pnode = this->L->shead;
		int pos = 1;
		while (pnode != nullptr && pos < i) {
			pnode = pnode->next;
			++pos;
		}
		if (pnode == nullptr || pos > i)
			return ERROR;

		SNode* temp;
		temp = new SNode[1];
		temp->element = elem;
		temp->next = pnode->next;
		pnode->next = temp;
		return OK;
	}

	//删除第i个位置的元素
	Status SinglyLinkedList::DeleteWithPos(int i, ElementType& elem) {
		SNode* pnode = this->L->shead;
		int pos = 1;
		while (pnode->next != nullptr && pos < i) {
			pnode = pnode->next;
			++pos;
		}

		if (pnode->next == nullptr || pos > i)
			return ERROR;

		SNode* temp;
		temp = pnode->next->next;
		delete[]pnode->next;
		pnode->next = temp;
		return OK;
	}

	//根据值查找某个元素，返回第一次出现的位置，若没有，则返回-1
	int SinglyLinkedList::SearchWithValue(ElementType elem){
		SNode* pnode = this->L->shead->next;
		int pos = 1, ok = 0;
		while (pnode != nullptr) {
			if (pnode->element == elem) {
				ok = 1;
				break;
			}
			pnode = pnode->next;
			++pos;
		}
		if (ok)
			return pos;
		return -1;
	}

	//显示链表
	void SinglyLinkedList::Display()const {
		if (this->L->shead == nullptr) {
			cout << "链表为空!" << endl;
			return;
		}
		SNode* pnode = this->L->shead->next;
		while (pnode != nullptr) {
			cout << pnode->element << " ";
			pnode = pnode->next;
		}
		cout << endl;
	}

	//析构
	SinglyLinkedList::~SinglyLinkedList() {
		SNode * pnode = this->L->shead;
		while (pnode != nullptr) {
			pnode = pnode->next;
			delete[] this->L->shead;
			this->L->shead = pnode;
		}
	}

	//逆置单链表，时间复杂度O(n)
	void SinglyLinkedList::ReverseList() {
		SNode* p, *q, *r;
		p = this->L->shead->next;
		q = p->next;
		p->next = nullptr;
		while (q != nullptr) {
			r = q->next;
			q->next = p;
			p = q;
			q = r;
		}
		this->L->shead->next = p;
		
	}

	//删除多余元素
	void SinglyLinkedList::Deduplicate() {
		SNode *p1 = this->L->shead, *p2, *temp;
		ElementType x;
		while (p1 != nullptr) {
			x = p1->element;
			p2 = p1;
			while (p2->next != nullptr) {
				if (p2->next->element == x) {
					temp = p2->next->next;
					delete[]p2->next;
					p2->next = temp;
				}
				else
					p2 = p2->next;
			}
			p1 = p1->next;
		}
	}


	//	<--------单向循环链表-------->
	
	//构造函数，需要输入n个值来创建
	SinglyCircularLinkedList::SinglyCircularLinkedList(int n) 
		:BasicLinkedList(SINGLE)
	{
		this->L->shead = new SNode[1];
		this->L->shead->next = this->L->shead;

		int elem;
		SNode* temp;
		//头插法
		for (int i = 0; i < n; ++i) {
			cin >> elem;
			temp = new SNode[1];
			temp->element = elem;
			temp->next = this->L->shead->next;
			this->L->shead->next = temp;
		}
	}

	//在第i个位置前插入
	Status SinglyCircularLinkedList::InsertWithPos(int i, ElementType elem) {
		if (i <= 0)
			return ERROR;
		SNode* pnode = this->L->shead;
		int pos = 1;
		while (pnode->next != this->L->shead && pos < i) {
			pnode = pnode->next;
			++pos;
		}
		if (pnode->next == this->L->shead && pos < i)
			return ERROR;

		SNode* temp;
		temp = new SNode[1];
		temp->element = elem;
		temp->next = pnode->next;
		pnode->next = temp;
		return OK;
	}

	//删除第i个位置的元素
	Status SinglyCircularLinkedList::DeleteWithPos(int i, ElementType& elem) {
		SNode* pnode = this->L->shead;
		int pos = 1;
		while (pnode->next != this->L->shead && pos < i) {
			pnode = pnode->next;
			++pos;
		}

		if (pnode->next == this->L->shead || pos > i)
			return ERROR;

		elem = pnode->next->element;
		SNode* temp;
		temp = pnode->next->next;
		delete[]pnode->next;
		pnode->next = temp;
		return OK;
	}

	//根据值查找某个元素，返回第一次出现的位置，若没有，则返回-1
	int SinglyCircularLinkedList::SearchWithValue(ElementType elem) {
		SNode* pnode = this->L->shead->next;
		int pos = 1, ok = 0;
		while (pnode != this->L->shead) {
			if (pnode->element == elem) {
				ok = 1;
				break;
			}
			pnode = pnode->next;
			++pos;
		}
		if (ok)
			return pos;
		return -1;
	}

	//显示
	void SinglyCircularLinkedList::Display()const {
		if (this->L->shead == nullptr) {
			cout << "链表为空!" << endl;
			return;
		}
		SNode* pnode = this->L->shead->next;
		while (pnode != this->L->shead) {
			cout << pnode->element << " ";
			pnode = pnode->next;
		}
		cout << endl;
	}

	//析构函数，单向循环链表的销毁
	SinglyCircularLinkedList::~SinglyCircularLinkedList() {
		SNode * pnode = this->L->shead->next;
		while (pnode != this->L->shead) {
			pnode = pnode->next;
			delete[] this->L->shead;
			this->L->shead = pnode;
		}
		delete[]this->L->shead;
	}


	//	<--------双向循环链表-------->
	//构造函数，需要输入n个值来创建
	DoublyCircularLinkedList::DoublyCircularLinkedList(int n)
		:BasicLinkedList(DOUBLE)
	{
		this->L->dhead = new DNode[1];
		this->L->dhead->prev = this->L->dhead;
		this->L->dhead->next = this->L->dhead;

		int elem;
		DNode* temp;
		//头插法
		for (int i = 0; i < n; ++i) {
			cin >> elem;
			temp = new DNode[1];
			temp->element = elem;
			temp->next = this->L->dhead->next;
			temp->next->prev = temp;
			this->L->dhead->next = temp;
			temp->prev = this->L->dhead;
		}
	}

	//在第i个位置前插入
	Status DoublyCircularLinkedList::InsertWithPos(int i, ElementType elem) {
		if (i <= 0)
			return ERROR;
		DNode* pnode = this->L->dhead;
		int pos = 1;
		while (pnode->next != this->L->dhead && pos < i) {
			pnode = pnode->next;
			++pos;
		}
		if (pnode->next == this->L->dhead && pos < i)
			return ERROR;

		DNode* temp;
		temp = new DNode[1];
		temp->element = elem;
		temp->prev = pnode;
		temp->next = pnode->next;
		pnode->next->prev = temp;
		pnode->next = temp;
		return OK;
	}

	//删除第i个位置的元素
	Status DoublyCircularLinkedList::DeleteWithPos(int i, ElementType& elem) {
		DNode* pnode = this->L->dhead;
		int pos = 1;
		while (pnode->next != this->L->dhead && pos < i) {
			pnode = pnode->next;
			++pos;
		}

		if (pnode->next == this->L->dhead || pos > i)
			return ERROR;

		elem = pnode->next->element;
		DNode* temp;
		temp = pnode->next->next;
		temp->prev = pnode;
		delete[]pnode->next;
		pnode->next = temp;
		return OK;
	}

	//根据值查找某个元素，返回第一次出现的位置，若没有，则返回-1
	int DoublyCircularLinkedList::SearchWithValue(ElementType elem) {
		SNode* pnode = this->L->shead->next;
		int pos = 1, ok = 0;
		while (pnode != this->L->shead) {
			if (pnode->element == elem) {
				ok = 1;
				break;
			}
			pnode = pnode->next;
			++pos;
		}
		if (ok)
			return pos;
		return -1;
	}

	//显示
	void DoublyCircularLinkedList::Display()const {
		if (this->L->dhead == nullptr) {
			cout << "链表为空!" << endl;
			return;
		}
		SNode* pnode = this->L->shead->next;
		while (pnode != this->L->shead) {
			cout << pnode->element << " ";
			pnode = pnode->next;
		}
		cout << endl;
	}

	//析构函数，双向循环链表的销毁
	DoublyCircularLinkedList::~DoublyCircularLinkedList() {
		SNode * pnode = this->L->shead->next;
		while (pnode != this->L->shead) {
			pnode = pnode->next;
			delete[] this->L->shead;
			this->L->shead = pnode;
		}
		delete[]this->L->shead;
	}

}