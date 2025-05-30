#include "exp4.h"

QUEUE::QUEUE(int m) : elems(new int[m]), max(m) {
	head = tail = 0;
}

QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), max(q.max) { 
    head = q.head;
    tail = q.tail;
    for (int i = 0; i < max; i++)
        *(elems + i) = q.elems[i];
}

QUEUE::QUEUE(QUEUE&& q) noexcept : elems(q.elems), max(q.max), head(q.head), tail(q.tail) {
    *(int**)&q.elems = 0;
    *(int*)&q.max = 0;
    q.head = 0;
    q.tail = 0;
}

int QUEUE::size() const noexcept{
    return max;
}

QUEUE::operator int() const noexcept {
	return (tail - head + max) % max;
}

QUEUE& QUEUE::operator<<(int e) {
	if (head == (tail + 1) % max) {
		cerr << "Error: 队列已满\n";
		return *this;
	}
	elems[tail] = e;
	tail = (tail + 1) % max;
	return *this;
}

QUEUE& QUEUE::operator<<(std::list<int>& s) {
	if (s.empty())
		return *this;
	for (auto it = s.begin(); it != s.end(); ++it) {
		if (head == (tail + 1) % max) {
			cerr << "Error: 队列已满\n";
			break;
		}
		elems[tail] = *it;
		tail = (tail + 1) % max;
	}
	return *this;
}

QUEUE& QUEUE::operator>>(int& e) {
	if (head == tail) {
		cerr << "Error: 队列为空\n";
		return *this;
	}
	e = elems[head];
	head = (head + 1) % max;
	return *this;
}

QUEUE& QUEUE::operator>>(std::list<int>& s) {
	if (head == tail) {
		cerr << "Error: 队列为空\n";
		return *this;
	}
	while (head != tail) {
		s.push_back(elems[head]);
		head = (head + 1) % max;
	}
	return *this;
}


QUEUE& QUEUE::operator=(const QUEUE& q) {
	if (this == &q)
		return *this;
	if (elems)
		delete[] elems;

	*(int*)&(this->max) = q.max;
	*(int**)&(this->elems) = new int[q.max];
	int* elems = q.elems;
	head = q.head;
	tail = q.tail;
	memcpy(this->elems, q.elems, q.max * sizeof(int));
	return *this;
}

QUEUE& QUEUE::operator=(QUEUE&& q) noexcept {
	if (this == &q)
		return *this;
	if (elems)
		delete[] elems;
	head = q.head;
	tail = q.tail;
	*(int*)&max = q.max;
	*(int**)&elems = q.elems;
	*(int**)&q.elems = 0;
	*(int*)&q.max = 0;
	q.head = q.tail = 0;
	return *this;
}

void QUEUE::print(char* s) const {
	if (head == tail) {
		cout << s << "队列为空\n";
		return;
	}
	int i = head;
	while (i != tail) {
		cout << elems[i] << " ";
		i = (i + 1) % max;
	}
}

void QUEUE::clear()noexcept {
	head = tail = 0;
}

QUEUE::~QUEUE() {
	if (elems && !(head == max && tail == max)) {
		delete[] elems;
	}
}
