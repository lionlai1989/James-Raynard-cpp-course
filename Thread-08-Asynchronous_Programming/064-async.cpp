/**
 * std::async()
 *
 * The std::async() function is defined in <future> header and is a higher-level abstraction than
 * std::thread.
 *
 * We can execute a task with std::async() which runs in the background and this allows us to do
 * other work while the task is running. Alternatively, it can run synchronously in the same thread.
 *
 * The task may throw an exception. The exception is stored in the std::future object. The exception
 * will be re-thrown when get() is called.
 */

#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <thread>

// Task function
void hello() { std::cout << "Hello, Async!\n"; }

// Task which returns a value
// How to get a result from a task executed by std::async()
unsigned long long fibonacci(unsigned long long n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// A task started by std::async() throws an exception
int produce() {
    int x = 42;

    using namespace std::literals;
    std::this_thread::sleep_for(2s);

    // Some code which may throw an exception
    if (1) {
        throw std::out_of_range("Oops");
    }

    std::cout << "Produce returning " << x << '\n';
    return x;
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 064-async.cpp && ./a.out
int main() {
    // Call std::async() to perform the task
    std::async(hello);

    std::cout << "------------------------\n";

    std::cout << "Calling fibonacci(44)\n";

    // Call async() and store the returned future
    auto result = std::async(fibonacci, 44);

    std::cout << "Doing other work...\n";

    using namespace std::literals;
    while (result.wait_for(1s) != std::future_status::ready) {
        std::cout << "Waiting for the result...\n";
    }

    // Call get() when we are ready
    std::cout << result.get() << std::endl;

    std::cout << "------------------------\n";

    // Call async() and store the returned future
    auto result2 = std::async(produce);

    // Get the result - may throw an exception
    std::cout << "Future calling get()...\n";
    try {
        int x = result2.get(); // Get the result
        std::cout << "Future returns from calling get()\n";
        std::cout << "The answer is " << x << '\n';
    } catch (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}
