/**
 * Atomic Types
 *
 * All operations on the variable will be atomic
 * C++11 defines an atomic type template std::atomic<T>. Note that the object must be initialized.
 * ```
 *     std::atomic<int> counter{0};
 * ```
 *
 * The parameter T must be a "trivially copyable" type.
 *  - Scalar types (integral types, floating point types, pointers)
 *  - Classes where all the copy and move constructors are trivial
 * Normally, only scalar types and pointers are used.
 * For more complex types, locks may be silently added. Locking a mutex takes longer. Thus, use
 * pointers pointing to complex types instead of complex types directly.
 *
 * Note that atomic types do not support the "." or "->" operators. We must copy to a non-atomic
 * pointer before using it:
 * ```
 *     struct MyClass {
 *         void do_something() {
 *             std::cout << "Doing something\n";
 *         }
 *     };
 *     std::atomic<MyClass*> atomic_ptr{new MyClass()}; // Create an atomic pointer to MyClass
 *     MyClass* ptr = atomic_ptr.load(); // load into a raw pointer first
 *     ptr->do_something();
 *     delete atomic_ptr.load(); // Clean up (since we used new)
 * ```
 */

#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

/**
 * A shared variable is modified by multiple threads
 * Use an "atomic" variable to prevent a data race
 */
std::atomic<int> counter = 0;
void task() {
    for (int i = 0; i < 100'000; ++i)
        ++counter;
}

////////////////////////////////////////////////////////////

/**
 * A shared variable is modified by multiple threads.
 * Using a "volatile" variable does not prevent a data race.
 * "volatile" prevents some compiler optimizations. It's typically used when accessing hardware.
 */
volatile int counter2 = 0;
void task2() {
    for (int i = 0; i < 100'000; ++i)
        ++counter2;
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 056-atomic_types.cpp && ./a.out
int main() {
    std::vector<std::thread> tasks;
    for (int i = 0; i < 10; ++i)
        tasks.push_back(std::thread(task));
    for (auto &thr : tasks)
        thr.join();
    std::cout << counter << '\n';

    std::cout << "--------------------------------\n";

    std::vector<std::thread> tasks2;
    for (int i = 0; i < 10; ++i)
        tasks2.push_back(std::thread(task2));
    for (auto &thr : tasks2)
        thr.join();
    std::cout << counter2 << '\n';
}
