/**
 * Thread pool with single queue
 */

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "concurrent_queue_cv.h"

#include <functional>
#include <thread>
#include <vector>

// Type alias to simplify the code
// All the task functions will have this type. No parameters and no return value.
using Func = std::function<void()>;

class ThreadPool {
  private:
    // A concurrent queue to store incoming tasks as callable objects
    ConcurrentQueueCondVar<Func> work_queue;

    // Vector of thread objects which make up the pool
    std::vector<std::thread> threads;

    // Entry point function for the threads
    void worker();

    // The number of threads in the pool
    int thread_count;

  public:
    ThreadPool();
    ~ThreadPool();

    // Add a task to the queue
    void submit(Func func);
};

#endif // THREAD_POOL_H
