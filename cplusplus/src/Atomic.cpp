#include <iostream>
#include <atomic>
#include <thread>

std::atomic<int> sharedVariable(0);
void incrementVariable() {
    for (int i = 0; i < 1000000; ++i) {
        sharedVariable.fetch_add(1, std::memory_order_relaxed);
    }
}
void decrementVariable() {
    for (int i = 0; i < 1000000; ++i) {
        sharedVariable.fetch_sub(1, std::memory_order_relaxed);
    }
}

//int sharedVariable = 0;
//void incrementVariable() {
//    for (int i = 0; i < 1000000; ++i) {
//        sharedVariable++;
//    }
//}
//void decrementVariable() {
//    for (int i = 0; i < 1000000; ++i) {
//        sharedVariable--;
//    }
//}

int main() {
    std::thread thread1(incrementVariable);
    std::thread thread2(decrementVariable);

    thread1.join();
    thread2.join();

    std::cout << "Final value of sharedVariable: " << sharedVariable << std::endl;

    return 0;
}
