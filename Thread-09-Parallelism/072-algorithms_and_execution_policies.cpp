#include <algorithm>
#include <exception>
#include <execution>
#include <iostream>
#include <vector>

// g++ -std=c++20 -Wall -Wextra -pedantic 072-algorithms_and_execution_policies.cpp -ltbb && ./a.out
int main() {
    std::vector<int> vec{3, 1, 4, 1, 5, 9};

    /**
     * Algorithms and exceptions in C++14
     * An algorithm may throw an exception for various reasons.	The exception is handled by the
     * programmer. Here, we use a try-catch block to catch and handle the exception.
     */
    try {
        // Predicate throws an exception
        std::sort(vec.begin(), vec.end(), [](int a, int b) {
            throw std::out_of_range("Oops");
            return a > b;
        });
    } catch (std::exception &e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    }
    for (auto v : vec)
        std::cout << v << ", ";

    /**
     * Algorithms and exceptions in C++17
     * With the introduction of execution policies in C++17, algorithms can be executed in multiple
     * threads. Each threadd has its own execution stack. If an exception is thrown in one of the
     * threads, do we want to continue executing the other threads, or do we want to stop all
     * execution?
     * The C++17 standard specifies that if an exception is thrown in any of the threads,
     * `std::terminate()` is called. `std::terminate()` terminates the current thread and all other
     * threads with respect to the algorithm call. Does it include the main thread?
     * Yes, it does. The entire program will be terminated.
     */
    try {
        std::sort(std::execution::seq, vec.begin(), vec.end(), [](int a, int b) {
            throw std::out_of_range("Oops");
            return a < b;
        });
    } catch (std::exception &e) {
        /**
         * This block will not be executed because std::terminate() is called
         *
         * terminate called after throwing an instance of 'std::out_of_range'
         *   what():  Oops
         * Aborted (core dumped)
         */
        std::cout << "Caught exception: " << e.what() << '\n';
    }
}
