#include <chrono>   // sleep_for
#include <iostream> // cout
#include <thread>   // thread

void hello(int num) {
    // Add a delay
    std::this_thread::sleep_for(std::chrono::seconds(num));
    std::cout << "Hello from thread " << num << '\n';
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 023-multiple_threads.cpp && ./a.out
int main() {
    // Start 3 threads
    std::cout << "Starting 3 threads:\n";
    std::thread thr1(hello, 1);
    std::thread thr2(hello, 2);
    std::thread thr3(hello, 3);

    // Wait for the threads to finish
    thr1.join();
    thr2.join();
    thr3.join();
}
