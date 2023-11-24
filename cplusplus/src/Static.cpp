#include <iostream>

class MyClass {
public:
    static int staticVar;// 静态成员变量声明
    static void staticFunction() {//静态成员函数
        std::cout << "staticFunction" << std::endl;
    }
};
int MyClass::staticVar = 0;// 静态成员变量初始化

void staticLocalVarFun() { // 静态局部变量
    static int staticLocalVar = 0;  
    std::cout << "staticLocalVarFun" << staticLocalVar << std::endl;
    staticLocalVar++;
}

static int staticGlobalVar = 0;  // 静态全局变量,全局作用域内声明的变量将被限制在声明它的文件中

int main() {
   
    std::cout << "MyClass::staticVar: " << MyClass::staticVar << std::endl;
    MyClass::staticVar++;
    std::cout << "MyClass::staticVar: " << MyClass::staticVar << std::endl;

    MyClass::staticFunction();
   
    staticLocalVarFun();
    staticLocalVarFun();

    std::cout << "staticGlobalVar: " << staticGlobalVar << std::endl;

    return 0;
}