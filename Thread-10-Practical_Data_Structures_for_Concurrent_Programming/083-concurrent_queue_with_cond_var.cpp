/**
 * Concurrent Queue with Condition Variables
 *
 * Efficiency Comparison vs. Lock-Free Implementation:
 *
 * 1. Mutex + Condition Variable (This Implementation)
 *    - Pros: Efficient CPU usage. Threads sleep when waiting (0% CPU).
 *    - Cons: Higher latency due to OS context switching overhead.
 *    - Best for: General-purpose use, battery-sensitive apps, or when processing takes longer than
 * synchronization.
 *
 * 2. Lock-Free Michael-Scott Queue (Atomic Operations)
 *    - Pros: Lower latency (avoids context switches), potentially higher throughput.
 *    - Cons: High CPU usage under contention (threads spin/busy-wait).
 *    - Best for: Ultra-low latency requirements or high-frequency data streams where CPU usage is
 * secondary.
 */

#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

using namespace std::literals;

// Simple concurrent queue implementation with condition variable
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

ConcurrentQueueCondVar<std::string> conc_que;

// Waiting thread
void reader() {
    std::string data;

    // Pop some elements from the queue
    std::cout << "Reader calling pop..." << std::endl;
    for (int i = 0; i < 60; ++i) {
        conc_que.pop(data); // Pop the data off the queue
        std::cout << "Reader received data: " << data << std::endl;
    }
}

// Modyifing thread
void writer() {
    using namespace std::literals;
    std::this_thread::sleep_for(2s); // Pretend to be busy...
    std::cout << "Writer calling push..." << std::endl;

    // Push the data onto the queue
    for (int i = 0; i < 60; ++i) {
        std::string data = "Item " + std::to_string(i);
        conc_que.push(data);
    }

    std::cout << "Writer returned from push..." << std::endl;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 083-concurrent_queue_with_cond_var.cpp && ./a.out
int main() {
    // Start the threads
    std::cout << "Starting reader" << std::endl;
    auto read_fut = async(std::launch::async, reader);
    std::cout << "Starting writer" << std::endl;
    auto write_fut = std::async(std::launch::async, writer);

    // Wait for them to complete
    read_fut.wait();
    write_fut.wait();
}
