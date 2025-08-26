/**
 * Futures and Promises
 *
 * std::thread does not provide a way to return a value from a thread.
 * std::future and std::promise can transfer data between threads.
 *
 * Producer-Consumer Model:
 *  - An std::promise is associated with the producer
 *  - An std::future is associated with the consumer
 *
 * Exception Handling:
 *  - Futures and promises also work with exceptions. The promise stores the exception in the shared
 *    state.
 *  - This exception will be rethrown in the consumer thread by the future's blocking function.
 *  - The producer thread "throws" the exception to the consumer thread.
 *
 * std::future
 *  - Represents a value that will be available at some point in the future.
 *
 * std::promise
 *  - The constructor of std::promise creates an associated std::future object.
 */

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

/**
 * Example using std::promise and std::future to send a result from a producer thread to a consumer
 * thread
 */
void produce(std::promise<int> &px) {
    using namespace std::literals;

    // Produce the result
    int x = 42;
    std::this_thread::sleep_for(2s);

    // Store the result in the shared state
    std::cout << "Promise sets shared state to " << x << '\n';
    px.set_value(x);
}
void consume(std::future<int> &fx) {
    // Get the result from the shared state
    std::cout << "Future calling get()...\n";
    int x = fx.get();
    std::cout << "Future returns from calling get()\n";
    std::cout << "The answer is " << x << '\n';
}

////////////////////////////////////////////////////////////

/**
 * Example using std::promise and std::future to throw an exception from a producer thread to a
 * consumer thread
 */
void produce2(std::promise<int> &px) {
    try {
        using namespace std::literals;
        int x = 42;
        std::this_thread::sleep_for(2s);

        // Code that may throw
        if (1)
            throw std::out_of_range("Oops");

        // No exception - store the result in the shared state
        std::cout << "Promise sets shared state to " << x << '\n';
        px.set_value(x);
    } catch (...) {
        // Exception thrown - store it in the shared state
        px.set_exception(std::current_exception());
    }
}
void consume2(std::future<int> &fx) {
    std::cout << "Future calling get()...\n";
    try {
        // Get the result from the shared state - may throw
        int x = fx.get();
        std::cout << "Future returns from calling get()\n";
        std::cout << "The answer is " << x << '\n';
    } catch (std::exception &e) {
        // Exception thrown - get it from the shared state
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}

////////////////////////////////////////////////////////////

/**
 * In produce2 and consume2, we used try-catch blocks to throw and catch exceptions.
 * C++11 has std::make_exception_ptr to simplify this and avoid try-catch "boilerplate" code.
 *  - Takes an exception object we want to throw
 *  - Returns a pointer to its argument
 *  - Passes this pointer to set_exception()
 */
void produce3(std::promise<int> &px) {
    using namespace std::literals;
    int x = 42;
    std::this_thread::sleep_for(2s);

    // Code that may throw
    if (1) {
        px.set_exception(std::make_exception_ptr(std::out_of_range("Oops")));
        return;
    }

    // No exception - store the result in the shared state
    std::cout << "Promise sets shared state to " << x << '\n';
    px.set_value(x);
}
void consume3(std::future<int> &fx) {
    std::cout << "Future calling get()...\n";
    try {
        // Get the result from the shared state - may throw
        int x = fx.get();
        std::cout << "Future returns from calling get()\n";
        std::cout << "The answer is " << x << '\n';
    } catch (std::exception &e) {
        // Exception thrown - get it from the shared state
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 053-futures_and_promises.cpp && ./a.out
int main() {
    // Create an std::promise object. This creates an associated std::future object and sets up a
    // shared state between them
    std::promise<int> prom;
    // Get the future associated with the promise
    std::future<int> fut = prom.get_future();
    // Start the threads
    // The producer task function takes the promise as argument
    std::thread thr_producer(produce, std::ref(prom));
    // The consumer task function takes the future as argument
    std::thread thr_consumer(consume, std::ref(fut));
    thr_consumer.join();
    thr_producer.join();

    std::cout << "--------------------------------\n";

    std::promise<int> prom2;
    std::future<int> fut2 = prom2.get_future();
    std::thread thr_producer2(produce2, std::ref(prom2));
    std::thread thr_consumer2(consume2, std::ref(fut2));
    thr_consumer2.join();
    thr_producer2.join();

    std::cout << "--------------------------------\n";

    std::promise<int> prom3;
    std::future<int> fut3 = prom3.get_future();
    std::thread thr_producer3(produce3, std::ref(prom3));
    std::thread thr_consumer3(consume3, std::ref(fut3));
    thr_consumer3.join();
    thr_producer3.join();
}
