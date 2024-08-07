#include <iostream>
using namespace std;

// 基类
class Shape {
public:
    virtual void draw() {
        std::cout << "Drawing a shape." << std::endl;
    }
};

// 派生类1
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

// 派生类2
class Square : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a square." << std::endl;
    }
};

class MyClass {
public:
    int value;

    // 默认构造函数
    MyClass() {
        value = 0;
        cout << "Default constructor called" << endl;
    }

    // 带参数的构造函数
    MyClass(int val) {
        value = val;
        cout << "MyClass Parameterized constructor called" << endl;
    }

    // 拷贝构造函数
    MyClass(const MyClass& obj) {
        value = obj.value;
        cout << "MyClass Copy constructor called" << endl;
    }

    // 析构函数
    ~MyClass() {
        cout << "MyClass Destructor called" << endl;
    }

    void test() {
        cout << "MyClass test" << endl;
    }
};

void test() {
    MyClass obj1;          // 调用默认构造函数
    MyClass obj2(42);      // 调用带参数的构造函数
    MyClass obj3 = obj2;   // 调用拷贝构造函数
    cout << "test()" << endl;
}

void test2() {
    MyClass* obj1 = new MyClass();
    delete obj1;
}

void test3(MyClass* obj) {
    obj->test();
}
void test32(MyClass obj) {
    obj.test();
}

int main() {
    Shape* shape;

    Circle circle;
    Square square;

    // 基类指针指向派生类对象，实现多态性
    shape = &circle;
    shape->draw();  // 调用 Circle 的 draw 函数

    shape = &square;
    shape->draw();  // 调用 Square 的 draw 函数

    // test();
    // test2();
    //MyClass* obj = new MyClass();
    //test3(obj);
    
    //MyClass obj;
    //test3(&obj);
    //test32(obj);
 
    getchar();
    return 0;
}
