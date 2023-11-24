#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//r，rb	以只读的方式打开文件
//w，wb	以只写的方式打开文件，若不存在，则新建文件，否则文件被截断（覆盖）
//a，ab	以追加的方式打开文件，若不存在，则新建该文件
//r + ，r + b，rb + 以读写方式打开文件
//w + ，w + b，wb + 以读写方式打开文件，若不存在，则新建文件，否则文件被截断（覆盖）
//a + ，a + b，ab + 以读和追加方式打开文件，若不存在，则新建文件
void testFile() {
	cout << "file test" << endl;
	FILE* fp;
	fp = fopen("E:/clib/test.txt", "ab");
	if (fp != nullptr) {
		cout << "文件存在" << endl;
	}
	else {
		cout << "文件不存在" << endl;
		return;
	}

	char str[14] = "abcdefg中文";
	fprintf(fp, "%s", str);
	fclose(fp);

	FILE* fp2;
	fp2 = fopen("E:/clib/test.txt", "r");

	char str2[100];
	fscanf(fp2, "%s", str2);
	cout << str2 << endl;
	fclose(fp2);

	//buffer
	FILE* fp3 = fopen("E:/clib/test.txt", "r");
	const int BUFFER_SIZE = 2;
	char buffer[BUFFER_SIZE];
	memset(buffer, '/0', BUFFER_SIZE);
	int length = 0;
	while ((length = fread(buffer, sizeof(char), BUFFER_SIZE, fp3)) > 0) {
		cout << buffer << endl;
		memset(buffer, '/0', BUFFER_SIZE);
	}
}
void testFile2() {
	string filename = string("E:/clib/test.txt");
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		printf("could not load file correctly...\n");
		return;
	}
	// 读取文件内容
	std::string line;
	while (std::getline(file, line)) {
		std::cout << "testFile2:" << line << std::endl;
	}

	// 关闭文件
	file.close();

}
int main() {

	testFile();
	testFile2();


	return 0;
}
