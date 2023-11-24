#include <iostream>

// 为 int 类型创建别名
typedef int Integer;
// 为函数指针类型创建别名
typedef void (*FunctionPointer)();

// 使用 using 定义别名
using Integer2 = int;
using FunctionPointer2 = void (*)();

void test(FunctionPointer fun) {
    fun();
}
void fun() {
    std::cout << "fun" << std::endl;
}

int main() {
    // 使用别名
    Integer num = 1;
    std::cout << "Number: " << num << std::endl;
    // 使用函数指针别名
    FunctionPointer funcPtr = []() {
        std::cout << "Function pointer called." << std::endl;
    };
    funcPtr();  // 调用函数指针
    test(funcPtr);
    test(fun);

    // 使用别名
    Integer2 num2 = 2;
    std::cout << "Number2: " << num2 << std::endl;
    // 使用函数指针别名
    FunctionPointer2 funcPtr2 = []() {
        std::cout << "Function2 pointer called." << std::endl;
    };
    funcPtr2();  // 调用函数指针

    return 0;
}
