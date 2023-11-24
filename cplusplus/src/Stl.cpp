#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

void testVector() {
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //v����ʼ������10��Ԫ��
    cout << "��һ�ֱ���������" << endl;
    //size����Ԫ�ظ���
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " "; //����ͨ����һ��ʹ��vector����
    //����һ���������������Ȼ��vectorҲ֧������ 3 �ֶ���������ķ�ʽ

    cout << endl << "�ڶ��ֱ���������" << endl;
    vector<int>::iterator i;
    //�� != �Ƚ�����������
    for (i = v.begin(); i != v.end(); ++i)
        cout << *i << " ";

    cout << endl << "�����ֱ���������" << endl;
    for (i = v.begin(); i < v.end(); ++i) //�� < �Ƚ�����������
        cout << *i << " ";

    cout << endl << "�����ֱ���������" << endl;
    i = v.begin();
    while (i < v.end()) { //���һ�����
        cout << *i << " ";
        i += 2; // ������ʵ�����֧�� "+= ����"  �Ĳ���
    }
}

void testList() {
    //�����յ� list ����
    list<double> values;
    //�����������Ԫ��
    values.push_back(3.1);
    values.push_back(2.2);
    values.push_back(2.9);
    cout << "values size��" << values.size() << endl;
    //�������е�Ԫ�ؽ�������
    values.sort();
    //ʹ�õ��������list�����е�Ԫ��
    for (list<double>::iterator it = values.begin(); it != values.end(); ++it) {
        cout << *it << " ";
    }
}

void testMap() {
    //��������ʼ�� map ����
    map<string, string> myMap{ {"STL�̳�", "http://c.biancheng.net/stl/"}, { "C���Խ̳�","http://c.biancheng.net/c/" }, { "Java�̳�","http://c.biancheng.net/java/" } };

    string cValue = myMap["C���Խ̳�"];
    cout << cValue << endl;

    pair<string, string> STL = { "pair�̳�","http://c.biancheng.net/stl/" };
    myMap.insert(STL);

    for (map<string, string>::iterator iter = myMap.begin(); iter != myMap.end(); ++iter) {
        cout << iter->first << " " << iter->second << endl;
    }
}

int main() {
    cout << "stl test" << endl;
    //testVector();
    //testList();
    testMap();

    return 0;
}
