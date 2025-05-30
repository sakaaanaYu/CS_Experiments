#include "exp4.h"

STACK::STACK(int m) : QUEUE(m), q(m) {}

STACK::STACK(const STACK& s) : QUEUE(s), q(s.q) {} 

STACK::STACK(STACK&& s) noexcept : QUEUE((QUEUE&&)s), q((QUEUE&&)s.q) {}

int STACK::size()const noexcept {
	return q.size() * 2;
}

STACK::operator int() const noexcept {
	return q.operator int() + QUEUE::operator int();
}

STACK& STACK::operator<<(int e) {
    if (QUEUE::operator int() < QUEUE::size() - 1) {
        QUEUE::operator<<(e);
        return *this;
    }
    if (q.operator int() < q.size() - 1) {
        q << e;
        return *this;
    }
    cerr << "Error：队列已满\n";
}

STACK& STACK::operator<<(std::list<int>& s) {
    for (auto& e : s) {
        if (QUEUE::operator int() < QUEUE::size() - 1) {
            QUEUE::operator<<(e);
        } else if (q.operator int() < q.size() - 1) {
            q << e;
        } else {
            cerr << "Error：队列已满\n";
            return *this;
        }
    }
    return *this;
}

STACK& STACK::operator>>(int& e) {
    if (q.operator int() > 0) {
        q >> e;
        return *this;
    } else if (QUEUE::operator int() > 0) {
        QUEUE::operator>>(e);
        return *this;
    }
    cerr << "Error：队列已空\n";
    return *this;
}

STACK& STACK::operator>>(std::list<int>& s) {
    while (q.operator int() > 0) {
        int e;
        q >> e;
        s.push_back(e);
    }
    while (QUEUE::operator int() > 0) {
        int e;
        QUEUE::operator>>(e);
        s.push_back(e);
    }
    return *this;
}

STACK& STACK::operator=(const STACK& s) { 
    if (this != &s) {
        QUEUE::operator=(s);
        q = s.q;
    }
    return *this;
}

STACK& STACK::operator=(STACK&& s) noexcept {
    if (this != &s) {
        QUEUE::operator=(move(s)); q = move(s.q);
    }
    return *this;
}

void STACK::print(char* s)const { 
    QUEUE::print(s);
}

void STACK::clear()noexcept{ 
    QUEUE::clear();
    q.clear();
}

STACK::~STACK() = default;