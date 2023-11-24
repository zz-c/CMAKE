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
    int getValue() {
        return value;
    }

private:
    int value;
};

void test(std::shared_ptr<MyClass> ptr3) {
    std::cout << "usecount is " << ptr3.use_count() << std::endl;
}

void good_use_sharedptr()
{
    std::shared_ptr<int> p(new int(5));
    //通过p获取内置指针q
    //注意q此时被p绑定，不要手动delete q
    int* q = p.get();
    {
        // m和p的引用计数都为2
        std::shared_ptr<int> m(p);
    }

    //上述}结束则m被回收，其绑定的q也被回收
    //此时使用q是非法操作，崩溃或者逻辑错误
    std::cout << "q data is " << *q << std::endl;
}

void bad_use_sharedptr()
{
    std::shared_ptr<int> p(new int(5));
    //通过p获取内置指针q
    //注意q此时被p绑定，不要手动delete q
    int* q = p.get();
    {
        //两个独立的shared_ptr m和p都绑定q
        auto m = std::shared_ptr<int>(q);
    }

    //上述}结束则m被回收，其绑定的q也被回收
    //此时使用q是非法操作，崩溃或者逻辑错误
    std::cout << "q data is " << *q << std::endl;
}

int main() {
    // 创建 shared_ptr，它指向一个 MyClass 对象
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(42);
    // 创建另一个 shared_ptr，与前一个共享同一个对象
    std::shared_ptr<MyClass> ptr2 = ptr1;
    // 使用 shared_ptr 访问对象的成员函数
    ptr1->setValue(100);
    // 访问对象的成员
    std::cout << "Value from ptr2: " << ptr2->getValue() << std::endl;
    std::cout << "usecount is " << ptr1.use_count() << std::endl;
    test(ptr1);
    std::cout << "usecount is " << ptr1.use_count() << std::endl;
    // shared_ptr 在其生命周期结束时自动释放内存
    // 输出对象的析构函数调用信息
    return 0;
}
