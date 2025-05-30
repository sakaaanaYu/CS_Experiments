#define _CRT_SECURE_NO_WARNINGS
#include <list>
#include<iostream>
using namespace std;

class QUEUE {
	int* const	elems;	 	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
	const int  	max;	 	//elems��������Ԫ�ظ���max
	int     	head;		//����ͷhead
	int			tail;			//����βtail
public:
	QUEUE(int m);
	QUEUE(const QUEUE& q);
	QUEUE(QUEUE&& q) noexcept;
	virtual int size() const noexcept;
	virtual operator int() const noexcept;  			//���ض��е�ʵ��Ԫ�ظ���
	virtual QUEUE& operator<<(int e);  			//���뵥��Ԫ��e������
	virtual QUEUE& operator<<(std::list<int>& s); //��������Ԫ��������
	virtual QUEUE& operator>>(int& e); 			//�Ƴ�����Ԫ�ص�e
	virtual QUEUE& operator>>(std::list<int>& s);	//�����Ƴ�Ԫ�ص�����s
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
	operator int() const noexcept;	   				//����ջ��ʵ��Ԫ�ظ���
	STACK& operator<<(int e); 	     			//��e��ջ�������ص�ǰջ
	STACK& operator<<(std::list<int>& s); 		//��Ԫ��������ջ
	STACK& operator>>(int& e);     			//��ջ��e�������ص�ǰջ
	STACK& operator>>(std::list<int>& s);		//������ջ
	STACK& operator=(const STACK& s);
	STACK& operator=(STACK&& s) noexcept;
	void print(char* s)const;
	void clear()noexcept;
	~STACK()noexcept;
}; 
