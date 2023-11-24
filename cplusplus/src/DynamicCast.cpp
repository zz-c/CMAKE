#include <iostream>

class Base {
public:
    virtual ~Base() {}
};

class Derived1 : public Base {
public:
    ~Derived1() {
        std::cout << "~Derived1" << std::endl;
    }
    void derived1Method() {
        std::cout << "Derived1 method" << std::endl;
    }
};

class Derived2 : public Base {
public:
    ~Derived2() {
        std::cout << "~Derived2" << std::endl;
    }
    void derived2Method() {
        std::cout << "Derived2 method" << std::endl;
    }
};

int main() {
    Derived1 obj1;
    Derived2 obj2;

    // 使用 dynamic_cast 判断对象的实际类型
    Base* ptr1 = &obj1;
    Base* ptr2 = &obj2;

    Derived1* d1 = dynamic_cast<Derived1*>(ptr1);
    if (d1 != nullptr) {
        std::cout << "Object is of type Derived1" << std::endl;
        d1->derived1Method();
    }
    else {
        std::cout << "Object is of unknown type" << std::endl;
    }
    Derived2* d2 = dynamic_cast<Derived2*>(ptr2);
    if (d2 != nullptr) {
        std::cout << "Object is of type Derived2" << std::endl;
        d2->derived2Method();
    }
    else {
        std::cout << "Object is of unknown type" << std::endl;
    }

    return 0;
}
