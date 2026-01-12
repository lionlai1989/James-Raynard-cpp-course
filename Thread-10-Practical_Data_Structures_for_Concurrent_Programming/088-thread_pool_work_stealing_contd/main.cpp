/**
 * Test program for thread pool with work stealing
 * We put a long-running task on one queue
 * Other threads execute the tasks behind it
 */

#include "thread_pool.h"

#include <iostream>

using namespace std::literals;

// A task function
void task() {
    std::cout << "Thread id: " << std::this_thread::get_id() << " starting a task " << std::endl;
    std::this_thread::sleep_for(100ms);
    std::cout << "Thread id: " << std::this_thread::get_id() << " finishing a task " << std::endl;
}

// A long-running task function
void task2() {
    std::cout << "Thread id: " << std::this_thread::get_id() << " starting a long-running task "
              << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "Thread id: " << std::this_thread::get_id() << " finishing a long-running task "
              << std::endl;
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread main.cpp thread_pool.cpp && ./a.out
int main() {
    // Create the thread pool
    ThreadPool pool;

    // Send one long-running task to the thread pool
    pool.submit(task2);

    // Send 200 tasks to the thread pool
    for (int i = 0; i < 200; ++i)
        pool.submit(task);

    pool.submit([&pool]() {
        std::this_thread::sleep_for(6s);
        std::cout << "All tasks completed" << std::endl;
    });

    std::cout << "Main thread exiting" << std::endl;

    // Notice that before "All tasks completed", the "finishing a long-running task" shall be
    // printed. This is because all other tasks (`task`) are executed by the other threads before
    // the thread that runs the long-running task (`task2`).
}
