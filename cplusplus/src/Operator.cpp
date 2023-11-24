#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    // ���ؼӷ������
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    // ������������
    friend std::ostream& operator<<(std::ostream& os, const Complex& obj);
};

class Counter {
private:
    int count;

public:
    Counter() : count(0) {}

    // ����ǰ׺���������
    Counter operator++() {
        ++count;
        return *this;
    }
    // ���غ�׺���������
    Counter operator++(int) {
        Counter temp = *this;
        ++count;
        return temp;
    }
    // ��ȡ����ֵ
    int getCount() const {
        return count;
    }
};

// ������������
std::ostream& operator<<(std::ostream& os, const Complex& obj) {
    os << obj.real << " + " << obj.imag << "i";
    return os;
}

int main() {
    Complex a(2.0, 3.0);
    Complex b(1.5, 2.5);
    // ʹ�����صļӷ������
    Complex result = a + b;
    // ʹ�����ص���������
    std::cout << "Result: " << result << std::endl;

    Counter counter;
    // ʹ��ǰ׺���������
    ++counter;
    std::cout << "Count after prefix increment: " << counter.getCount() << std::endl;
    // ʹ�ú�׺���������
    Counter anotherCounter = counter++;
    std::cout << "Count after postfix increment: " << counter.getCount() << std::endl;
    std::cout << "AnotherCounter: " << anotherCounter.getCount() << std::endl;

    return 0;
}
