/**
 * Deadlock
 * A thread is deadlocked when it is waiting for a resource that is held by another thread, which is
 * also waiting for a resource held by the first thread.
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

/**
 * A simple example of deadlock with two threads.
 * - Thread A locks mutex 1 and waits for mutex 2.
 * - Thread B locks mutex 2 and waits for mutex 1.
 * - Thread A and Thread B are now deadlocked because they are waiting for each other to release the
 *   mutexes.
 */
std::mutex mut1;
std::mutex mut2;
void funcA() {
    std::cout << "Thread A trying to lock mutex 1...\n";
    std::lock_guard<std::mutex> lck_guard1(mut1); // Acquire lock on mut1
    std::cout << "Thread A has locked mutex 1\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread A trying to lock mutex 2...\n";
    std::lock_guard<std::mutex> lck_guard2(mut2); // Wait for lock on mut2
    std::cout << "Thread A has locked mutex 2\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread A releases all its locks\n";
}
void funcB() {
    std::cout << "Thread B trying to lock mutex 2...\n";
    std::lock_guard<std::mutex> lck_guard1(mut2); // Acquire lock on mut2
    std::cout << "Thread B has locked mutex 2\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread B trying to lock mutex 1...\n";
    std::lock_guard<std::mutex> lck_guard2(mut1); // Wait for lock on mut1
    std::cout << "Thread B has locked mutex 1\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread B releases all its locks\n";
}

/**
 * A simple way to avoid deadlock is to ensure all threads (can be more than 2 threads) acquire the
 * mutexes in the same order.
 */
std::mutex mut3;
std::mutex mut4;
void funcA2() {
    std::cout << "Thread A2 trying to lock mutex 3...\n";
    std::lock_guard<std::mutex> lck_guard1(mut3); // Acquire lock on mut3
    std::cout << "Thread A2 has locked mutex 3\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread A2 trying to lock mutex 4...\n";
    std::lock_guard<std::mutex> lck_guard2(mut4); // Wait for lock on mut4
    std::cout << "Thread A2 has locked mutex 4\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread A2 releases all its locks\n";
}
void funcB2() {
    std::cout << "Thread B2 trying to lock mutex 3...\n";
    std::lock_guard<std::mutex> lck_guard1(mut3); // Acquire lock on mut3
    std::cout << "Thread B2 has locked mutex 3\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread B2 trying to lock mutex 4...\n";
    std::lock_guard<std::mutex> lck_guard2(mut4); // Wait for lock on mut4
    std::cout << "Thread B2 has locked mutex 4\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread B2 releases all its locks\n";
}
void funcC2() {
    std::cout << "Thread C2 trying to lock mutex 3...\n";
    std::lock_guard<std::mutex> lck_guard1(mut3); // Acquire lock on mut3
    std::cout << "Thread C2 has locked mutex 3\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread C2 trying to lock mutex 4...\n";
    std::lock_guard<std::mutex> lck_guard2(mut4); // Wait for lock on mut4
    std::cout << "Thread C2 has locked mutex 4\n";
    std::this_thread::sleep_for(50ms); // Do some work
    std::cout << "Thread C2 releases all its locks\n";
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 039-deadlock.cpp && ./a.out
int main() {
    // This will cause a deadlock
    // std::thread thrA(funcA);
    // std::thread thrB(funcB);
    // thrA.join();
    // thrB.join();

    // This will avoid deadlock by making all threads lock the mutexes in the same order
    std::thread thrA2(funcA2);
    std::thread thrB2(funcB2);
    std::thread thrC2(funcC2);
    thrA2.join();
    thrB2.join();
    thrC2.join();

    return 0;
}
