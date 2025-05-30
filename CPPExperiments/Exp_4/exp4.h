#define _CRT_SECURE_NO_WARNINGS
#include <list>
#include<iostream>
using namespace std;

class QUEUE {
	int* const	elems;	 	//elems申请内存用于存放队列的元素
	const int  	max;	 	//elems申请的最大元素个数max
	int     	head;		//队列头head
	int			tail;			//队列尾tail
public:
	QUEUE(int m);
	QUEUE(const QUEUE& q);
	QUEUE(QUEUE&& q) noexcept;
	virtual int size() const noexcept;
	virtual operator int() const noexcept;  			//返回队列的实际元素个数
	virtual QUEUE& operator<<(int e);  			//加入单个元素e至队列
	virtual QUEUE& operator<<(std::list<int>& s); //批量加入元素至队列
	virtual QUEUE& operator>>(int& e); 			//移出单个元素到e
	virtual QUEUE& operator>>(std::list<int>& s);	//批量移出元素到集合s
	virtual QUEUE& operator=(const QUEUE& q);
	virtual QUEUE& operator=(QUEUE&& q) noexcept;
	virtual void print(char* s) const;
	virtual void clear()noexcept;
	virtual ~QUEUE()noexcept;
};

class STACK : public QUEUE {
	QUEUE  q;
public:
	STACK(int m);
	STACK(const STACK& s);
	STACK(STACK&& s) noexcept;
	int size()const noexcept;
	operator int() const noexcept;	   				//返回栈的实际元素个数
	STACK& operator<<(int e); 	     			//将e入栈，并返回当前栈
	STACK& operator<<(std::list<int>& s); 		//将元素批量入栈
	STACK& operator>>(int& e);     			//出栈到e，并返回当前栈
	STACK& operator>>(std::list<int>& s);		//批量出栈
	STACK& operator=(const STACK& s);
	STACK& operator=(STACK&& s) noexcept;
	void print(char* s)const;
	void clear()noexcept;
	~STACK()noexcept;
}; 
