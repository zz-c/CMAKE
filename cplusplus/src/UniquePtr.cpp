#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "Constructor called. Value: " << value << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called. Value: " << value << std::endl;
    }

    void setValue(int val) {
        value = val;
    }

    int getValue() const {
        return value;
    }

private:
    int value;
};
void test(std::unique_ptr<MyClass> ptr3) {// 错误
    std::cout << "Value from ptr3: " << ptr3->getValue() << std::endl;
}

int main() {
    // 创建 unique_ptr，它指向一个 MyClass 对象
    std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>(42);
    // 不能直接复制 unique_ptr，因为它是独占所有权的
    // std::unique_ptr<MyClass> ptr2 = ptr1; // 错误
    //test(ptr1);// 错误
    // 可以通过 std::move 转移所有权
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);
    // 使用 unique_ptr 访问对象的成员函数
    ptr2->setValue(100);
    // 访问对象的成员
    std::cout << "Value from ptr2: " << ptr2->getValue() << std::endl;
    // unique_ptr 在其生命周期结束时自动释放内存
    // 输出对象的析构函数调用信息
    return 0;
}
