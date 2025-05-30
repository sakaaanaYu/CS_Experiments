#include "exp4.h"
#include <iostream>

int main() {
    //1. 初始化栈（m=5），入队4个元素，返回栈最大容量、栈实际元素个数，打印栈中元素
    STACK stack(5);

    int e1 = 10, e2 = 20, e3 = 30, e4 = 40;
    stack << e1; stack << e2; stack << e3; stack << e4;

    char* s = new char[100];
    s[0] = '\0';
    cout << "stack栈最大容量" << stack.size() << "，栈实际元素个数" << int(stack) << "，栈中元素:";
    stack.print(s);
    cout << "\n\n";

    //2. 出栈
    int e;
    stack >> (e);
    cout << "出栈元素: " << e << "，出栈后栈内容：";
    stack.print(s);
    cout << "\n\n";

    //3. 用栈stack2深拷贝stack
    STACK stack2(stack);
    cout << "用栈stack2深拷贝stack，stack2为：";
    stack2.print(s);
    cout << "\n\n";

    //4. 用栈stack3移动拷贝stack
    STACK stack3(move(stack));
    cout << "用栈stack3移动拷贝stack，stack3为：";
    stack3.print(s);
    cout << "\n\n";

    //5. 清空栈
    stack.clear();
    cout << "清空栈stack：";
    stack.print(s);

}