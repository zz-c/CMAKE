#include <windows.h>
#include <iostream>

int main() {
    // 打开音频文件，指定别名为 "mymusic"
    MCIERROR error = mciSendString(TEXT("open \"E:/clib/data/test-cg.mp3\" type mpegvideo alias mymusic"), NULL, 0, NULL);
    if (error) {
        // 输出错误信息
        TCHAR errorMessage[128];
        mciGetErrorString(error, errorMessage, 128);
        std::wcout << L"Error: " << errorMessage << std::endl;
        return 1;
    }

    // 播放音频文件
    mciSendString(TEXT("play mymusic"), NULL, 0, NULL);

    //mciSendString(TEXT("open \"E:/clib/data/test.mp3\" type mpegvideo alias mymusic2"), NULL, 0, NULL);
    //mciSendString(TEXT("play mymusic2"), NULL, 0, NULL);

    // 等待用户输入任意键停止播放
    std::cout << "Press Enter to stop playing..." << std::endl;
    std::cin.get();

    // 停止播放
    mciSendString(TEXT("stop mymusic"), NULL, 0, NULL);

    // 关闭音频文件
    mciSendString(TEXT("close mymusic"), NULL, 0, NULL);

    return 0;
}
