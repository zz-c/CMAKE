#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//r��rb	��ֻ���ķ�ʽ���ļ�
//w��wb	��ֻд�ķ�ʽ���ļ����������ڣ����½��ļ��������ļ����ضϣ����ǣ�
//a��ab	��׷�ӵķ�ʽ���ļ����������ڣ����½����ļ�
//r + ��r + b��rb + �Զ�д��ʽ���ļ�
//w + ��w + b��wb + �Զ�д��ʽ���ļ����������ڣ����½��ļ��������ļ����ضϣ����ǣ�
//a + ��a + b��ab + �Զ���׷�ӷ�ʽ���ļ����������ڣ����½��ļ�
void testFile() {
	cout << "file test" << endl;
	FILE* fp;
	fp = fopen("E:/clib/test.txt", "ab");
	if (fp != nullptr) {
		cout << "�ļ�����" << endl;
	}
	else {
		cout << "�ļ�������" << endl;
		return;
	}

	char str[14] = "abcdefg����";
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
	// ��ȡ�ļ�����
	std::string line;
	while (std::getline(file, line)) {
		std::cout << "testFile2:" << line << std::endl;
	}

	// �ر��ļ�
	file.close();

}
int main() {

	testFile();
	testFile2();


	return 0;
}
