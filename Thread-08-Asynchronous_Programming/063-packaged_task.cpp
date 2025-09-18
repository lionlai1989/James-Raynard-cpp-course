/**
 * Synchronous Programming: wait for each task to complete before moving on
 *
 * Asynchronous programming: continue without waiting for tasks to complete
 *
 * Blocking Synchronization: synchronized by mutexes
 *  - A thread is blocked until another thread releases a mutex
 *
 * Non-blocking Synchronization: synchronized by message queues
 *  - A thread pushes a message onto a concurrent queue
 *  - Another thread takes the message off the queue and processes it
 *  - The first thread continues without waiting for the second thread
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std::literals;

/**
 * std::packaged_task defined in <future>
 * Encapsulates a task
 *  - A callable object (function, lambda expression, bind expression, or function object) for the
 *    task's code
 *  - An std::promise for the result of the task
 */

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 063-packaged_task.cpp && ./a.out
int main() {
    // Packaged task example
    // Executes the task in the current thread
    // Packaged task object
    // The callable object is a lambda expression
    // It takes int and int arguments
    // It returns int
    std::packaged_task<int(int, int)> ptask([](int a, int b) {
        std::this_thread::sleep_for(2s);
        return a + b;
    });

    // The promise object is an std::promise<int>
    // Get the future associated with it
    std::future<int> fut = ptask.get_future();

    // Directly invoke the packaged task in this thread
    ptask.operator()(6, 7);

    std::cout << "Waiting for result (blocking)\n";

    // Call get() to receive the result of the packaged task
    std::cout << "6 + 7 is " << fut.get() << '\n';

    std::cout << "--------------------------------\n";

    // Packaged task object
    // The callable object is a lambda expression
    // It takes int and int arguments
    // It returns int
    std::packaged_task<int(int, int)> ptask2([](int a, int b) {
        std::this_thread::sleep_for(2s);
        return a + b;
    });

    // The promise object is an std::promise<int>
    // Get the future associated with it
    auto fut2 = ptask2.get_future();

    // Start a new thread
    // The packaged task will be its entry point
    std::thread thr(std::move(ptask2), 8, 9);

    std::cout << "Waiting for result (non-blocking)\n";

    std::cout << "8 + 9 is " << fut2.get() << '\n';

    thr.join();
}