#pragma once
#include <iostream>
using namespace std;

//r，rb	以只读的方式打开文件
//w，wb	以只写的方式打开文件，若不存在，则新建文件，否则文件被截断（覆盖）
//a，ab	以追加的方式打开文件，若不存在，则新建该文件
//r + ，r + b，rb + 以读写方式打开文件
//w + ，w + b，wb + 以读写方式打开文件，若不存在，则新建文件，否则文件被截断（覆盖）
//a + ，a + b，ab + 以读和追加方式打开文件，若不存在，则新建文件


int main() {
	cout << "file test" << endl;
	FILE* fp;
	fp = fopen("E:/clib/test.txt", "ab");
	if (fp != nullptr){
		cout << "文件存在" << endl;
	}else{
		cout << "文件不存在" << endl;
		return 0;
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
	
	return 0;
}
