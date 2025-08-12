/**
 * Thread-local Variables
 *
 * A variable declared with the `thread_local` specifier
 * has a **separate instance in each thread**.
 * In contrast, a non-`thread_local` static or global variable
 * has a **single shared instance** across all threads.
 *
 * You can declare thread-local variables in these scopes:
 *  - Namespace scope (globals)
 *  - Static data members of a class
 *  - Local variables inside a function
 *
 * Example:
 *   // Each thread gets its own `counter`
 *   thread_local int counter = 0;
 */

#include <iostream>
#include <random>
#include <thread>

/**
 * Thread-local random number engine
 * Ensures that each thread generates the same sequence, which is useful for testing.
 * But why not use global variables or just send it as an argument? Let's find out.
 */
thread_local std::mt19937 mt;

void func() {
    std::uniform_real_distribution<double> dist(0, 1); // Doubles in the range 0 to 1

    for (int i = 0; i < 10; ++i) // Generate 10 random numbers
        std::cout << dist(mt) << ", ";
}

////////////////////////////////////////////////////////////

// global variable. There is only one global_mt object in the entire program.
std::mt19937 global_mt;

void func2() {
    std::uniform_real_distribution<double> dist(0, 1); // Doubles in the range 0 to 1

    for (int i = 0; i < 10; ++i) // Generate 10 random numbers
        std::cout << dist(global_mt) << ", ";
}

////////////////////////////////////////////////////////////

// Pass by value (copy). Is std::mt19937 copyable?
void func3(std::mt19937 local_mt) {
    std::uniform_real_distribution<double> dist(0, 1); // Doubles in the range 0 to 1

    for (int i = 0; i < 10; ++i) // Generate 10 random numbers
        std::cout << dist(local_mt) << ", ";
}

////////////////////////////////////////////////////////////

// Pass by reference
void func4(std::mt19937 &ref_mt) {
    std::uniform_real_distribution<double> dist(0, 1); // Doubles in the range 0 to 1

    for (int i = 0; i < 10; ++i) // Generate 10 random numbers
        std::cout << dist(ref_mt) << ", ";
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 036-thread_local_variables.cpp && ./a.out
int main() {
    std::cout << "Thread 1's random values:\n";
    std::thread thr1(func);
    thr1.join();
    std::cout << "\nThread 2's random values:\n";
    std::thread thr2(func);
    thr2.join();

    std::cout << "\n--------------------------------\n" << std::endl;

    std::cout << "Thread 3's random values:\n";
    std::thread thr3(func2);
    thr3.join();
    std::cout << "\nThread 4's random values:\n";
    std::thread thr4(func2);
    thr4.join();

    std::cout << "\n--------------------------------\n" << std::endl;

    std::mt19937 local_mt;
    std::cout << "Thread 5's random values:\n";
    std::thread thr5(func3, local_mt);
    thr5.join();
    std::cout << "\nThread 6's random values:\n";
    std::thread thr6(func3, local_mt);
    thr6.join();

    std::cout << "\n--------------------------------\n" << std::endl;

    std::mt19937 ref_mt;
    std::cout << "Thread 7's random values:\n";
    std::thread thr7(func4, std::ref(ref_mt));
    thr7.join();
    std::cout << "\nThread 8's random values:\n";
    std::thread thr8(func4, std::ref(ref_mt));
    thr8.join();

    std::cout << '\n';
}
