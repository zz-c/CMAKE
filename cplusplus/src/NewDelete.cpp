#include <iostream>

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructor" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destructor" << std::endl;
    }
};

int main() {
    // ʹ�� new ������������
    MyClass* obj = new MyClass;

    // ʹ����������Ҫ�ֶ��ͷ��ڴ�
    delete obj;

    return 0;
}
