#include <iostream>

int main() {
	//�������͵�ת��
	double d = 3.14;
	int i = static_cast<int>(d);

	//ָ�����͵�ת��
	int j = 42;
	void* ptr = static_cast<void*>(&j);

	//ö�����͵�ת��
	enum class Color { RED, GREEN, BLUE };
	int value = static_cast<int>(Color::RED);

	//���м̳й�ϵ����֮���ת�� ��ȫ��ת����ʽ��ʹ�� dynamic_cast
	class Base {};
	class Derived : public Base {
	public:
		void test() {
			std::cout << "test" << std::endl;
		}
	};
	Base* basePtr = new Derived;
	Derived* derivedPtr = static_cast<Derived*>(basePtr);
	derivedPtr->test();
}