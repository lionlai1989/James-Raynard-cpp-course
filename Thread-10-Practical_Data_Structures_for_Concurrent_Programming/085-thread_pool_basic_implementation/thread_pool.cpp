/**
 * Thread Creation Overhead
 * Creating a thread requires a lot of work:
 * - Create an execution stack for the thread
 * - Call a system API
 * - The operaing system creates internal data to manage the thread
 * - The scheduler executes the thread
 * - A context switch occurs to run the thread
 *
 * Creating a new thread can take 10,000 times longer than calling a function directly
 * Is there any way we can "recycle" threads so that we don't have to create a new thread for each
 * task?
 *
 * Thread Pool Motivation
 * We want to make full use of all our processor cores. Every core should be running one of our
 * threads. This is difficult to achieve with `std::async` because we need to keep track of all the
 * threads we create. An analogy of the thread pool is typing pool.
 *
 * Advantages of Thread Pool:
 * - The thread pool will automatically scale to the number of cores available on the system.
 * - Threads are recycled and always busy.
 * - Works best with short, simple tasks where the tasks are independent of each other. And the time
 *   taken to create a thread consumes a significant amount of time.
 */

#include "thread_pool.h"
#include <iostream>

ThreadPool::ThreadPool() {
    // -1 to leave one core for the main thread or the OS
    thread_count = std::thread::hardware_concurrency() - 1;
    std::cout << "Creating a thread pool with " << thread_count << " threads\n";

    // Start the threads
    for (int i = 0; i < thread_count; ++i)
        // Create a thread that executes the 'worker' member function.
        // We pass '&ThreadPool::worker' as the function to run.
        // We pass 'this' as the object instance because 'worker' is a non-static member function.
        this->threads.push_back(std::thread{&ThreadPool::worker, this});
}

ThreadPool::~ThreadPool() {
    stop = true;

    // Push empty tasks to wake up the threads.
    // Threads are blocked in the work_queue.pop() function.
    // Pushing a task will wake up a thread, which will then check the stop flag.
    for (int i = 0; i < thread_count; ++i) {
        work_queue.push([] {});
    }

    // Wait for the threads to finish
    for (auto &thr : this->threads) {
        thr.join();
    }
}

// Entry point function for the threads
void ThreadPool::worker() {
    while (!stop) {
        Func task;

        // Take a task function off the queue
        this->work_queue.pop(task);

        // Invoke it
        task();
    }
}

// Add a task to the queue
void ThreadPool::submit(Func func) { this->work_queue.push(func); }
