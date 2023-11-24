#include <iostream>

int main() {
	//基本类型的转换
	double d = 3.14;
	int i = static_cast<int>(d);

	//指针类型的转换
	int j = 42;
	void* ptr = static_cast<void*>(&j);

	//枚举类型的转换
	enum class Color { RED, GREEN, BLUE };
	int value = static_cast<int>(Color::RED);

	//具有继承关系的类之间的转换 安全的转换方式是使用 dynamic_cast
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