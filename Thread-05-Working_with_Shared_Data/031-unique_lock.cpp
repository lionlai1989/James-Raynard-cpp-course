/**
 * std::unique_lock
 * The issue of std::lock_guard is demonstrated below:
 *
 * try {
 *     std::lock_guard<std::mutex> lck_guard(mtx);
 *
 *     // Start of critical section
 *     std::cout << str[0] << str[1] << str[2] << std::endl;
 *     // End of critical section
 *
 *     // The mutex is still locked here after the end of the critical section. Other threads
 *     // cannot lock the mutex until the lock_guard object goes out of scope and is destroyed by
 *     // the destructor.
 *
 *     // This is a WASTE of time because other threads need to wait for the current thread to
 *     // finish.
 *     std::this_thread::sleep_for(50ms); // Mimic the current thread is still doing something.
 *
 * } // Calls ~std::lock_guard. The destructor calls mtx.unlock()
 * catch (std::exception &e) {
 *     std::cout << "Exception caught: " << e.what() << '\n';
 * }
 *
 * std::unique_lock is used to solve the above issue. It has an unlock() method that can be called
 * to unlock the mutex after the critical section. This will AVOID blocking other threads while we
 * execute non-critical code.
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std::literals;

std::mutex print_mutex;

void task(std::string str) {
    for (int i = 0; i < 5; ++i) {
        // Create an std::unique_lock object
        // This calls print_mutex.lock()
        std::unique_lock<std::mutex> uniq_lck(print_mutex);

        // Start of critical section
        std::cout << str[0] << str[1] << str[2] << std::endl;
        // End of critical section

        // Unlock the mutex. This unblocks other threads.
        // Comment this out to see the scrambled output.
        uniq_lck.unlock();

        std::this_thread::sleep_for(50ms);
    } // Calls ~std::unique_lock
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 031-unique_lock.cpp && ./a.out
int main() {
    std::thread thr1(task, "abc");
    std::thread thr2(task, "def");
    std::thread thr3(task, "xyz");

    thr1.join();
    thr2.join();
    thr3.join();

    return 0;
}