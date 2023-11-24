#include <iostream>
#include <thread>

class MyClass {
public:
    static void staticFunction() {//静态成员函数
        std::cout << "MyClass staticFunction" << std::endl;
    }
    static void staticFunction2(std::string y) {//静态成员函数
        std::cout << "MyClass staticFunction" << ",y=" << y << std::endl;
    }
    void testFunction(std::string y) {
        std::cout << "MyClass testFunction" << ",y=" << y << std::endl;
    }
};

int main() {
    // Lambda 表达式，没有捕获变量
    auto func = []() {
        std::cout << "Hello, from lambda!" << std::endl;
    };
    // 调用 lambda 表达式
    func();

    // Lambda 表达式，捕获外部变量
    int x = 42;
    auto funcWithCapture = [x](std::string y) {
        std::cout << "Value of captured variable: " << x << ",y=" << y << std::endl;
    };
    // 调用带有捕获变量的 lambda 表达式
    funcWithCapture("7");

    std::thread testThread([]() {std::cout << "Hello, zzz from lambda!" << std::endl; });
    testThread.join();

    std::thread testThread1(func);
    testThread1.join();

    std::thread test2Thread(funcWithCapture,"test2Thread");
    test2Thread.join();

    std::thread test3Thread(MyClass::staticFunction);
    test3Thread.join();

    std::thread test4Thread(MyClass::staticFunction2,"test4Thread");
    test4Thread.join();
    
    MyClass myClass;
    std::thread test5Thread(&MyClass::testFunction, &myClass,"test5Thread");
    test5Thread.join();

    std::thread test6Thread([&myClass]() {
        myClass.testFunction("test6Thread");
    });
    test6Thread.join();

    return 0;
}
