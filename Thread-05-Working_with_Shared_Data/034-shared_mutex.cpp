/**
 * std::shared_mutex (Read-Write Lock)
 * A shared mutex is a mutex that can be locked in two different ways:
 * - Exclusive lock: (std::lock_guard<std::shared_mutex>)
 *   - Only one thread can lock the mutex exclusively.
 *   - Only one thread can enter the critical section at a time.
 * - Shared lock: (std::shared_lock<std::shared_mutex>)
 *   - Other threads may acquire a shared lock.
 *   - They can execute critical sections concurrently.
 *
 */
#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex shmtx;

// Shared variable
int x = 0;

void writer() {
    // Only this thread can execute the critical section. Other threads must wait until this thread
    // releases the lock. It can only acquire the lock when the shmtx is unlocked.
    std::lock_guard<std::shared_mutex> lck_guard(shmtx);

    // Start of critical section
    ++x;
    // End of critical section
}

void reader() {
    // A thread which has a shared lock can enter a critical section. If another thread has an
    // exclusive lock, this thread must wait until the exclusive lock is released.
    std::shared_lock<std::shared_mutex> lck_guard(shmtx);

    // Start of critical section
    using namespace std::literals;
    std::this_thread::sleep_for(100ms);
    // End of critical section
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 034-shared_mutex.cpp && ./a.out
int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 20; ++i)
        threads.push_back(std::thread(reader));

    threads.push_back(std::thread(writer));
    threads.push_back(std::thread(writer));

    for (int i = 0; i < 20; ++i)
        threads.push_back(std::thread(reader));

    // There are 40 readers and 2 writers. Each reader takes 100ms to read the shared resource.
    // Therefore, this program should take 100ms * 40 = 4000ms = 4s to finish. Or does it?
    // It takes roughly 100ms to finish. Why?
    // The readers are reading the shared resource concurrently.
    for (auto &thr : threads)
        thr.join();
}