//这是链表ADT的头文件
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

namespace datastructure {
	//返回状态
	enum Status {
		OVER_FLOW = -2,
		INFEASIBLE = -1,
		ERROR = 0,
		OK = 1
	};

	enum NodeType {
		SINGLE,
		DOUBLE
	};
	
	typedef int ElementType;

	//单链表节点
	struct SNode {
		ElementType element;
		SNode* next;
	};

	//双链表节点
	struct DNode {
		ElementType element;
		DNode* prev, *next;
	};

	//头节点
	union Head
	{
		SNode *shead;
		DNode *dhead;
	};

	//抽象ADT：基本链表，一些基本操作
	class BasicLinkedList {
	public:
		//构造
		BasicLinkedList(NodeType nodetype);

		//插入
		virtual Status InsertWithPos(int i, int elem) = 0;
		//删除
		virtual Status  DeleteWithPos(int i, ElementType& elem) = 0;
		//查找
		virtual int SearchWithValue(ElementType elem) = 0;
		//显示
		virtual void Display()const = 0;
		//析构
		virtual ~BasicLinkedList();
		//判断是否是循环链表
		friend bool IsCircularList(const BasicLinkedList& b);
		//判断两个链表是否相交
		friend bool IsIntersecting(const BasicLinkedList& b1, const BasicLinkedList& b2);

	protected:
		Head *L;  //头节点
	private:
		const NodeType node_type_;   //节点类型
	};

	//单链表
	//基本操作：建立、插入、删除、查找、销毁；其他操作：去重、判定是否相交
	class SinglyLinkedList : public BasicLinkedList {
	public:
		//构造函数，需要输入n个值来创建
		explicit SinglyLinkedList(int n = 0);

		//在第i个位置前插入
		virtual Status InsertWithPos(int i, ElementType elem);

		//删除第i个位置的元素
		virtual Status DeleteWithPos(int i, ElementType& elem);

		//根据值查找某个元素，返回第一次出现的位置，若没有，则返回-1
		virtual int SearchWithValue(ElementType elem);

		//显示
		virtual void Display()const;

		//析构函数，单链表的销毁
		virtual ~SinglyLinkedList();

		//逆置单链表
		void ReverseList();

		//删除多余元素
		void Deduplicate();

	};

	//单向循环链表
	class SinglyCircularLinkedList : public BasicLinkedList  {
	public:
		//构造函数，需要输入n个值来创建
		explicit SinglyCircularLinkedList(int n = 0);

		//在第i个位置前插入
		virtual Status InsertWithPos(int i, ElementType elem);

		//删除第i个位置的元素
		virtual Status DeleteWithPos(int i, ElementType& elem);

		//根据值查找某个元素，返回第一次出现的位置，若没有，则返回-1
		virtual int SearchWithValue(ElementType elem);

		//显示
		virtual void Display()const;

		//析构函数，单向链表的销毁
		virtual ~SinglyCircularLinkedList();

	};

	//双向循环链表
	class DoublyCircularLinkedList : public BasicLinkedList {
	public:
		//构造函数，需要输入n个值来创建
		explicit DoublyCircularLinkedList(int n = 0);

		//在第i个位置前插入
		virtual Status InsertWithPos(int i, ElementType elem);

		//删除第i个位置的元素
		virtual Status DeleteWithPos(int i, ElementType& elem);

		//根据值查找某个元素，返回第一次出现的位置，若没有，则返回-1
		virtual int SearchWithValue(ElementType elem);

		//显示
		virtual void Display()const;

		//析构函数，单链表的销毁
		virtual ~DoublyCircularLinkedList();
	};
}

#endif // !LINKED_LIST_H_

