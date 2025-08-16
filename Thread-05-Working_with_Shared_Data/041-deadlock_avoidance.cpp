/**
 * Deadlock Avoidance Guidelines
 * - Avoid waiting for a thread while holding a lock
 *   - The other thread may need the lock to proceed
 * - Try to avoid waiting for other threads
 *   - The other thread may be waiting for your thread
 * - Try to avoid nested locks
 *   - If your thread already holds a lock, do not aqquire another lock
 *   - If you need multiple locks, acquire them in a single operation
 * - Avoid calling functions within a critical section
 *   - Unless you are certain the function does not try to lock any mutexes
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

/**
 * std::scoped_lock (C++17 or later)
 * It is similar to std::lock_guard except it can lock more than one mutex at the same time.
 * The mutexes are locked in the order given in the constructor call.
 * In the destructor, the mutexes are unlocked in the reverse order.
 *
 * Caveat of std::scoped_lock
 * std::scoped_lock can be used with a single mutex, `std::scoped_lock scoped_lck(mtx);`.
 * It is easy to accidentally omit the argument, `std::scoped_lock scoped_lck;`. This will compile
 * and run, but NOT actually perform any locking.
 */
std::mutex mut1;
std::mutex mut2;
void funcA() {
    std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
    std::scoped_lock scoped_lck(mut1, mut2);
    std::cout << "Thread A has locked mutexes 1 and 2\n";
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread A releasing mutexes 1 and 2...\n";
}
void funcB() {
    std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
    std::scoped_lock scoped_lck(mut2, mut1);
    std::cout << "Thread B has locked mutexes 2 and 1\n";
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

/**
 * std::unique_lock can "adopt" the locks.
 */
std::mutex mut3;
std::mutex mut4;
void funcA2() {
    std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
    std::lock(mut3, mut4); // Lock both mutexes
    std::cout << "Thread A has locked mutexes 1 and 2\n";

    // Adopt the locks. uniq_lk1 and uniq_lk2 now own mut3 and mut4, respectively.
    std::unique_lock<std::mutex> uniq_lk1(mut3, std::adopt_lock); // Associate each mutex
    std::unique_lock<std::mutex> uniq_lk2(mut4, std::adopt_lock); // with a unique_lock
    std::cout << "Thread A has adopted the locks\n";

    std::this_thread::sleep_for(50ms);
    std::cout << "Thread A releasing mutexes 1 and 2...\n";
}
void funcB2() {
    std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
    lock(mut4, mut3); // Lock both mutexes
    std::cout << "Thread B has locked mutexes 2 and 1\n";

    // Adopt the locks
    std::unique_lock<std::mutex> uniq_lk2(mut4, std::adopt_lock); // with a unique_lock
    std::unique_lock<std::mutex> uniq_lk1(mut3, std::adopt_lock); // Associate each mutex
    std::cout << "Thread B has adopted the locks\n";

    std::this_thread::sleep_for(50ms);
    std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

/**
 * Deferring Locks
 * Alternatively, we can "defer" the locking.
 */
std::mutex mut5;
std::mutex mut6;
void funcA3() {
    std::unique_lock<std::mutex> uniq_lk1(mut5, std::defer_lock); // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk2(mut6, std::defer_lock); // ...but don’t lock it yet

    std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
    std::lock(uniq_lk1, uniq_lk2); // Now lock both of them
    std::cout << "Thread A has locked mutexes 1 and 2\n";
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread A releasing mutexes 1 and 2...\n";
}
void funcB3() {
    std::unique_lock<std::mutex> uniq_lk2(mut6, std::defer_lock); // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk1(mut5, std::defer_lock); // ...but don’t lock it yet

    std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
    std::lock(uniq_lk2, uniq_lk1); // Now lock both of them
    std::cout << "Thread B has locked mutexes 2 and 1\n";
    std::this_thread::sleep_for(50ms);
    std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

/**
 * std::try_lock
 * The `std::lock` function is a blocking call, meaning it will wait until all mutexes are locked.
 * If it's not possible to lock all mutexes, it will block indefinitely. This is not always
 * desirable.
 * std::try_lock is non-blocking and will attempt to lock the mutexes, returning immediately.
 * - On success, it returns -1.
 * - On failure, it returns the index of the mutex that could not be locked.
 *
 */
std::mutex mut7;
std::mutex mut8;
void funcA4() {
    std::unique_lock<std::mutex> uniq_lk1(mut7, std::defer_lock); // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk2(mut8, std::defer_lock); // ...but don’t lock it yet

    std::cout << "Thread A trying to lock mutexes 1 and 2...\n";

    // Now lock both of them
    auto idx = std::try_lock(uniq_lk1, uniq_lk2);
    if (idx != -1) {
        std::cout << "try_lock failed on mutex with index " << idx << '\n';
    } else {
        std::cout << "Thread A has locked mutexes 1 and 2\n";
        std::this_thread::sleep_for(50ms);
        std::cout << "Thread A releasing mutexes 1 and 2...\n";
    }
}
void funcB4() {
    std::unique_lock<std::mutex> uniq_lk2(mut8, std::defer_lock); // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk1(mut7, std::defer_lock); // ...but don’t lock it yet

    std::cout << "Thread B trying to lock mutexes 2 and 1...\n";

    // Now lock both of them
    auto idx = std::try_lock(uniq_lk2, uniq_lk1);
    if (idx != -1) {
        std::cout << "try_lock failed on mutex with index " << idx << '\n';
    } else {
        std::cout << "Thread B has locked mutexes 2 and 1\n";
        std::this_thread::sleep_for(50ms);
        std::cout << "Thread B releasing mutexes 2 and 1...\n";
    }
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 041-deadlock_avoidance.cpp && ./a.out
int main() {
    std::thread thrA(funcA);
    std::thread thrB(funcB);
    thrA.join();
    thrB.join();

    std::cout << "--------------------------------\n";

    std::thread thrA2(funcA2);
    std::thread thrB2(funcB2);
    thrA2.join();
    thrB2.join();

    std::cout << "--------------------------------\n";

    std::thread thrA3(funcA3);
    std::thread thrB3(funcB3);
    thrA3.join();
    thrB3.join();

    std::cout << "--------------------------------\n";

    std::thread thrA4(funcA4);
    std::thread thrB4(funcB4);
    thrA4.join();
    thrB4.join();

    return 0;
}