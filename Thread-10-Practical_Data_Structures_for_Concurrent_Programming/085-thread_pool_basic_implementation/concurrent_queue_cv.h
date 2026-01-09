// Simple concurrent queue implementation
// with condition variable
// pop() blocks when the queue is empty
// push() polls when the queue is full
#ifndef CONCURRENT_QUEUE_CV_H
#define CONCURRENT_QUEUE_CV_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

using namespace std::literals;

// Concurrent queue class
template <class T> class ConcurrentQueueCondVar {
  private:
    // Data members
    std::mutex mut;
    std::queue<T> que;
    std::condition_variable cv_not_empty;
    std::condition_variable cv_not_full;
    size_t max{50};

  public:
    // Constructors
    ConcurrentQueueCondVar() = default;
    ConcurrentQueueCondVar(size_t max) : max(max) {};

    // Deleted special member functions
    ConcurrentQueueCondVar(const ConcurrentQueueCondVar &) = delete;
    ConcurrentQueueCondVar &operator=(const ConcurrentQueueCondVar &) = delete;
    ConcurrentQueueCondVar(ConcurrentQueueCondVar &&) = delete;
    ConcurrentQueueCondVar &operator=(ConcurrentQueueCondVar &&) = delete;

    // Member functions
    // Push an element onto the queue
    void push(const T &value) {
        std::unique_lock<std::mutex> uniq_lck(mut);

        // Block when the queue is full
        cv_not_full.wait(uniq_lck, [this] { return que.size() < max; });

        // Perform the push and notify
        que.push(value);
        cv_not_empty.notify_one();
    }

    // Pop an element from the queue
    void pop(T &value) {
        std::unique_lock<std::mutex> uniq_lck(mut);

        // Block when the queue is empty
        cv_not_empty.wait(uniq_lck, [this] { return !que.empty(); });

        // Perform the pop
        value = que.front();
        que.pop();

        // Notify producer that space is available
        cv_not_full.notify_one();
    }
};

#endif // CONCURRENT_QUEUE_CV_H
