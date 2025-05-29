#include "exp3.h"


STACK::STACK(int m) : QUEUE(m), q(m) {} //初始化栈：最多存放2m-2个元素

STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {} //用栈s深拷贝初始化栈

STACK::STACK(STACK&& s) noexcept : QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {} //用栈s移动拷贝初始化栈

int STACK::size() const { //返回栈的max容量,即2m  
    return QUEUE::size() * 2;  
}

int STACK::number() const { //返回栈的实际元素个数
	return QUEUE::number() + q.number();
}

STACK& STACK::enter(int e) { //将e入栈，并返回当前栈
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

//STACK& STACK::enter(short n, ...) { //批量入栈
//    va_list args; va_start(args, n);
//    for (short i = 0; i < n; ++i) enter(va_arg(args, int));
//    va_end(args);
//    return *this;
//}

STACK& STACK::leave(int& e) { //出栈到e，并返回当前栈
    if (QUEUE::number() == 0) { cerr << "Stack empty\n"; return *this; }
    QUEUE::leave(e);
    return *this;
}

STACK& STACK::leave(int& n, int* buf) { //批量出栈
    if (n <= 0) {
        std::cerr << "Error: n必须为正\n";
        n = 0;
        return *this;
    }
    if (buf == nullptr) {
        std::cerr << "Error: buf不能为空\n";
        n = 0;
        return *this;
    }

    int actualSize = 0;
    for (; actualSize < n; ++actualSize) {
        if (QUEUE::number() == 0) break; // 栈空
        QUEUE::leave(buf[actualSize]);
    }
    n = actualSize; 
    return *this;
}

STACK& STACK::operator=(const STACK & s) { //深拷贝赋值并返回被赋值栈
    if (this != &s) {
        QUEUE::operator=(s); 
        q = s.q;
    }
    return *this;
}

STACK& STACK::operator=(STACK&& s) noexcept { //移动赋值并返回被赋值栈
    if (this != &s) {
        QUEUE::operator=(move(s)); q = move(s.q);
    }
    return *this;
}

void STACK::print(char* s)const { //从栈底到栈顶打印栈元素 
    QUEUE::print(s);
}

void STACK::clear() { //清空栈
    QUEUE::clear(); 
    q.clear();
}

STACK::~STACK() = default; //销毁栈
