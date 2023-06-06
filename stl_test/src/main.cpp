#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <map>
using namespace std;

void testVector() {
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //v被初始化成有10个元素
    cout << "第一种遍历方法：" << endl;
    //size返回元素个数
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " "; //像普通数组一样使用vector容器
    //创建一个正向迭代器，当然，vector也支持其他 3 种定义迭代器的方式

    cout << endl << "第二种遍历方法：" << endl;
    vector<int>::iterator i;
    //用 != 比较两个迭代器
    for (i = v.begin(); i != v.end(); ++i)
        cout << *i << " ";

    cout << endl << "第三种遍历方法：" << endl;
    for (i = v.begin(); i < v.end(); ++i) //用 < 比较两个迭代器
        cout << *i << " ";

    cout << endl << "第四种遍历方法：" << endl;
    i = v.begin();
    while (i < v.end()) { //间隔一个输出
        cout << *i << " ";
        i += 2; // 随机访问迭代器支持 "+= 整数"  的操作
    }
}

void testList() {
    //创建空的 list 容器
    list<double> values;
    //向容器中添加元素
    values.push_back(3.1);
    values.push_back(2.2);
    values.push_back(2.9);
    cout << "values size：" << values.size() << endl;
    //对容器中的元素进行排序
    values.sort();
    //使用迭代器输出list容器中的元素
    for (list<double>::iterator it = values.begin(); it != values.end(); ++it) {
        cout << *it << " ";
    }
}

void testMap() {
    //创建并初始化 map 容器
    map<string, string> myMap{ {"STL教程", "http://c.biancheng.net/stl/"},{ "C语言教程","http://c.biancheng.net/c/" },{ "Java教程","http://c.biancheng.net/java/" } };

    string cValue = myMap["C语言教程"];
    cout << cValue << endl;

    pair<string, string> STL = { "pair教程","http://c.biancheng.net/stl/" };
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
