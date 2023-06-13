// main.cpp: 定义应用程序的入口点。
#pragma once
#include <iostream>

using namespace std;

void use_sharedptr()
{
    //我们定义一个指向整形5得指针
    auto psint2 = make_shared<int>(5);
    auto psstr2 = make_shared<string>("hello zack");
    //将psint2赋值给psint3,他们底层的内置指针相同
    // psint3和psint2引用计数相同，引用计数+1，都为2
    shared_ptr<int> psint3 = psint2;
    //打印引用计数
    cout << "psint2 usecount is " << psint2.use_count() << endl;
    cout << "psint3 usecount is " << psint3.use_count() << endl;
    // psint3引用计数为1
    psint3 = make_shared<int>(1024);
    // psint2引用计数-1，变为1
    //打印引用计数
    cout << "psint2 usecount is " << psint2.use_count() << endl;
    cout << "psint3 usecount is " << psint3.use_count() << endl;
}

void good_use_sharedptr()
{
    shared_ptr<int> p(new int(5));
    //通过p获取内置指针q
    //注意q此时被p绑定，不要手动delete q
    int* q = p.get();
    {
        // m和p的引用计数都为2
        shared_ptr<int> m(p);
    }

    //上述}结束则m被回收，其绑定的q也被回收
    //此时使用q是非法操作，崩溃或者逻辑错误
    cout << "q data is " << *q << endl;
}

void bad_use_sharedptr()
{
    shared_ptr<int> p(new int(5));
    //通过p获取内置指针q
    //注意q此时被p绑定，不要手动delete q
    int* q = p.get();
    {
        //两个独立的shared_ptr m和p都绑定q
        auto m = shared_ptr<int>(q);
    }

    //上述}结束则m被回收，其绑定的q也被回收
    //此时使用q是非法操作，崩溃或者逻辑错误
    cout << "q data is " << *q << endl;
}
int main() {
	std::cout << "shareptr" << std::endl;
    use_sharedptr();
    good_use_sharedptr();
    //bad_use_sharedptr();
	return 0;
}
