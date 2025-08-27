#include <chrono>
#include <future>
#include <iostream>
#include <thread>

void produce(std::promise<int> &px) {
    using namespace std::literals;

    // Produce the result
    int x = 42;
    std::this_thread::sleep_for(2s);

    // Store the result in the shared state
    std::cout << "Promise sets shared state to " << x << '\n';
    px.set_value(x);
}

/**
 * std::future is designed for use with a single consumer thread.
 * std::future is a move-only class (cannot be copied).
 */
void consume(std::future<int> &fx) {
    // Get the result from the shared state
    std::cout << "Future calling get()...\n";
    int x = fx.get();
    std::cout << "Future returns from calling get()\n";
    std::cout << "The answer is " << x << '\n';
}

/**
 * std::shared_future can be copied.
 * Each thread has its own object. Each threads share the same state with the std::promise.
 */
void consume2(std::shared_future<int> &fx) {
    // Get the result from the shared state
    std::cout << "Thread " << std::this_thread::get_id() << " calling get()...\n";
    int x = fx.get();
    std::cout << "Thread " << std::this_thread::get_id() << " returns from calling get()\n";
    std::cout << "Thread " << std::this_thread::get_id() << " has answer " << x << '\n';
}

// g++ -std=c++20 -Wall -Wextra -pthread 054-promises_with_multiple_waiting_threads.cpp && ./a.out
int main() {

    /**
     * The following code block is undefined behaviour because std::future is passed to two threads.
     */
    // std::promise<int> prom;
    // std::future<int> fut = prom.get_future();
    // std::thread thr_producer(produce, std::ref(prom));
    // std::thread thr_consumer(consume, std::ref(fut));
    // std::thread thr_consumer2(consume, std::ref(fut));
    // thr_consumer.join();
    // thr_consumer2.join();
    // thr_producer.join();

    std::cout << "--------------------------------\n";

    std::promise<int> prom;

    // Get an std::shared_future associated with the promise
    // This will move the promise's future into a shared future
    std::shared_future<int> shared_fut1 = prom.get_future();

    // Copy the shared future object
    std::shared_future<int> shared_fut2 = shared_fut1;

    std::thread thr_producer(produce, std::ref(prom));

    // Start two consumer threads
    // The consumer task function takes a shared future as argument
    // Each thread uses a different shared future object
    std::thread thr_consumer1(consume2, std::ref(shared_fut1));
    std::thread thr_consumer2(consume2, std::ref(shared_fut2));

    thr_consumer1.join();
    thr_consumer2.join();
    thr_producer.join();
}
