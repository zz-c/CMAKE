#include <iostream>

// ���������Ķ���
inline int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(3, 4);  // ���������ܻὫ�˵�������չ���� a + b
    std::cout << "Result: " << result << std::endl;

    return 0;
}
