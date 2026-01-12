/**
 * Thread pool with work stealing
 * It uses the non-blocking operations of the ConcurrentQueue to implement work stealing.
 */

#include "thread_pool.h"

#include <iostream>

using namespace std::literals;

// Protect shared state in random number engine
std::mutex rand_mut;

// Constructor
ThreadPool::ThreadPool() {
    this->thread_count = std::thread::hardware_concurrency() - 1;
    std::cout << "Creating a thread pool with " << this->thread_count << " threads\n";

    // Create a dynamic array of queues
    this->work_queues = std::make_unique<Queue[]>(this->thread_count);

    // Start the threads
    for (int i = 0; i < this->thread_count; ++i) {
        this->threads.push_back(std::thread{&ThreadPool::worker, this, i});
    }
}

// Destructor
ThreadPool::~ThreadPool() {
    std::cout << "Destroying thread pool\n";

    // We cannot send a poison pill to each worker, because the work_queues[i] may be full and
    // try_push() will fail. Even if we find a way to push a poison pill to each queue, the poison
    // pill may be stolen by other threads, which will result to some threads do not receive the
    // poison pill.
    // TODO: Find a way to exit the `this->worker()` function.

    // Wait for the threads to finish
    for (auto &thr : this->threads) {
        thr.join();
    }
}

// Returns a random number between 0 and thread_count-1
int ThreadPool::get_random() {
    // random number engine has a shared state, so we need to protect it with a mutex
    std::lock_guard<std::mutex> lck_guard(rand_mut);
    std::uniform_int_distribution<int> dist(0, this->thread_count - 1);
    return dist(mt);
}

// Entry point function for the threads
void ThreadPool::worker(int idx) {
    while (true) {
        // Number of queues we have checked so far
        int visited = 0;
        Func task;

        // Take a task function off our queue
        int i = idx;

        // Try to find a queue where try_pop() succeeds
        while (!this->work_queues[i].try_pop(task)) {
            // Nothing on this queue
            // Pick another queue at random
            i = get_random();

            // Hot loop avoidance
            // If we have checked "enough" queues, pause for a while
            // then start again with our own queue
            if (++visited == this->thread_count) {
                std::this_thread::sleep_for(10ms);
                visited = 0;
                i = idx;
            }
        }

        // Invoke the task function
        task();
    }
}

// Choose a thread's queue and add a task to it
void ThreadPool::submit(Func func) {
    int i;

    // Try to find a queue where try_push() succeeds
    do {
        // Pick a queue at random
        i = get_random();
    }
    // Until we find one that is not full
    while (!this->work_queues[i].try_push(func));
}
