#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

class ConcurrentQueueEmpty : public std::runtime_error {
  public:
    ConcurrentQueueEmpty() : std::runtime_error("Queue is empty") {}
    explicit ConcurrentQueueEmpty(const char *s) : std::runtime_error(s) {}
};

class ConcurrentQueueFull : public std::runtime_error {
  public:
    ConcurrentQueueFull() : std::runtime_error("Queue is full") {}
    explicit ConcurrentQueueFull(const char *s) : std::runtime_error(s) {}
};

template <class T> class ConcurrentQueue {
  private:
    // Data members
    std::mutex mut;
    std::queue<T> que;
    size_t max;

  public:
    // Constructors
    ConcurrentQueue(size_t max = 50) : max(max) {};

    // Deleted special member functions, copy and move operators are deleted.
    ConcurrentQueue(const ConcurrentQueue &) = delete;
    ConcurrentQueue &operator=(const ConcurrentQueue &) = delete;
    ConcurrentQueue(ConcurrentQueue &&) = delete;
    ConcurrentQueue &operator=(ConcurrentQueue &&) = delete;

    // Push an element onto the queue
    void push(const T &value) {
        std::lock_guard<std::mutex> lck_guard(mut);

        if (que.size() >= max) {
            throw ConcurrentQueueFull();
        }

        que.push(value);
    }

    // Pop an element from the queue
    void pop(T &value) {
        std::unique_lock<std::mutex> uniq_lck(mut);

        if (que.empty()) {
            throw ConcurrentQueueEmpty();
        }

        value = que.front();
        que.pop();
    }
};

// Shared queue object
ConcurrentQueue<std::string> conc_que;

void reader() {
    using namespace std::literals;
    std::this_thread::sleep_for(2s); // Pretend to be busy...
    std::string sdata;

    // Pop some elements from the queue
    std::cout << "Reader calling pop..." << std::endl;
    for (int i = 0; i < 50; ++i) {
        conc_que.pop(sdata); // Pop the data off the queue
        std::cout << "Reader received data: " << sdata << std::endl;
    }
}

void writer() {
    // Push the data onto the queue
    for (int i = 0; i < 50; ++i) {
        std::string sdata = "Item " + std::to_string(i);
        conc_que.push(sdata);
    }

    std::cout << "Writer returned from push..." << std::endl;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 082-concurrent_queue.cpp && ./a.out
int main() {
    // Start the threads
    auto write_fut = std::async(std::launch::async, writer);
    auto read_fut = std::async(std::launch::async, reader);

    // Wait for them to complete
    try {
        read_fut.get();
    } catch (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    try {
        write_fut.get();
    } catch (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}