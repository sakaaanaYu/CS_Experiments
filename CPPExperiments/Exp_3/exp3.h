#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include<cstdarg>
#include<string.h>

using namespace std;

class QUEUE {
	int* const elems; //elems申请内存用于存放队列的元素
	const int max; //elems申请的最大元素个数max
	int head; //队列头head
	int tail; //队列尾tail
public:
	QUEUE(int m);
	QUEUE(const QUEUE& q);
	QUEUE(QUEUE&& q) noexcept;
	virtual int size() const;
	virtual int number() const;
	virtual QUEUE& enter(int e);
	virtual QUEUE& enter(short n, ...);
	virtual QUEUE& leave(int& e);
	virtual QUEUE& leave(int& n, int* buf);
	virtual QUEUE& operator=(const QUEUE& q);
	virtual QUEUE& operator=(QUEUE&& q) noexcept;
	virtual QUEUE& queCat(const QUEUE& q);
	virtual void print(char* s) const;
	virtual void clear();
	virtual ~QUEUE();
};

class STACK : public QUEUE {
	QUEUE q;
public:
	STACK(int m); //初始化栈：最多存放2m-2个元素
	STACK(const STACK& s); //用栈s深拷贝初始化栈
	STACK(STACK&& s) noexcept; //用栈s移动拷贝初始化栈
	int size()const; //返回栈的容量即2m
	int number() const; //返回栈的实际元素个数
	STACK& enter(int e); //将e入栈，并返回当前栈
	STACK& enter(short n, ...); //批量入栈
	STACK& leave(int& e); //出栈到e，并返回当前栈
	STACK& leave(int& n, int* buf); //批量出栈
	STACK& operator=(const STACK& s); //深拷贝赋值并返回被赋值栈
	STACK& operator=(STACK&& s) noexcept; //移动赋值并返回被赋值栈
	void print(char* s)const; //从栈底到栈顶打印栈元素 
	void clear(); //清空栈
	~STACK(); //销毁栈
};