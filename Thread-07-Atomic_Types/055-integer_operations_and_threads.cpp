/**
 * Integer operations and threads
 * Integer operations are usually a single instruction. That is a thread cannot be interrupted while
 * performing integer operations.
 *
 * Do we still need to lock a shared integer? Yes.
 *
 * The ++ operation is a single instruction, but ++counter involves three operations:
 *  - Pre-fetch the value of counter from memory into a register
 *  - Increment the value in the register
 *  - Publish the new value of counter
 * Thus, a mutex is needed to protect the entire operations.
 *
 * Another way to handle this is to use atomic types, see 056-atomic_types.cpp.
 * Basically, atomic types tell the compiler to generate special instructions for operations
 *  - Disable pre-fetching for "counter"
 *  - Flush the store buffer immediately after doing the increment
 * This results to only one thread can access "counter" at a time
 */

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/**
 * A shared variable is modified by multiple threads without a mutex
 * Integer operations take a single instruction
 * Is there a data race?
 */
int counter = 0;
void task() {
    for (int i = 0; i < 100'000; ++i) {
        ++counter;
    }
}

////////////////////////////////////////////////////////////

/**
 * A shared variable is modified by multiple threads with a mutex.
 */
std::mutex mut2;
int counter2 = 0;
void task2() {
    for (int i = 0; i < 100'000; ++i) {
        std::lock_guard<std::mutex> lck_guard(mut2);
        ++counter2;
    }
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 055-integer_operations_and_threads.cpp && ./a.out
int main() {
    /**
     * What should the `counter` variable be at the end of the program?
     * Is it 10 * 100'000 = 1'000'000?
     * Or is it less than 1'000'000?
     */
    std::vector<std::thread> tasks;
    for (int i = 0; i < 10; ++i)
        tasks.push_back(std::thread(task));
    for (auto &thr : tasks)
        thr.join();
    std::cout << counter << '\n';

    std::cout << "--------------------------------\n";

    /**
     * counter2 is 1'000'000 at the end of the program
     */
    std::vector<std::thread> tasks2;
    for (int i = 0; i < 10; ++i)
        tasks2.push_back(std::thread(task2));
    for (auto &thr : tasks2)
        thr.join();
    std::cout << counter2 << '\n';
}
