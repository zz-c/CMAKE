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
    // 使用 new 创建单个对象
    MyClass* obj = new MyClass;

    // 使用完对象后需要手动释放内存
    delete obj;

    return 0;
}
