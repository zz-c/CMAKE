#include <iostream>

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

int main() {
    Shape* shape;

    Circle circle;
    Square square;

    // ����ָ��ָ�����������ʵ�ֶ�̬��
    shape = &circle;
    shape->draw();  // ���� Circle �� draw ����

    shape = &square;
    shape->draw();  // ���� Square �� draw ����

    getchar();
    return 0;
}
