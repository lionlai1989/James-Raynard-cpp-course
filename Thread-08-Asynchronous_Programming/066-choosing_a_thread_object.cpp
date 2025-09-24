/**
 * We now have three different ways to execute a task:
 *  - Create an std::thread object
 *  - Create an std::packaged_task object
 *  - Call std::async()
 * Each of these has its own advantages and disadvantages.
 *
 * Which one should we use?
 */

#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;

// async_future_destructor.cc
// The destructor for std::async() will block
// if launched with std::launch::async

void task() {
    std::this_thread::sleep_for(5s);
    std::cout << "Task result: " << 42 << '\n';
}

void func() {
    std::cout << "Calling std::async\n";

    // the task is started in a new thread immediately due to std::launch::async
    std::future fut = std::async(std::launch::async, task);

    std::cout << "std::async is called\n";

    // this future (fut) destructor will block here until task() is done
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 066-choosing_a_thread_object.cpp && ./a.out
int main() {
    /**
     * The output of this program is:
     * ```
     * Calling std::async
     * std::async is called
     * Task result: 42
     * Task started
     * ```
     *
     * Why does "Task result: 42" appear before "Task started"?
     */

    func();
    std::cout << "Task started\n";
}