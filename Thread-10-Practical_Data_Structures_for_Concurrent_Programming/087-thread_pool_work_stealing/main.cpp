/**
 * In `086-thread_pool_multiple_queues`, it shows that a queue can be assigned to a thread in
 * a thread pool with multiple queues. However, this implementation has a problem: it doesn't handle
 * the case where a long-running task is added to the queue. This can delay the execution of other
 * tasks in the same queue.
 *
 * The following code shows the problem.
 *
 * To solve this problem, see `088-thread_pool_work_stealing_contd`.
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
    std::cout << "Thread id: " << std::this_thread::get_id() << " starting a task " << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "Thread id: " << std::this_thread::get_id() << " finishing a task " << std::endl;
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
}
