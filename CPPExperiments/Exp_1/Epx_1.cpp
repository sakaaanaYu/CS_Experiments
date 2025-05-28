//experiment_1
#include <iostream>

struct Queue {
    int* const elems; //elems申请内存用于存放队列的元素
    const int max; //elems申请的最大元素个数max
    int head; //队列头head
    int tail; //队列尾tail
};

void queInit(Queue* const p, int m);
void queInit(Queue* const p, const Queue& q);
int queSize(const Queue* const p);
int queNumber(const Queue* const p);
Queue* const queEnter(Queue* const p, int& e);
Queue* const queLeave(Queue* const p, int& e);
Queue* const queAssign(Queue* const p, const Queue& q);
void quePrint(const Queue* const p, char* s);
void queClear(Queue* const p);
void queDestroy(Queue* const p);

void queInit(Queue* const p, int m) //初始化p指向的新队列，最多申请m个元素
{
    if (p == nullptr || p->elems != nullptr) {
        std::cerr << "Error: p是空指针，或其指向的队列已分配内存。\n";
        return;
    }

    new ((void*)&p->elems) int* (new int[m]);//申请m个元素的内存空间
    new ((void*)&p->max) int(m); //初始化max为m
	p->head = p->tail = 0; //初始化head和tail为0 
}

void queInit(Queue *const p, const Queue& q) //用队列q深拷贝构造p指向的新队列
{
    if (p == nullptr || p->elems != nullptr) {
        std::cerr << "Error: p是空指针，或其指向的队列已分配内存。\n";
        return;
    }

    new ((void*)&p->elems) int* (new int[q.max]); //分配相同内存
    new ((void*)&p->max) int(q.max); //设置相同max
    p->head = q.head; //复制队列头
    p->tail = q.tail; //复制队列尾
    for (int i = q.head; i < q.tail; i++) {
        (p->elems)[i % (q.max)] = (q.elems)[i % (q.max)]; //复制元素，实现循环队列
    }
}

int queSize(const Queue* const p) //返回队列申请的最大元素个数max
{
    if (p == nullptr) {
        std::cerr << "Error: p是空指针。\n";
        return -1;
    }
    return p->max;
}

int queNumber(const Queue* const p) //返回p指向的队列的实际元素个数
{
    if (p == nullptr) {
        std::cerr << "Error: p是空指针。\n";
        return -1;
    }
    if (p->elems == nullptr || p->max <= 0) {
        std::cerr << "Error: 队列未初始化或已销毁。\n";
        return -1;
    }
    return (p->tail - p->head + p->max) % p->max;
}

Queue* const queEnter(Queue* const p, int& e) //将e加入队列，并返回p
{
    if (p == nullptr || p->elems == nullptr) {
        std::cerr << "Error: p是空指针，或其指向的队列未分配内存。\n";
        return nullptr;
    }
    if (queNumber(p) >= p->max-1) {
        std::cerr << "Error: 队列已满。\n";
        return nullptr;
    }
    p->elems[p->tail] = e;
    p->tail = (p->tail + 1) % p->max;
    return p;
}

Queue* const queLeave(Queue* const p, int& e) //从队列移出元素到e，并返回p
{
    if (p == nullptr) {
        std::cerr << "Error: p是空指针，或其指向的队列未分配内存。\n";
        return nullptr;
    }
    if (queNumber(p) <= 0) {
        std::cerr << "Error: 队列为空。\n";
        return nullptr;
    }
    e = p->elems[p->head];
    p->head = (p->head + 1) % p->max;
    return p;
}

Queue* const queAssign(Queue* const p, const Queue& q) //用队列q赋值给p指向的队列并返回p
{
    if (p == nullptr) {
        std::cerr << "Error: p是空指针。\n";
        return nullptr;
    }
    delete[] p->elems;
    new ((void*)&p->elems) int* (new int[q.max]);
    new ((void*)&p->max) int(q.max);
    p->head = q.head;
    p->tail = q.tail;
    for (int i = q.head; i < q.tail; ++i) {
        p->elems[i % q.max] = q.elems[i % q.max];
    }
    return p;
}

void quePrint(const Queue* const p, char* s) //打印p指向的队列至s
{
    if (s == nullptr) {
        std::cerr << "Error: s是空指针。\n";
        return;
    }
    int pos = 0; //每一个下次写入的位置
    int n = queNumber(p);
    for (int i = 0; i < n; ++i) {
        pos += snprintf(s + pos, 100 - pos, "%d ", p->elems[(p->head + i) % p->max]);
    }
}

void queClear(Queue* const p) //清空并重置p指向的队列到初始化前的状态
{
    p->head = p->tail = 0;
}

void queDestroy(Queue* const p) //销毁p指向的队列，释放内存
{
    if (p == nullptr || p->elems == nullptr) return;
    delete[] p->elems;
    new ((void*)&p->elems) int* (nullptr);
    new ((void*)&p->max) int(0);
    p->head = p->tail = 0;
}

int main()
{
    
    int a[5] = {10, 20, 30, 40, 50};
    Queue* p = (Queue*)malloc(sizeof(Queue));
    new ((void*)&p->elems) int* (nullptr);
    new ((void*)&p->max) int(0);
    p->head = p->tail = 0;

    // 1. 初始化队列p
    queInit(p, 6);
	std::cout << "初始化p: " << "p->head: " << p->head << ", p->tail: " << p->tail << ", p->max:" << p->max << ", size: " << sizeof(p->elems) << std::endl;
    queDestroy(p);

	//2. 用q深拷贝p
    Queue q = {a, 5, 0, 4};
    queInit(p, q);
    std::cout << "用q深拷贝p: " << "p->head: " << p->head << ", p->tail: " << p->tail << ", p->max:" << p->max << ", size: " << sizeof(p->elems) << std::endl;

	//3. 返回队列申请的最大元素个数max
	std::cout << "p最大元素个数: " << queSize(p) << std::endl;

	//4. 返回p指向的队列的实际元素个数
	std::cout << "p实际元素个数: " << queNumber(p) << std::endl;

    // 5. 将e加入队列，并返回p
	int e = 60;
	queEnter(p, e);
	std::cout << "加入e（60）: " << e << ", p->head: " << p->head << ", p->tail: " << p->tail << ", p->max:" << p->max << ", size: " << sizeof(p->elems) << std::endl;
    
	//6. 从队列移出元素到e，并返回p
	queLeave(p, e);
    std::cout << "移出e: " << e << ", p->head: " << p->head << ", p->tail: " << p->tail << ", p->max:" << p->max << ", size: " << sizeof(p->elems) << std::endl;

	// 7. 用队列q赋值给p指向的队列并返回p
	queAssign(p, q);
    std::cout << "用p赋值给q: " << "p->head: " << p->head << ", p->tail: " << p->tail << ", p->max:" << p->max << ", size: " << sizeof(p->elems) << std::endl;

	// 8. 打印p内容到s
	char s[100] = { 0 }; 
	quePrint(p, s);
	std::cout << "打印p内容到s: " << s << std::endl;

	// 9. 清空队列
	queClear(p);
    char s1[100] = { 0 };
    quePrint(p, s1);
    std::cout << "清空p，打印p内容（看是否为空）: " << s1 << std::endl;

    // 10. 销毁队列
    queDestroy(p);
    char s2[100] = { 0 };
    std::cout << "销毁p。 " << std::endl;

	free(p);
    return 0;
}