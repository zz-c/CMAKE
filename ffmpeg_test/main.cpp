// main.cpp: 定义应用程序的入口点。
//

#include "main.h"
#include "Test.h"

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}

using namespace std;

int main()
{
    std::cout << "Test FFmpeg" << std::endl;
    std::cout << avcodec_configuration() << std::endl;
    Test* test = new Test();
    //test->test01();
    test->testRtsp();
    //test->testCamera();
    getchar();
}
