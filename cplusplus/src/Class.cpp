#include <iostream>

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

int main() {
    Shape* shape;

    Circle circle;
    Square square;

    // 基类指针指向派生类对象，实现多态性
    shape = &circle;
    shape->draw();  // 调用 Circle 的 draw 函数

    shape = &square;
    shape->draw();  // 调用 Square 的 draw 函数

    getchar();
    return 0;
}
