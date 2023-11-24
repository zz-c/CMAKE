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
    int getValue() {
        return value;
    }

private:
    int value;
};

void test(std::shared_ptr<MyClass> ptr3) {
    std::cout << "usecount is " << ptr3.use_count() << std::endl;
}

void good_use_sharedptr()
{
    std::shared_ptr<int> p(new int(5));
    //ͨ��p��ȡ����ָ��q
    //ע��q��ʱ��p�󶨣���Ҫ�ֶ�delete q
    int* q = p.get();
    {
        // m��p�����ü�����Ϊ2
        std::shared_ptr<int> m(p);
    }

    //����}������m�����գ���󶨵�qҲ������
    //��ʱʹ��q�ǷǷ����������������߼�����
    std::cout << "q data is " << *q << std::endl;
}

void bad_use_sharedptr()
{
    std::shared_ptr<int> p(new int(5));
    //ͨ��p��ȡ����ָ��q
    //ע��q��ʱ��p�󶨣���Ҫ�ֶ�delete q
    int* q = p.get();
    {
        //����������shared_ptr m��p����q
        auto m = std::shared_ptr<int>(q);
    }

    //����}������m�����գ���󶨵�qҲ������
    //��ʱʹ��q�ǷǷ����������������߼�����
    std::cout << "q data is " << *q << std::endl;
}

int main() {
    // ���� shared_ptr����ָ��һ�� MyClass ����
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>(42);
    // ������һ�� shared_ptr����ǰһ������ͬһ������
    std::shared_ptr<MyClass> ptr2 = ptr1;
    // ʹ�� shared_ptr ���ʶ���ĳ�Ա����
    ptr1->setValue(100);
    // ���ʶ���ĳ�Ա
    std::cout << "Value from ptr2: " << ptr2->getValue() << std::endl;
    std::cout << "usecount is " << ptr1.use_count() << std::endl;
    test(ptr1);
    std::cout << "usecount is " << ptr1.use_count() << std::endl;
    // shared_ptr �����������ڽ���ʱ�Զ��ͷ��ڴ�
    // ����������������������Ϣ
    return 0;
}
