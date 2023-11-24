#include <iostream>

// Ϊ int ���ʹ�������
typedef int Integer;
// Ϊ����ָ�����ʹ�������
typedef void (*FunctionPointer)();

// ʹ�� using �������
using Integer2 = int;
using FunctionPointer2 = void (*)();

void test(FunctionPointer fun) {
    fun();
}
void fun() {
    std::cout << "fun" << std::endl;
}

int main() {
    // ʹ�ñ���
    Integer num = 1;
    std::cout << "Number: " << num << std::endl;
    // ʹ�ú���ָ�����
    FunctionPointer funcPtr = []() {
        std::cout << "Function pointer called." << std::endl;
    };
    funcPtr();  // ���ú���ָ��
    test(funcPtr);
    test(fun);

    // ʹ�ñ���
    Integer2 num2 = 2;
    std::cout << "Number2: " << num2 << std::endl;
    // ʹ�ú���ָ�����
    FunctionPointer2 funcPtr2 = []() {
        std::cout << "Function2 pointer called." << std::endl;
    };
    funcPtr2();  // ���ú���ָ��

    return 0;
}
