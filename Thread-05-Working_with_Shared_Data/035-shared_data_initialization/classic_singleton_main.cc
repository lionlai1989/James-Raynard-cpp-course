/**
 * Shared data can be various forms:
 * - Global variable:
 *   - accessible to all code in the program.
 * - Static variable at namespace scope:
 *   - accessible to all code in the translation unit
 * - Class member which is declared static:
 *   - potentially accessible to code which calls its member functions.
 *   - if public, accessible to all code.
 * - Local variable which is declared static:
 *   - accessible to all code which calls that function.
 *
 * For the first three cases, global variable, static variable at namespace scope, and static data
 * member of class, they are all initialized when the program starts. At that point, only one thread
 * is running so there can not be data race happening.
 *
 * For the static local variable, it has some implications. It is initialized after the program
 * started. When the declaration is reached,
 *
 * void func() {
 *     ...
 *     // static local variable
 *     static std::string str("abc");
 * }
 *
 * In this case, two or more threads may call the constructor concurrently. Is there a data race?
 * Yes.
 *
 */

#include "classic_singleton.h"
#include <thread>
#include <vector>

// Define the one and only static data member instance "single".
// Compilation error without this line.
Singleton *Singleton::single = nullptr;

void task() {
    // Only one constructor shall be called. But it has been called multiple times due to data race.
    Singleton *single = Singleton::get_Singleton();

    // The returned Singleton object "single" should be the same for all threads. But it's not due
    // to data race.
    std::cout << single << std::endl;
}

// g++ -std=c++11 -Wall classic_singleton_main.cc classic_singleton.cc && ./a.out
int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i)
        threads.push_back(std::thread(task));

    for (auto &thr : threads)
        thr.join();

    // The output shows constructor is called multiple times.
    // Initializing Singleton
    // 0x709068000b70
    // Initializing Singleton
    // Initializing Singleton0x709060000b70
    // Initializing Singleton
    // 0x709044000b70

    // 0x70905c000b70
    // 0x70905c000b70
    // Initializing Singleton
    // Initializing Singleton
    // 0x709058000b70Initializing Singleton

    // 0x709050000b70
    // 0x709048000b70
    // Initializing Singleton
    // 0x70903c000b70
    // Initializing Singleton
    // 0x709034000b70
}
