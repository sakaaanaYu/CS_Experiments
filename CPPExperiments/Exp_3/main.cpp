#include "exp3.h"

int main() {
	//1. ��ʼ��ջ��m=5�������4��Ԫ�أ�����ջ���������ջʵ��Ԫ�ظ�������ӡջ��Ԫ��
	STACK stack(5);
	stack.enter(10);
	stack.enter(20, 30, 40); 
    char s[100] = { 0 };
    stack.print(s);
	cout << "stackջ�������" << stack.size() << "��ջʵ��Ԫ�ظ���" << stack.number() << "ջ��Ԫ��:" << s << "\n\n";

    //2. ��ջһ��Ԫ��
    int e;
    stack.leave(e);
    stack.print(s);
    cout << "��ջԪ��: " << e << "����ջ��ջ���ݣ�" << s << "\n\n";

    //3. ������ջ
    int buf[5], n = 2;
    stack.leave(n, buf);
	stack.print(s);
    cout << "������ջ2��Ԫ�أ���ջ��ջ���ݣ�" << s << "\n\n";

    //4. ��ջstack2���stack
    STACK stack2(stack);
    stack2.print(s);
    cout << "��ջstack2���stack��stack2Ϊ��" << s << "\n\n";

	//5. ��ջstack3�ƶ�����stack
    STACK stack3(move(stack));
    stack3.print(s);
    cout << "��ջstack3�ƶ�����stack��stack3Ϊ��" << s << "\n\n";

    //6. ���ջ
    stack.clear();
    stack.print(s);
    cout << "���ջstack��" << s << "\n";

    //7. ����ջ
    stack.~stack();
}
