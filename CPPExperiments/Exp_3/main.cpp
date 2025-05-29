#include "exp3.h"

int main() {
	//1. 初始化栈（m=5），入队4个元素，返回栈最大容量、栈实际元素个数，打印栈中元素
	STACK stack(5);
	stack.enter(10);
	stack.enter(20, 30, 40); 
    char s[100] = { 0 };
    stack.print(s);
	cout << "stack栈最大容量" << stack.size() << "，栈实际元素个数" << stack.number() << "栈中元素:" << s << "\n\n";

    //2. 出栈一个元素
    int e;
    stack.leave(e);
    stack.print(s);
    cout << "出栈元素: " << e << "，出栈后栈内容：" << s << "\n\n";

    //3. 批量出栈
    int buf[5], n = 2;
    stack.leave(n, buf);
	stack.print(s);
    cout << "批量出栈2个元素，出栈后栈内容：" << s << "\n\n";

    //4. 用栈stack2深拷贝stack
    STACK stack2(stack);
    stack2.print(s);
    cout << "用栈stack2深拷贝stack，stack2为：" << s << "\n\n";

	//5. 用栈stack3移动拷贝stack
    STACK stack3(move(stack));
    stack3.print(s);
    cout << "用栈stack3移动拷贝stack，stack3为：" << s << "\n\n";

    //6. 清空栈
    stack.clear();
    stack.print(s);
    cout << "清空栈stack：" << s << "\n";

    //7. 销毁栈
    stack.~stack();
}
