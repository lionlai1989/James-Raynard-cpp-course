/**
 * Thread pool with multiple queues
 */

#include "thread_pool.h"

#include <iostream>
#include <thread>
#include <vector>

using namespace std::literals;

// Constructor
ThreadPool::ThreadPool() {
    this->thread_count = std::thread::hardware_concurrency() - 1;
    std::cout << "Creating a thread pool with " << this->thread_count << " threads\n";

    // Create a dynamic array of queues with size of thread_count
    this->work_queues = std::make_unique<Queue[]>(this->thread_count);

    // Start the threads
    for (int i = 0; i < this->thread_count; ++i) {
        this->threads.push_back(std::thread{&ThreadPool::worker, this, i});
    }
}

// Destructor
ThreadPool::~ThreadPool() {
    // Send a poison pill to each worker
    for (int i = 0; i < this->thread_count; ++i) {
        this->work_queues[i].push(Func{});
    }

    // Wait for the threads to finish
    for (auto &thr : this->threads) {
        thr.join();
    }
}

// Entry point function for the threads
void ThreadPool::worker(int idx) {
    while (true) {
        Func task;

        // Take a task function off the queue
        this->work_queues[idx].pop(task);

        if (!task)
            return;

        // Invoke it
        task();
    }
}

// Add a task to the current thread's queue
void ThreadPool::submit(Func func) {
    // Note that submit() is not a thread-safe operation because it modifies the shared state, pos.
    // If multiple threads call submit() at the same time, the result is undefined.
    // This is why we need to use a mutex to protect the shared state.
    // But in our case, we don't need to use a mutex because we only have the main thread calling
    // submit().

    this->work_queues[this->pos].push(func);

    // Advance to the next thread's queue
    this->pos = (this->pos + 1) % this->thread_count;
}
