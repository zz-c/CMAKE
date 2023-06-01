// main.cpp: 定义应用程序的入口点。
//
#include "main.h"
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
    getchar();
}
