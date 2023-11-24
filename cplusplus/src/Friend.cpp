#pragma once
#include <iostream>

class B;  // 前向声明

class A {
private:
    int privateMemberA;
public:
    A() : privateMemberA(0) {}
    // 将类 B 声明为 A 的友元
    friend class B;
    // 友元函数可以访问 A 的私有成员
    friend void displayPrivateMemberA(const A& obj);
};

class B {
public:
    void accessPrivateMemberA(const A& obj) {
        // 类 B 可以访问 A 的私有成员
        std::cout << "B accessing private member of A: " << obj.privateMemberA << std::endl;
    }
};

// 友元函数的定义
void displayPrivateMemberA(const A& obj) {
    // 友元函数可以访问 A 的私有成员
    std::cout << "Friend function accessing private member of A: " << obj.privateMemberA << std::endl;
}

int main() {
    A aObj;
    B bObj;

    // 类 B 的成员函数可以访问 A 的私有成员
    bObj.accessPrivateMemberA(aObj);

    // 友元函数可以访问 A 的私有成员
    displayPrivateMemberA(aObj);

    return 0;
}


