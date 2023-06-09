// main.cpp: 定义应用程序的入口点。
#pragma once
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
#ifdef USE_MYDEF 
    std::cout << "Test CMAKE USE_MYDEF" << std::endl;
#else
    std::cout << "Test CMAKE" << std::endl;
#endif 

#if defined(WIN32) || defined(_WIN32) 
    std::cout << "WIN32" << std::endl;
#endif 




#ifdef COMPILE_M1
    printf("Defined macro: COMPILE_M1\n");
#endif

#if COMPILE_M2 == 0x100
    printf("Macro COMPILE_M2: 0x%x\n", COMPILE_M2);
#endif

#if COMPILE_M3 == 0x200
    printf("Macro COMPILE_M3: 0x%x\n", COMPILE_M3);
#endif

#ifdef COMPILE_M4
    printf("Macro COMPILE_M4 is defined by cmake command\n");
#endif

    getchar();
}
