// Thread pool with multiple queues
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <memory>
#include <thread>

#include "concurrent_queue.h"

// Type aliases to simplify the code
// All the task functions will have this type
using Func = std::function<void()>;

// Alias for concurrent queue type
using Queue = ConcurrentQueue<Func>;

class ThreadPool {
  private:
    // Each thread has its own queue of task functions
    std::unique_ptr<Queue[]> work_queues;

    // Vector of thread objects which make up the pool
    std::vector<std::thread> threads;

    // Entry point function for the threads
    void worker(int idx);

    // The number of threads in the pool
    int thread_count;

    // Index into the vector of queues
    int pos{0};

  public:
    ThreadPool();
    ~ThreadPool();

    // Add a task to the queue
    void submit(Func func);
};

#endif // THREAD_POOL_H
