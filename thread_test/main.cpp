// main.cpp: 定义应用程序的入口点。
#pragma once
#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "MMThread.h"

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;
int count = 0;

void producer() {
	while (true) {
		{	// 离开作用域后自动析构
			std::unique_lock<std::mutex> locker(mu); // 不能替换成lock_guard
			std::cout << "fun1 lock" << std::endl;
			q.push_front(count++);
			//locker.unlock(); // 没必要
			cond.notify_one();
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void consumer() {
	while (true) {
		std::unique_lock<std::mutex> locker(mu);
		std::cout << "fun2 lock" << std::endl;
		std::cout << "fun2 wait into" << std::endl;
		cond.wait(locker, []() {return !q.empty(); });
		std::cout << "fun2 wait leave" << std::endl;
		auto data = q.back();
		q.pop_back();
		// locker.unlock(); //没必要
		std::cout << "thread2 get value form thread1: " << data << std::endl;
	}
}

class MyMMThread : public MMThread
{
private:
	int a = 0;
public:
	MyMMThread(int _a)
	{
		a = _a;
	}

	virtual void run()
	{
		while (true) {
			printf("MyMMThread %d\n", a);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		
	}
};

int main() {
	//std::thread t1(producer);
	//std::thread t2(consumer);
	//t1.join();
	//t2.join();

	MyMMThread mmThread(10);
	mmThread.Start();
	
	getchar();


	return 0;
}
