#include <iostream>

class MyClass {
public:
    static int staticVar;// ��̬��Ա��������
    static void staticFunction() {//��̬��Ա����
        std::cout << "staticFunction" << std::endl;
    }
};
int MyClass::staticVar = 0;// ��̬��Ա������ʼ��

void staticLocalVarFun() { // ��̬�ֲ�����
    static int staticLocalVar = 0;  
    std::cout << "staticLocalVarFun" << staticLocalVar << std::endl;
    staticLocalVar++;
}

static int staticGlobalVar = 0;  // ��̬ȫ�ֱ���,ȫ���������������ı����������������������ļ���

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