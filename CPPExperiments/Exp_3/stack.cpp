#include "exp3.h"


STACK::STACK(int m) : QUEUE(m), q(m) {} //��ʼ��ջ�������2m-2��Ԫ��

STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {} //��ջs�����ʼ��ջ

STACK::STACK(STACK&& s) noexcept : QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {} //��ջs�ƶ�������ʼ��ջ

int STACK::size() const { //����ջ��max����,��2m  
    return QUEUE::size() * 2;  
}

int STACK::number() const { //����ջ��ʵ��Ԫ�ظ���
	return QUEUE::number() + q.number();
}

STACK& STACK::enter(int e) { //��e��ջ�������ص�ǰջ
    if (number() >= size() - 1) { cerr << "Stack full\n"; return *this; }
    while (QUEUE::number()) {
        int tmp; QUEUE::leave(tmp); q.enter(tmp);
    }
    QUEUE::enter(e);
    while (q.number()) {
        int tmp; q.leave(tmp); QUEUE::enter(tmp);
    }
    return *this;
}

//STACK& STACK::enter(short n, ...) { //������ջ
//    va_list args; va_start(args, n);
//    for (short i = 0; i < n; ++i) enter(va_arg(args, int));
//    va_end(args);
//    return *this;
//}

STACK& STACK::leave(int& e) { //��ջ��e�������ص�ǰջ
    if (QUEUE::number() == 0) { cerr << "Stack empty\n"; return *this; }
    QUEUE::leave(e);
    return *this;
}

STACK& STACK::leave(int& n, int* buf) { //������ջ
    if (n <= 0) {
        std::cerr << "Error: n����Ϊ��\n";
        n = 0;
        return *this;
    }
    if (buf == nullptr) {
        std::cerr << "Error: buf����Ϊ��\n";
        n = 0;
        return *this;
    }

    int actualSize = 0;
    for (; actualSize < n; ++actualSize) {
        if (QUEUE::number() == 0) break; // ջ��
        QUEUE::leave(buf[actualSize]);
    }
    n = actualSize; 
    return *this;
}

STACK& STACK::operator=(const STACK & s) { //�����ֵ�����ر���ֵջ
    if (this != &s) {
        QUEUE::operator=(s); 
        q = s.q;
    }
    return *this;
}

STACK& STACK::operator=(STACK&& s) noexcept { //�ƶ���ֵ�����ر���ֵջ
    if (this != &s) {
        QUEUE::operator=(move(s)); q = move(s.q);
    }
    return *this;
}

void STACK::print(char* s)const { //��ջ�׵�ջ����ӡջԪ�� 
    QUEUE::print(s);
}

void STACK::clear() { //���ջ
    QUEUE::clear(); 
    q.clear();
}

STACK::~STACK() = default; //����ջ
