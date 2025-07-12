/**
 * Mutex Wrapper Classes
 *
 * The C++ library provides mutex wrapper classes, classes with a mutex object as a private member.
 * They uses RAII idiom for managing the mutex.
 */

#include <chrono>
#include <iostream>
#include <mutex> // mutex, lock_guard
#include <string>
#include <thread>

using namespace std::literals;

// Global mutex object
std::mutex task_mutex;
std::mutex task_mutex2;

void task(const std::string &str) {
    for (int i = 0; i < 5; ++i) {
        try {
            // Lock the mutex before the critical section
            // DO NOT USE IT. It's prone to deadlock.
            // This is the MAIN reason why we need other lock classes such as std::lock_guard,
            // std::unique_lock, etc.
            task_mutex.lock();

            // Start of critical section
            std::cout << str[0] << str[1] << str[2] << std::endl;

            // Critical section throws an exception
            throw std::exception();
            // End of critical section

            // Never gets called. The task_mutex is left locked.
            task_mutex.unlock();
            std::this_thread::sleep_for(50ms);
        } catch (std::exception &e) {
            std::cout << "Exception caught: " << e.what() << '\n';
        }
    }
}

void task2(std::string str) {
    for (int i = 0; i < 5; ++i) {
        try {
            // Create an std::lock_guard object. The constructor calls task_mutex2.lock()
            std::lock_guard<std::mutex> lck_guard(task_mutex2); // task_mutex2 is locked

            // Start of critical section
            std::cout << str[0] << str[1] << str[2] << std::endl;

            // Critical section throws an exception
            throw std::exception();
            // End of critical section

            // The mutex is still locked here after the end of the critical section. Other threads
            // cannot lock the mutex until the lock_guard object is destroyed.

            std::this_thread::sleep_for(50ms);
        } // Calls ~std::lock_guard. The destructor calls task_mutex2.unlock()
        catch (std::exception &e) {
            std::cout << "Exception caught: " << e.what() << '\n';
        }
    }
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 030-lock_guard.cpp && ./a.out
int main() {
    // std::thread thr1(task, "abc");
    // std::thread thr2(task, "def");
    // std::thread thr3(task, "xyz");

    // The entire program will stuck here, waiting for the three threads to finish, which will never
    // happen because the task_mutex is left locked.
    // thr1.join();
    // std::cout << "thr1 joined" << std::endl;
    // thr2.join();
    // std::cout << "thr2 joined" << std::endl;
    // thr3.join();
    // std::cout << "thr3 joined" << std::endl;

    std::cout << "--------------------------------" << std::endl;

    std::thread thr1(task2, "abc");
    std::thread thr2(task2, "def");
    std::thread thr3(task2, "xyz");

    thr1.join();
    std::cout << "thr1 joined" << std::endl;
    thr2.join();
    std::cout << "thr2 joined" << std::endl;
    thr3.join();
    std::cout << "thr3 joined" << std::endl;
}