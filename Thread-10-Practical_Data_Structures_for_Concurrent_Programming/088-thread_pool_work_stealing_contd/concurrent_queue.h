/**
 * ConcurrentQueue supports work stealing with try_push() and try_pop()
 * Add non-blocking operations to the ConcurrentQueue:
 *   - Return immediately if they cannot obtain a lock.
 *   - try_push() returns immediately if the queue is full.
 *   - try_pop() returns immediately if the queue is empty.
 */

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <mutex>
#include <queue>

using namespace std::literals;

template <class T> class ConcurrentQueue {
    std::timed_mutex mut;
    std::queue<T> que;
    std::size_t max{50};

  public:
    ConcurrentQueue() = default;
    ConcurrentQueue(std::size_t max) : max(max) {};

    bool try_push(T value) {
        // Lock the mutex with a timeout. We do not want the constructor to lock the mutex because
        // we want to lock the mutex ourselves.
        std::unique_lock<std::timed_mutex> lck_guard(mut, std::defer_lock);

        // Try 1ms but cannot lock successfully or queue is full - return immediately
        if (!lck_guard.try_lock_for(1ms) || que.size() >= max) {
            return false;
        }

        // Locked - add the element to the queue
        que.push(value);

        return true;
    }

    bool try_pop(T &value) {
        // Lock the mutex with a time-out
        std::unique_lock<std::timed_mutex> lck_guard(mut, std::defer_lock);

        // Try 1ms but cannot lock successfully or queue is empty - return immediately
        if (!lck_guard.try_lock_for(1ms) || que.empty()) {
            return false;
        }

        // Locked - remove front element from the queue
        value = que.front();
        que.pop();

        return true;
    }
};

#endif // CONCURRENT_QUEUE_H
