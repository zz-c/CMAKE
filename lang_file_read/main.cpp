#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <filesystem>

class LangObj {
public:
    std::string key;
    std::string zh;
    std::string en;

    LangObj() {
    
    }
    ~LangObj() {
    
    }

};

std::vector<std::string> listFiles(const std::string& path) {
    std::vector<std::string> files;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((path + "/*").c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening directory: " << path << std::endl;
        return files;
    }
    do {
        if (findFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) {
            // 是文件
            files.push_back(findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    return files;
}
std::string UTF8ToGB(const char* str)
{
    std::string result;
    WCHAR* strSrc;
    LPSTR szRes;

    //获得临时变量的大小
    int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    strSrc = new WCHAR[i + 1];
    MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

    //获得临时变量的大小
    i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
    szRes = new CHAR[i + 1];
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

    result = szRes;
    delete[]strSrc;
    delete[]szRes;

    return result;
}
void readFile(std::string filePath, std::string fileName, std::map<std::string, LangObj>& langObjMap) {

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
    }
    // 读取文件内容或执行其他文件操作
    std::string line;
    while (std::getline(file, line)) {
        // 判断是否包含子字符串
        if (line.find("\":") == std::string::npos) {
            continue;
        }
        // std::cout << line << std::endl;
        // 双引号的位置
        size_t firstQuote = line.find("\"");
        size_t secondQuote = line.find("\"", firstQuote + 1);
        size_t thirdQuote = line.find("\"", secondQuote + 1);
        size_t fourthQuote = line.find("\"", thirdQuote + 1);
        // 截取双引号之间的子字符串
        if (firstQuote == std::string::npos && secondQuote == std::string::npos && thirdQuote == std::string::npos && fourthQuote == std::string::npos) {
            continue;
        }
        std::string key = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
        std::string zh = line.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);
        //std::cout << filePath << " find " << key << " " << zh << std::endl;
        //std::cout << filePath << " findZZZ " << key << " " << UTF8ToGB(line.c_str()) << std::endl;

        LangObj langObj;
        langObj.key = key;
        //langObj.zh = zh;
        langObj.zh = UTF8ToGB(zh.c_str());
        langObj.en = "-";
        langObjMap[fileName+":"+ key] = langObj;
    }
    file.close();
}

void readFileEn(std::string filePath, std::string fileName, std::map<std::string, LangObj>& langObjMap) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening en file." << std::endl;
    }
    // 读取文件内容或执行其他文件操作
    std::string line;
    while (std::getline(file, line)) {
        // 判断是否包含子字符串
        if (line.find("\":") == std::string::npos) {
            continue;
        }
        // std::cout << line << std::endl;
        // 双引号的位置
        size_t firstQuote = line.find("\"");
        size_t secondQuote = line.find("\"", firstQuote + 1);
        size_t thirdQuote = line.find("\"", secondQuote + 1);
        size_t fourthQuote = line.find("\"", thirdQuote + 1);
        // 截取双引号之间的子字符串
        if (firstQuote == std::string::npos && secondQuote == std::string::npos && thirdQuote == std::string::npos && fourthQuote == std::string::npos) {
            continue;
        }
        std::string key = line.substr(firstQuote + 1, secondQuote - firstQuote - 1);
        std::string en = line.substr(thirdQuote + 1, fourthQuote - thirdQuote - 1);

        auto it = langObjMap.find(fileName + ":" + key);
        if (it != langObjMap.end()) {
            it->second.en = en;
        }
        else {
            LangObj langObj;
            langObj.key = key;
            langObj.zh = "-";
            langObj.en = en;
            langObjMap[fileName + ":" + key] = langObj;
        }
    }
    file.close();
}

void createOutFile(std::string filePath, std::map<std::string, LangObj>& langObjMap) {
    // 创建一个输出文件流
    std::ofstream outputFile(filePath);
    // 检查文件是否成功打开
    if (!outputFile.is_open()) {
        std::cerr << "打开输出文件失败" << std::endl;
        return;
    }
    outputFile << "文件键值" << ",键值" << ",中文" << ",英文" << std::endl;
    // 遍历 map
    for (const auto& pair : langObjMap) {
        // std::cout << pair.first << "," << pair.second.key << "," << pair.second.zh << "," << pair.second.en << std::endl;
        //outputFile << pair.first << "," << pair.second.key << "," << pair.second.zh << "," << pair.second.en << std::endl;
        //outputFile << pair.first << "\t" << pair.second.key << "\t" << pair.second.zh << "\t" << pair.second.en << std::endl;
        outputFile << pair.first << "," << pair.second.key << "," << "\"" << pair.second.zh << "\"" << "," << "\"" << pair.second.en << "\"" << std::endl;
    }
    // 关闭文件流
    outputFile.close();
}

int main() {
    //const std::string pathZhDir = "G:/project/c/CMAKE/lang_file_read/source/zh-CN";
    //const std::string pathEnDir = "G:/project/c/CMAKE/lang_file_read/source/en";
    //const std::string outFile = "G:/project/c/CMAKE/lang_file_read/source/out.csv";
    const std::string pathZhDir = "./zh-CN";
    const std::string pathEnDir = "./en";
    const std::string outFile = "./out.csv";
    std::vector<std::string> filesName = listFiles(pathZhDir);
    std::map<std::string, LangObj> langObjMap;
    // 打印文件路径
    for (const auto& fileName : filesName) {
        std::cout << "文件" << fileName << "开始读取" << std::endl;
        readFile(pathZhDir + "/" + fileName, fileName, langObjMap);
        readFileEn(pathEnDir + "/" + fileName, fileName, langObjMap);
        std::cout << "文件" << fileName << "读取完成" << std::endl;
    }

    createOutFile(outFile, langObjMap);
    std::cout << "中英文翻译对照生成成功" << std::endl;

    getchar();
    return 0;
}