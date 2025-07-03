/**
 * Critical section:
 * A region of code must be executed by only one thread at a time. This usually happens when
 * accessing a shared resource such as shared data, network connection, hardware device, etc.
 *
 * Mutex: MUTual EXclusion object
 * A mutex has two states: locked and unlocked.
 * - MUtual: The threads agree to respect the mutex.
 * - EXclusion: The mutex is used to exclude threads from entering the critical section.
 * - Locking:
 *     - If the mutex is unlocked, a thread can enter the critical section.
 *     - If the mutex is locked, no thread can enter the critical section until it is unlocked.
 * 	   - A thread locks the mutex when it enters the critical section.
 * 	   - A thread unlocks the mutex when it exits the critical section.
 *
 * std::mutex has three main member functions:
 * - lock() tries to lock the mutex. If not successful, it waits until it locks the mutex.
 * - try_lock() tries to lock the mutex. It returns immediately, if not successful.
 * - unlock() releases the lock on the mutex.
 */

#include <iostream> // cout
#include <mutex>    // mutex
#include <string>   // string
#include <thread>   // thread

// Global mutex object
std::mutex task_mutex;

void task(const std::string &str) {
    for (int i = 0; i < 5; ++i) {
        // Lock the mutex before the critical section
        task_mutex.lock();

        // Start of critical section

        std::cout << str[0] << str[1] << str[2] << std::endl;

        // End of critical section

        // Unlock the mutex after the critical section
        task_mutex.unlock();
    }
}

////////////////////////////////////////////////////////////

using namespace std::literals;

std::mutex the_mutex;

void task1() {
    std::cout << "Task1 trying to lock the mutex" << std::endl;
    the_mutex.lock();
    std::cout << "Task1 has locked the mutex" << std::endl;
    std::this_thread::sleep_for(500ms);
    std::cout << "Task1 unlocking the mutex" << std::endl;
    the_mutex.unlock();
}

void task2() {
    std::this_thread::sleep_for(100ms);
    std::cout << "Task2 trying to lock the mutex" << std::endl;
    while (!the_mutex.try_lock()) {
        std::cout << "Task2 could not lock the mutex" << std::endl;
        std::this_thread::sleep_for(100ms);
    }
    std::cout << "Task2 has locked the mutex" << std::endl;
    the_mutex.unlock();
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 028-mutex_class.cpp && ./a.out
int main() {
    std::thread thr1(task, "abc");
    std::thread thr2(task, "def");
    std::thread thr3(task, "xyz");

    thr1.join();
    thr2.join();
    thr3.join();
    // abc
    // abc
    // abc
    // abc
    // abc
    // xyz
    // xyz
    // xyz
    // def
    // def
    // def
    // def
    // def
    // xyz
    // xyz

    std::cout << "--------------------------------" << std::endl;

    std::thread thr4(task2);
    std::thread thr5(task1);

    thr4.join();
    thr5.join();

    return 0;
}
