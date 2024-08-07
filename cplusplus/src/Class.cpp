#include <iostream>
using namespace std;

// ����
class Shape {
public:
    virtual void draw() {
        std::cout << "Drawing a shape." << std::endl;
    }
};

// ������1
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

// ������2
class Square : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a square." << std::endl;
    }
};

class MyClass {
public:
    int value;

    // Ĭ�Ϲ��캯��
    MyClass() {
        value = 0;
        cout << "Default constructor called" << endl;
    }

    // �������Ĺ��캯��
    MyClass(int val) {
        value = val;
        cout << "MyClass Parameterized constructor called" << endl;
    }

    // �������캯��
    MyClass(const MyClass& obj) {
        value = obj.value;
        cout << "MyClass Copy constructor called" << endl;
    }

    // ��������
    ~MyClass() {
        cout << "MyClass Destructor called" << endl;
    }

    void test() {
        cout << "MyClass test" << endl;
    }
};

void test() {
    MyClass obj1;          // ����Ĭ�Ϲ��캯��
    MyClass obj2(42);      // ���ô������Ĺ��캯��
    MyClass obj3 = obj2;   // ���ÿ������캯��
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

    // ����ָ��ָ�����������ʵ�ֶ�̬��
    shape = &circle;
    shape->draw();  // ���� Circle �� draw ����

    shape = &square;
    shape->draw();  // ���� Square �� draw ����

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
