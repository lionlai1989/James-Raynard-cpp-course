/**
 * Lock-Free Programming
 * Google this topic for more information
 */

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

/**
 * Another way to solve double-checked locking
 * Make the lazily-initialized variable atomic
 *
 * Review `038-double_checked_locking.cpp` and compare it with this code.
 */
class Test {
    // ...
  public:
    void func() { /*...*/ }
};
std::atomic<Test *> ptest = nullptr; // Variable to be lazily initialized
std::mutex mut;
void process() {
    // First check of ptest
    if (!ptest) {
        std::lock_guard<std::mutex> lck_guard(mut);

        // Second check of ptest
        if (!ptest) {
            // Initialize ptest
            ptest = new Test;
        }
    }

    // Atomic pointers cannot be dereferenced
    // Copy it to a non-atomic pointer first
    Test *ptr_test = ptest;
    ptr_test->func();
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 060-lock_free_programming.cpp && ./a.out
int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread(process));
    for (auto &thr : threads)
        thr.join();
}
