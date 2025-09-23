/**
 * std::async launch options
 *  - std::launch::async: always run the task in a new thread. The task is executed as soon as the
 *    thread starts.
 *  - std::launch::deferred: nothing happens until get() is called on the returned future. The task
 *    is then executed ("lazy evaluation").
 *  - default (no option specified): the implementation can choose either of the above options.
 *
 */
#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;

int task() {
    std::cout << "Executing task() in thread with ID: ";
    std::cout << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "Returning from task()\n";
    return 42;
}

void func(const std::string &option = "default"s) {
    std::future<int> result;

    if (option == "async"s)
        result = std::async(std::launch::async, task);
    else if (option == "deferred"s)
        result = std::async(std::launch::deferred, task);
    else
        result = std::async(task);

    std::cout << "Calling async with option \"" << option << "\"\n";
    std::this_thread::sleep_for(2s);
    std::cout << "Calling get()\n";
    std::cout << "Task result: \n";
    std::cout << result.get() << '\n';
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 065-async_launch_options.cpp && ./a.out
int main() {
    std::cout << "In main thread with ID: " << std::this_thread::get_id() << "\n\n";

    func("async");
    std::cout << "---------------------\n";
    func("deferred");
    std::cout << "---------------------\n";
    func("default");
}