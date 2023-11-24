#include <iostream>
#include <vector>

// 类模板
template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T& value) {
        elements.push_back(value);
    }

    T pop() {
        if (elements.empty()) {
            std::cerr << "Stack is empty." << std::endl;
            exit(1);
        }
        T value = elements.back();
        elements.pop_back();
        return value;
    }

    // 函数模板 template <typename T>
    T maximum(T x, T y) {
        return (x > y) ? x : y;
    }
};

int main() {
    // 使用类模板创建具体的栈对象
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);

    std::cout << "Popped value from intStack: " << intStack.pop() << std::endl;
    std::cout << "Maximum of 5 and 10 is: " << intStack.maximum(5, 10) << std::endl;

    Stack<double> doubleStack;
    doubleStack.push(1.5);
    doubleStack.push(2.5);
    doubleStack.push(3.5);

    std::cout << "Popped value from doubleStack: " << doubleStack.pop() << std::endl;
    std::cout << "Maximum of 3.5 and 1.2 is: " << doubleStack.maximum(3.5, 1.2) << std::endl;

    return 0;
}
