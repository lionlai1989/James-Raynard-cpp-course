/**
 * Livelock
 * A program cannot proceed because threads keep changing state in response to each other without
 * making progress.
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std::literals;

/**
 * Livelock example:
 * Livelock caused by poorly implemented deadlock avoidance. If a thread cannot get a lock, sleep
 * and try again. However, all the threads wake up at the same time
 */
std::mutex mut1, mut2;
void funcA() {
    std::this_thread::sleep_for(10ms);
    bool locked = false;
    while (!locked) {
        std::lock_guard<std::mutex> lck_guard(mut1); // Lock mut1
        std::cout << "After you, Claude!\n";
        std::this_thread::sleep_for(2s);
        locked = mut2.try_lock(); // Try to lock mut2
    }
    if (locked)
        std::cout << "ThreadA has locked both mutexes\n";
}
void funcB() {
    bool locked = false;
    while (!locked) {
        std::lock_guard<std::mutex> lk(mut2); // Lock mut2
        std::cout << "After you, Cecil!\n";
        std::this_thread::sleep_for(2s);
        locked = mut1.try_lock(); // Try to lock mut1
    }
    if (locked)
        std::cout << "ThreadB has locked both mutexes\n";
}

/**
 * Livelock Avoidance
 * std::shared_lock and std::lock() avoid deadlock.
 * When locking multiple mutexes. They also avoid livelock.
 */
std::mutex mut3, mut4;
void funcA2() {
    std::this_thread::sleep_for(10ms);

    std::cout << "After you, Claude!" << std::endl;
    std::scoped_lock scoped_lck(mut3, mut4); // Lock both mutexes
    std::this_thread::sleep_for(2s);
    std::cout << "Thread A has locked both mutexes\n";
}
void funcB2() {
    std::cout << "After you, Cecil!\n";
    std::scoped_lock scoped_lck(mut4, mut3); // Lock mutexes
    std::this_thread::sleep_for(2s);
    std::cout << "Thread B has locked both mutexes\n";
}

// g++ -std=c++20 -Wall -Wextra -pthread 043-livelock.cpp && ./a.out
int main() {
    // Livelock example: it runs indefinitely
    std::thread thrA(funcA);
    std::this_thread::sleep_for(10ms);
    std::thread thrB(funcB);
    thrA.join();
    thrB.join();

    std::cout << "--------------------------------\n";

    std::thread thrA2(funcA2);
    std::this_thread::sleep_for(10ms);
    std::thread thrB2(funcB2);
    thrA2.join();
    thrB2.join();

    return 0;
}