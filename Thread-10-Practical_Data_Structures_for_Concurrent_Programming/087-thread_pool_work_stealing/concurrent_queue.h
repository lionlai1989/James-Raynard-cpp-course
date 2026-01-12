/**
 * Simple concurrent queue implementation with two condition variables
 */

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

using namespace std::literals;

template <class T> class ConcurrentQueue {
  private:
    std::mutex mut;
    std::queue<T> que;

    // Two condition variables must be used. Only one is not enough.
    std::condition_variable cv_not_empty;
    std::condition_variable cv_not_full;

    // Maximum number of elements in the queue
    std::size_t max{50};

  public:
    ConcurrentQueue() = default;
    ConcurrentQueue(std::size_t max) : max(max) {};

    void push(T value) {
        std::unique_lock<std::mutex> uniq_lck(mut);

        cv_not_full.wait(uniq_lck, [this] { return que.size() < max; });

        que.push(value);
        cv_not_empty.notify_one();
    }

    void pop(T &value) {
        std::unique_lock<std::mutex> uniq_lck(mut);

        cv_not_empty.wait(uniq_lck, [this] { return !que.empty(); });

        value = que.front();
        que.pop();
        cv_not_full.notify_one();
    }
};

#endif // CONCURRENT_QUEUE_H
