#include "exp3.h"

QUEUE::QUEUE(int m) : elems(new int[m]), max(m) {
	head = tail = 0;
}

QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), max(q.max) {
	head = q.head;
	tail = q.tail;
	for (int i = 0; i < max; i++)
		*(elems + i) = q.elems[i];
}

QUEUE::QUEUE(QUEUE&& q)noexcept : elems(q.elems), max(q.max), head(q.head), tail(q.tail) {
	*(int**)&q.elems = 0;
	*(int*)&q.max = 0;
	q.head = q.tail = 0;
}

int QUEUE::size() const {
	return max;
}

int QUEUE::number() const {
	if (max <= 0) return 0;
	return (tail - head + max) % max;
}

QUEUE& QUEUE::enter(int e) {
	if ((tail + 1) % max == head) {
		std::cerr << "Error: 队列已满\n";
		return *this;
	}
	else {
		elems[tail] = e;
		tail = (tail + 1) % max;
	}
	return *this;
}

QUEUE& QUEUE::enter(short n, ...) {
	if (n < 0) {
		std::cerr << "Error: n不可非负\n";
		return *this;
	}

	int freeSpace = (head - tail - 1 + max) % max;

	if (n > freeSpace) {
		std::cerr << "Error: 队列已满\n";
		return *this;
	}

	va_list args;
	va_start(args, n);
	for (short i = 0; i < n; ++i) {
		int e = va_arg(args, int);
		elems[tail] = e;
		tail = (tail + 1) % max;
	}
	va_end(args);
	return *this;
}

QUEUE& QUEUE::leave(int& e) {
	if (head == tail) {
		e = 0;
		std::cerr << "队列为空\n";
		return *this;
	}
	else {
		e = elems[head];
		head = (head + 1) % max;
	}
	return *this;
}

QUEUE& QUEUE::leave(int& n, int* buf) {
	if (n < 0) {
		std::cerr << "Error: n不可非负\n";
		return *this;
	}
	if (buf == nullptr) {
		std::cerr << "Error: buf不能为空\n";
		return *this;
	}

	int actualSize;

	if (elems == nullptr) {
		actualSize = 0;
	}
	else {
		actualSize = number() < n ? number() : n;
		for (int i = 0; i < actualSize; i++) {
			if (head == tail) break;  // 队列为空
			buf[i] = elems[head];
			head = (head + 1) % max;
		}
		n = actualSize;
		return *this;
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

QUEUE& QUEUE::queCat(const QUEUE& q) {
	int p_num = this->number();
	int q_num = q.number();
	int free_space = (this->head - this->tail - 1 + this->max) % this->max;
	int new_max = p_num + q_num + 2;

	if (q_num > free_space) {
		int* new_elems = new int[new_max];

		for (int i = 0; i < p_num; ++i) {
			new_elems[i] = this->elems[(this->head + i) % this->max];
		}

		delete[] this->elems;

		*(int**)&this->elems = new_elems;
		*(int*)&this->max = new_max;

		this->head = 0;
		this->tail = p_num;
	}

	for (int i = 0; i < q_num; i++) {
		this->elems[this->tail] = q.elems[(q.head + i) % q.max];
		this->tail = (this->tail + 1) % this->max;
	}

	return *this;
}

void QUEUE::print(char* s) const {
	if (s == nullptr) {
		std::cerr << "Error: s不能为空\n";
		return;
	}
	int n = number();
	if (n == 0) {
		strcpy(s, "队列为空");
		return;
	}
	s[0] = '\0';
	for (int i = 0; i < n; ++i) {
		sprintf(s + strlen(s), "%d ", elems[(head + i) % max]);
	}
}

void QUEUE::clear() {
	head = tail = 0;
}

QUEUE::~QUEUE() {
	if (elems && !(head == max && tail == max)) {
		delete[] elems;
	}
}