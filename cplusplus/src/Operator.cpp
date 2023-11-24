#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    // 重载加法运算符
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    // 重载输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Complex& obj);
};

class Counter {
private:
    int count;

public:
    Counter() : count(0) {}

    // 重载前缀递增运算符
    Counter operator++() {
        ++count;
        return *this;
    }
    // 重载后缀递增运算符
    Counter operator++(int) {
        Counter temp = *this;
        ++count;
        return temp;
    }
    // 获取计数值
    int getCount() const {
        return count;
    }
};

// 输出运算符重载
std::ostream& operator<<(std::ostream& os, const Complex& obj) {
    os << obj.real << " + " << obj.imag << "i";
    return os;
}

int main() {
    Complex a(2.0, 3.0);
    Complex b(1.5, 2.5);
    // 使用重载的加法运算符
    Complex result = a + b;
    // 使用重载的输出运算符
    std::cout << "Result: " << result << std::endl;

    Counter counter;
    // 使用前缀递增运算符
    ++counter;
    std::cout << "Count after prefix increment: " << counter.getCount() << std::endl;
    // 使用后缀递增运算符
    Counter anotherCounter = counter++;
    std::cout << "Count after postfix increment: " << counter.getCount() << std::endl;
    std::cout << "AnotherCounter: " << anotherCounter.getCount() << std::endl;

    return 0;
}
