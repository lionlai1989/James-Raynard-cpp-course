// Simple concurrent queue implementation
// pop() busy waits when the queue is empty
#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

using namespace std::literals;

template <class T> class ConcurrentQueue {
    std::mutex mut;
    std::queue<T> que;
    std::condition_variable cond;
    size_t max{50};

  public:
    ConcurrentQueue() = default;
    ConcurrentQueue(size_t max) : max(max) {};

    void push(T value) {
        std::unique_lock<std::mutex> uniq_lck(mut);

        cond.wait(uniq_lck, [this] { return que.size() <= max; });

        que.push(value);
        cond.notify_one();
    }

    void pop(T &value) {
        std::unique_lock<std::mutex> uniq_lck(mut);

        cond.wait(uniq_lck, [this] { return !que.empty(); });

        value = que.front();
        que.pop();
        cond.notify_one();
    }
};

#endif // CONCURRENT_QUEUE_H
