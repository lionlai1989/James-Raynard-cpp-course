// Test program for Meyers Singleton
#include "cpp11_singleton.h"
#include <thread>
#include <vector>

void task() {
    Singleton &single = get_Singleton();
    std::cout << &single << std::endl;
}

// g++ -std=c++11 -Wall cpp11_singleton_main.cc cpp11_singleton.cc && ./a.out
int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread(task));

    for (auto &thr : threads)
        thr.join();

    // The output shows constructor are called only one once.
    // Initializing Singleton
    // 0x74f404000b70
    // 0x74f404000b70
    // 0x74f404000b70
    // 0x74f404000b70
    // 0x74f404000b70
    // 0x74f404000b70
    // 0x74f404000b70
    // 0x74f404000b70
    // 0x74f404000b70
    // 0x74f404000b70
}