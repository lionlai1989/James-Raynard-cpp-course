/**
 * Thread pool with work stealing
 */

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

#include "concurrent_queue.h"

// Type aliases to simplify the code
// All the task functions will have this type
using Func = std::function<void()>;

// Alias for concurrent queue type
using Queue = ConcurrentQueue<Func>;

class ThreadPool {
    // Random number engine
    std::mt19937 mt;

    // Each thread has its own queue of task functions
    std::unique_ptr<Queue[]> work_queues;

    // Vector of thread objects which make up the pool
    std::vector<std::thread> threads;

    // Entry point function for the threads
    void worker(int idx);

    // Returns a random number between 0 and thread_count
    int get_random();

    // The number of threads in the pool
    int thread_count;

    // Protect shared state in random number engine
    std::mutex rand_mut;

  public:
    ThreadPool();
    ~ThreadPool();

    // Add a task to the queue
    void submit(Func func);
};

#endif // THREAD_POOL_H
