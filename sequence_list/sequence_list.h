//这是顺序表ADT的头文件
#ifndef SEQUENCE_LIST_H_
#define SEQUENCE_LIST_H_

namespace datastructure {
	enum Status {
		OVER_FLOW = -2,
		INFEASIBLE = -1,
		ERROR = 0,
		OK = 1
	};

	typedef int ElementType;

	class SequenceList {
	public:
		//默认构造函数，顺序表的初始化
		SequenceList();
		
		//复制构造函数（深拷贝）
		SequenceList(const SequenceList& s);

		//赋值运算符重载（深拷贝）
		SequenceList & operator=(const SequenceList& s);

		//构造函数，给定最大个数n
		explicit SequenceList(int n);

		//在第i个元素前插入
		Status InsertWithPos(ElementType elem, int pos);

		//删除第i个元素
		Status DeleteWithPos(int pos, ElementType &elem);

		//根据值查找某个元素，返回第一次出现的位置，若没有，则返回-1
		int SearchWithValue(ElementType elem);

		//非递减插入一个元素，返回插入的位置，若溢出，则返回-2
		int InsertWithOrder(ElementType elem);

		//顺序查找，删除第一个元素e，返回其位置，若没有，则返回-1
		int DeleteFirstElemWithValue(ElementType elem, int begin = 0);

		//顺序查找，删除所有为e的元素，若成功，则返回1，若没有，返回-1
		Status DeleteAllElemWithValue(ElementType elem, int begin = 0);

		//逆转顺序表
		friend const SequenceList& ReverseList(const SequenceList& s);

		//合并两个有序表
		friend SequenceList MergeOrderedLists(const SequenceList& s1, const SequenceList& s2);

		//清空顺序表
		Status ClearList();

		//删除多余元素
		Status Deduplicate();

		//析构函数，顺序表的销毁
		~SequenceList();

		//显示
		Status Display()const;
		
	private:
		enum {
			LIST_INIT_SIZE_ = 100,
			LIST_INC_SIZE = 10
		};
		ElementType * list_ptr_;  //顺序表数组指针
		int list_size_;           //顺序表当前大小
		int list_max_size_;       //顺序表最大容量
	};

}


#endif // !SEQUENCE_LIST_H_
