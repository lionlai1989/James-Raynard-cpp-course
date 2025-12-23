/**
 * Threads and std::shared_ptr
 *
 * When using std::shared_ptr in a multi-threaded environment, there are two distinct concerns:
 * 1. Concurrent modification of the pointed-to data.
 * 2. Concurrent modification of the reference counter (control block).
 *
 * Reference Counting:
 * The reference counter in std::shared_ptr is thread-safe (atomic). Operations that only affect
 * the reference count (like copying or destroying a shared_ptr) are safe to perform concurrently
 * without extra synchronization.
 *
 * Managed Data:
 * Access to the pointed-to data is NOT thread-safe by default. If multiple threads access the same
 * object and at least one modifies it, the programmer must provide synchronization (e.g., using
 * mutexes) to prevent data races.
 */

#include <iostream> // cout, endl
#include <memory>   // shared_ptr, make_shared
#include <mutex>    // mutex, lock_guard
#include <thread>   // thread

// std::shared_ptr has an "atomic" reference counter
std::shared_ptr<int> shptr = std::make_shared<int>(42);
void func1() {
    // Increments shared_p's reference counter - safe
    std::shared_ptr<int> shp1 = shptr;
}
void func2() {
    // Increments shared_p's reference counter - safe
    std::shared_ptr<int> shp2 = shptr;
}

////////////////////////////////////////////////////////////

std::shared_ptr<int> shptr2 = std::make_shared<int>(42);
// Mutex to protect std::shared_ptr's data
std::mutex mut;
void func3() {
    // Potentially conflicting access - must be protected
    std::lock_guard<std::mutex> lgd(mut);
    *shptr2 = 5;
}
void func4() {
    // Potentially conflicting access - must be protected
    std::lock_guard<std::mutex> lgd(mut);
    *shptr2 = 7;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 078-shared_pointer.cpp && ./a.out
int main() {
    // Pass a pointer as the constructor argument
    std::shared_ptr<int> ptr1(new int(42));

    // Calling std::make_shared() is better
    auto ptr2 = std::make_shared<int>(42);

    // Can be dereferenced
    std::cout << *ptr1 << '\n';

    // Pointer arithmetic is not supported
    // ++ptr1;

    // Assignment, copying and moving are allowed
    ptr1 = ptr2;
    std::shared_ptr<int> ptr3(ptr2);
    std::shared_ptr<int> ptr4(std::move(ptr2));

    // Releases the allocated memory
    ptr1 = nullptr;

    std::cout << "--------------------------------\n";

    /**
     * Operations which only affect the reference counter are safe and do not need to be protected
     * by a mutex.
     */
    std::thread thr1(func1);
    std::thread thr2(func2);
    thr1.join();
    thr2.join();

    std::cout << "--------------------------------\n";

    /**
     * Operations which affect the pointed-to data are not safe. They must be protected by a mutex.
     */
    std::cout << "shptr data: " << *shptr2 << '\n';
    std::thread thr3(func3);
    std::thread thr4(func4);
    thr3.join();
    thr4.join();
    std::cout << "shptr data: " << *shptr2 << '\n';
}
