#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std::literals;

/**
 * The `Vector` class is internally synchronized. The member functions lock a mutex before
 * they access a data member
 */
class Vector {
    std::mutex mtx;
    std::vector<int> vec;

  public:
    void push_back(const int &i) {
        mtx.lock();

        // Start of critical section

        vec.push_back(i);

        // End of critical section

        mtx.unlock();
    }

    void print() {
        /**
         * You may think that just because this `print()` only print the elements in the vector, the
         * `mtx.lock()` and `mtx.unlock()` are not necessary.
         * The truth is that if without the `mtx.lock()` and `mtx.unlock()`, it's no longer
         * thread-safe to access the `vec` object. And the problem is that when the member function
         * `push_back()` is executed, it will change the length of the `vec`. And if the `print()`
         * function is executed at the same time, it is a data race.
         */

        mtx.lock(); // Necessary even if the `print()` only print the elements in the vector

        // Start of critical section

        for (auto i : vec) {
            std::cout << i << ", ";
        }

        // End of critical section

        mtx.unlock(); // Necessary even if the `print()` only print the elements in the vector
    }
};

void func(Vector &vec) {
    for (int i = 0; i < 50; ++i) {
        vec.push_back(i);
        std::this_thread::sleep_for(50ms);
        vec.print();
    }
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 029-internal_sync_class.cpp && ./a.out
int main() {
    Vector vec;

    // std::ref() is used to pass `vec` by value and the value happens to be a reference to the
    // `vec` object.
    std::thread thr1(func, std::ref(vec));
    std::thread thr2(func, std::ref(vec));
    std::thread thr3(func, std::ref(vec));

    thr1.join();
    thr2.join();
    thr3.join();
}
