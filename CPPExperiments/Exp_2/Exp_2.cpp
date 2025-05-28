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
	QUEUE(int m); //初始化队列，最多申请m个元素
	QUEUE(const QUEUE& q); //用q深拷贝初始化队列
	QUEUE(QUEUE&& q) noexcept; //用q移动初始化队列

	int queSize() const; //返回队列申请的最大元素个数max
	int queNumber() const; //返回队列的实际元素个数
	QUEUE& queEnter(int e); //将e加入队列尾部，并返回当前队列
	QUEUE& queEnter(short n, ...); //批量加入元素到队列并返回当前队列
	QUEUE& queLeave(int& e); //从队首移出元素到e，并返回当前队列
	QUEUE& queLeave(int& n, int* buf); //批量移出n个元素到buf，并返回p
	QUEUE& operator=(const QUEUE& q); //深拷贝赋值并返回被赋值队列
	QUEUE& operator=(QUEUE&& q) noexcept; //移动赋值并返回被赋值队列
	QUEUE& queCat(const QUEUE& q); //将q拼接到p队列末尾并返回p
	void quePrint(char* s) const; //打印队列至s并返回s
	void queClear(); //清空并重置p指向的队列
	~QUEUE(); //销毁当前队列
};


int main() {
	//1. 初始化队列，入队4个元素，返回队列最大元素个数、实际元素个数，打印队列内容
	QUEUE p(5);

	p.queEnter(4, 10, 20, 30, 40); //容量足
	std::cout << "容量足：初始化队列p，入队10, 20, 30, 40。队列最大元素个数: " << p.queSize() << "队列实际元素个数:" << p.queNumber() << std::endl;
	char s[100] = { 0 };
	p.quePrint(s);
	std::cout << "打印队列p：" << s << "\n" << std::endl;

	std::cout << "容量不足测试：" << std::endl;
	p.queEnter(6, 10, 20, 30, 40, 50, 60); //容量不足
	std::cout << "\n" << std::endl;


	//2. 出队一个元素
	int e;
	p.queLeave(e);
	p.quePrint(s);
	std::cout << "出队元素: " << e << "，出队后队列p内容：" << s << "\n" << std::endl;

	//3. 批量出队
	int buf[5], n = 2;
	p.queLeave(n, buf);
	p.quePrint(s);
	std::cout << "批量出队2个元素，出对后队列p内容：" << s << "\n" << std::endl;

	//4. 用q深拷贝p
	QUEUE q(p);
	q.quePrint(s);
	std::cout << "打印深拷贝后的q：" << s << "\n" << std::endl;

	//5. 拼接队列q到p末尾
	p.queCat(q);
	p.quePrint(s);
	std::cout << "拼接队列q到p末尾：" << s << "\n" << std::endl;

	//6. 用r移动初始化p
	QUEUE r(std::move(p));
	r.quePrint(s);
	std::cout << "打印移动初始化后的r：" << s << "\n" << std::endl;

	//7. 清空队列p
	p.queClear();
	p.quePrint(s);
	std::cout << "清空队列p：" << s << "\n" << std::endl;

	//8. 销毁队列p
	p.~QUEUE();
}


QUEUE::QUEUE(int m) : elems(new int[m]), max(m), head(0), tail(0) {
	if (m <= 0) {
		std::cerr << "Error: 队列大小必须大于0\n";
		exit(EXIT_FAILURE);
	}
}

QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), max(q.max), head(q.head), tail(q.tail) {
	int num = q.queNumber();
	if (num > q.max) {
		std::cerr << "Error: 拷贝构造时元素数量超出容量\n";
		num = q.max - 1;
	}
	for (int i = 0; i < num; ++i) {
		elems[(head + i) % max] = q.elems[(q.head + i) % q.max];
	}
}

QUEUE::QUEUE(QUEUE&& q) noexcept : elems(q.elems), max(q.max), head(q.head), tail(q.tail) {
	/**(int**)(q.elems) = nullptr;
	*(int*)(q.max) = 0;*/
	q.head = q.tail = q.max;
}

int QUEUE::queSize() const {
	return max;
}

int QUEUE::queNumber() const {
	return (tail - head + max) % max; //适用于循环队列
}

QUEUE& QUEUE::queEnter(int e) {
	if ((tail + 1) % max == head) {
		std::cerr << "Error: 队列已满\n";
		return *this;
	}
	elems[tail] = e;
	tail = (tail + 1) % max;
	return *this;
}

QUEUE& QUEUE::queEnter(short n, ...) {
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

QUEUE& QUEUE::queLeave(int& e) {
	if (head == tail) {
		std::cerr << "队列为空\n";
		return *this;
	}
	e = elems[head];
	head = (head + 1) % max;
	return *this;
}

QUEUE& QUEUE::queLeave(int& n, int* buf) {
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
		actualSize = queNumber() < n ? queNumber() : n;
		for (int i = 0; i < actualSize; i++) {
			if (elems[head])
				queLeave(buf[i]);
		}
		n = actualSize;
		return *this;
	}

	return *this;
}

QUEUE& QUEUE::operator=(const QUEUE& q) {
	if (this != &q) {
		if (max != q.max) {
			std::cerr << "Error: 无法赋值不同容量的队列\n";
			return *this;
		}
		head = q.head;
		tail = q.tail;
		for (int i = 0; i < q.queNumber(); ++i) {
			elems[(head + i) % max] = q.elems[(q.head + i) % q.max];
		}
	}
	return *this;
}

QUEUE& QUEUE::operator=(QUEUE&& q) noexcept {
	*(int**)&elems = q.elems;
	*(int*)&max = q.max;
	head = q.head;
	tail = q.tail;

	*(int**)&q.elems = nullptr;
	*(int*)&q.max = 0;
	q.head = q.tail = 0;

	return *this;
}

QUEUE& QUEUE::queCat(const QUEUE& q) {
	int p_num = this->queNumber();
	int q_num = q.queNumber();
	int free_space = (this->head - this->tail - 1 + this->max) % this->max;
	int new_max = p_num + q_num + 1;
	
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

void QUEUE::quePrint(char* s) const {
	if (s == nullptr) {
		std::cerr << "Error: s不能为空\n";
		return;
	}
	int n = queNumber();
	if (n == 0) {
		strcpy(s, "队列为空");
		return;
	}
	s[0] = '\0';
	for (int i = 0; i < n; ++i) {
		sprintf(s + strlen(s), "%d ", elems[(head + i) % max]);
	}
}

void QUEUE::queClear() {
	head = tail = 0;
}

QUEUE::~QUEUE() {
	if (elems && !(head == max && tail == max)) {
		delete[] elems;
	}
}
