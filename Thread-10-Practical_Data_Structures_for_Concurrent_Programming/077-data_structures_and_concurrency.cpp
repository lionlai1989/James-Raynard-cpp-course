// Conflicting operations on STL containers are not safe
// They must be synchronized
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// Shared vector
std::vector<int> vec;

// Mutex to protect std::vector's data
std::mutex mut;

void func1() {
    // Potentially conflicting access - must be protected
    // std::lock_guard<std::mutex> lgd(mut);
    for (int i = 0; i < 100000; ++i)
        vec.push_back(i);
}

void func2() {
    // Potentially conflicting access - must be protected
    // std::lock_guard<std::mutex> lgd(mut);
    for (int i = 100000; i < 200000; ++i)
        vec.push_back(i);
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 077-data_structures_and_concurrency.cpp &&
// ./a.out
int main() {
    std::thread thr1(func1);
    std::thread thr2(func2);
    thr1.join();
    thr2.join();
    std::cout << "shptr data: ";
    for (int i = 0; i < 200000; ++i)
        std::cout << vec[i] << ", ";

    std::cout << "Finished\n";

    /**
     * The code above exhibits problems far more severe than a typical race condition. You might
     * expect the program to merely produce incorrect results (e.g., wrong size), but it will likely
     * crash. This is because concurrent structural modifications to `std::vector` cause memory
     * corruption (Undefined Behavior), not just data inconsistency.
     *
     * Explanation:
     * This leads to Undefined Behavior that often results in a Segmentation Fault.
     * `std::vector` manages a dynamic array internally. When `push_back` is called, it may need to
     * reallocate memory if the current capacity is full.
     *
     * Scenarios leading to crash:
     * 1. Reallocation Interference (Use-After-Free):
     *    Thread A detects insufficient space and starts reallocating (allocating new memory,
     *    copying elements, freeing old memory). concurrently, Thread B might be trying to write
     *    to the *old* memory location which Thread A just freed. This access to freed memory
     *    causes a Segmentation Fault.
     *
     * 2. Double Free:
     *    Both threads might decide to reallocate simultaneously. They both allocate new buffers,
     *    but then both attempt to free the *same* old buffer. Double-freeing memory corrupts
     *    the heap and causes a crash.
     *
     * 3. Invariant Corruption:
     *    The internal pointers (start, finish, end_of_storage) are updated non-atomically.
     *    One thread might increment the size pointer past the allocated capacity without
     *    triggering reallocation because it read an outdated capacity value from the other thread,
     *    leading to writes out of bounds.
     *
     * IMPORTANT LESSON:
     * When the number of iterations is small (e.g., 1000), the program might run without
     * crashing. The crash is more likely to occur with higher workloads (e.g., 100000) that
     * trigger frequent reallocations and increase the probability of race conditions.
     *
     * Just because your program "works" (doesn't crash) does NOT mean it is free from
     * data races or Undefined Behavior. Do not be complacent with code that appears correct
     * during superficial testing. Extensive testing and proper synchronization are mandatory.
     */
}
