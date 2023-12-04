#include <iostream>

extern "C" {
    __declspec(dllexport) int add(int a, int b) {
        std::cout << "add," << a << "," << b << std::endl;
        return a + b;
    }
}
