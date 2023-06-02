#ifndef BXC_COMMON_H
#define BXC_COMMON_H

#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#pragma warning( disable : 4996 )

namespace BXC {

    static std::string getCurTimeStr() {
        const char* time_fmt = "%Y-%m-%d %H:%M:%S";
        time_t t = time(nullptr);
        char time_str[64];
        strftime(time_str, sizeof(time_str), time_fmt, localtime(&t));
        return time_str;
    }

    //  __FILE__ 获取源文件的相对路径和名字
    //  __LINE__ 获取该行代码在文件中的行号
    //  __func__ 或 __FUNCTION__ 获取函数名

#define LOGI(format, ...)  fprintf(stderr,"[DVCINFO]%s [%s:%d] " format "\n", getCurTimeStr().data(),__func__,__LINE__,##__VA_ARGS__)
#define LOGE(format, ...)  fprintf(stderr,"[DVCERROR]%s [%s:%d] " format "\n",getCurTimeStr().data(),__func__,__LINE__,##__VA_ARGS__)


    static int64_t getCurTime()// 获取当前系统启动以来的毫秒数
    {
        long long now = std::chrono::steady_clock::now().time_since_epoch().count();
        return now / 1000000;
    }
    static int64_t getCurTimestamp()// 获取毫秒级时间戳（13位）
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).
            count();

    }

    //static std::ofstream LOGFile{};

    static void WRITELOG(std::string log) {
        //if (!LOGFile) {
        //    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        //    std::string logFilename = "VideoCompatible.log";
        //    LOGFile.open(logFilename, std::ofstream::app);
        //}
        //LOGFile << getCurTimeStr() << " : " << log << "\n";
        //LOGFile.flush();

        std::ofstream logFile;
        std::string logFilename = "VideoCompatible.log";
        logFile.open(logFilename, std::ofstream::app);
        logFile << getCurTimeStr() << " : " << log << "\n";
        logFile.close();
    }
}

#endif //BXC_COMMON_H