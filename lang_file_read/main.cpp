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
        std::cout << filePath << " find " << key << " " << zh << std::endl;

        LangObj langObj;
        langObj.key = key;
        langObj.zh = zh;
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
    }
    file.close();
}

int main() {
    std::map<std::string, LangObj> langObjMap;

    const std::string pathZhDir = "G:/project/c/CMAKE/lang_file_read/source/zh-CN";
    const std::string pathEnDir = "G:/project/c/CMAKE/lang_file_read/source/en";
    const std::string outFile = "G:/project/c/CMAKE/lang_file_read/source/out.csv";
    std::vector<std::string> filesName = listFiles(pathZhDir);
    // 打印文件路径
    for (const auto& fileName : filesName) {
        std::cout << fileName << std::endl;
        readFile(pathZhDir + "/" + fileName, fileName, langObjMap);
        readFileEn(pathEnDir + "/" + fileName, fileName, langObjMap);
        std::cout << "文件" << fileName << "读取完成" << std::endl;
    }

    // 创建一个输出文件流
    std::ofstream outputFile(outFile);
    // 检查文件是否成功打开
    if (!outputFile.is_open()) {
        std::cerr << "打开输出文件失败" << std::endl;
        return 1;
    }
    outputFile << "文件键值" << ",键值" << ",中文" << ",英文" << std::endl;
    // 遍历 map
    for (const auto& pair : langObjMap) {
        std::cout << pair.first << "," << pair.second.key << "," << pair.second.zh << "," << pair.second.en << std::endl;
        outputFile << pair.first << ", " << pair.second.key << "," << pair.second.zh << "," << pair.second.en << std::endl;
    }
    // 关闭文件流
    outputFile.close();
    std::cout << "中英文翻译对照生成成功" << std::endl;

    return 0;
}