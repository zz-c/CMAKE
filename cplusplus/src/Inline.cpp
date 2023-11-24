#include <iostream>

// 内联函数的定义
inline int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(3, 4);  // 编译器可能会将此调用内联展开成 a + b
    std::cout << "Result: " << result << std::endl;

    return 0;
}
