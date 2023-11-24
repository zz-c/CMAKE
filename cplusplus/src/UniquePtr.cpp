#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "Constructor called. Value: " << value << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called. Value: " << value << std::endl;
    }

    void setValue(int val) {
        value = val;
    }

    int getValue() const {
        return value;
    }

private:
    int value;
};
void test(std::unique_ptr<MyClass> ptr3) {// ����
    std::cout << "Value from ptr3: " << ptr3->getValue() << std::endl;
}

int main() {
    // ���� unique_ptr����ָ��һ�� MyClass ����
    std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>(42);
    // ����ֱ�Ӹ��� unique_ptr����Ϊ���Ƕ�ռ����Ȩ��
    // std::unique_ptr<MyClass> ptr2 = ptr1; // ����
    //test(ptr1);// ����
    // ����ͨ�� std::move ת������Ȩ
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);
    // ʹ�� unique_ptr ���ʶ���ĳ�Ա����
    ptr2->setValue(100);
    // ���ʶ���ĳ�Ա
    std::cout << "Value from ptr2: " << ptr2->getValue() << std::endl;
    // unique_ptr �����������ڽ���ʱ�Զ��ͷ��ڴ�
    // ����������������������Ϣ
    return 0;
}
