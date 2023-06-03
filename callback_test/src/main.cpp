#pragma once
#include <iostream>

typedef void (*FPtr)(void);

typedef void (*FPtr2)(int);

class Test
{
public:

	

	friend void callBackFun(void) {
		std::cout << "CallBack Function!" << std::endl;
	}
	friend void callBackFun2(int i) {
		std::cout << "CallBack Function!" << i << std::endl;
	}

	static void callBackFun3(int i) {
		std::cout << "CallBack Function!" << i << std::endl;
	}
	void (*fPtrCall)(int);
};


void Fun(FPtr ptr){
	ptr();
}

void Fun2(FPtr2 ptr,int i){
	ptr(i);
}

int main() {

	std::cout << "c_base_test" << std::endl;

	Fun(callBackFun);

	Fun2(callBackFun2,5);

	void (*fPtrz)(int) = callBackFun2;
	fPtrz(6);

	
	void (*fPtr3)(int) = Test::callBackFun3;
	fPtr3(8);

	Test t;

	t.fPtrCall = Test::callBackFun3;
	t.fPtrCall(10);

	return 0;
}
