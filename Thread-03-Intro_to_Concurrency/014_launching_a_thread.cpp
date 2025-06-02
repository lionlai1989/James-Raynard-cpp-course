/**
 * Single-threaded C++ Program:
 * Non-threaded C++ programs have a single thread. When this thread starts, it executes the main()
 * function. main() is the entry point of the program. main() can call other functions which run in
 * the main thread. When main() returns, the main thread ends.
 *
 * Multi-threaded C++ Program:
 * Multi-threaded C++ programs also have a main thread. The main thread can start other threads.
 * Each created thread has its own entry point function.
 */

#include <iostream> // cout
#include <thread>   // thread

using namespace std;

class Hello {
    /**
     * A functor is a class that overloads the function call () operator.
     * The function call operator will be the thread entry point function.
     */
  public:
    void operator()() { std::cout << "Hello, Functor Thread!\n"; }
};

// Callable object - thread entry point
void hello() { cout << "Hello, Thread!\n"; }

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 014_launching_a_thread.cpp && ./a.out
int main() {
    /**
     * std::thread constructor takes a callable object which is the thread entry point function.
     * The constructor will start the thread which will execute immediately.
     * The entry point function can be any callable object. It cannot be overloaded and any return
     * value is ignored.
     */
    // Create an std::thread object
    thread thr(hello);

    // The parent thread continues execution immediately after the thread is launched.

    // Wait for the thread to complete. Blocking call.
    thr.join();

    // Create an object of the functor class
    Hello hello;
    // Pass the functor object to std::thread's constructor
    thread thr2(hello);
    thr2.join();

    // Use a lambda expression as the thread's entry point
    thread thr3([]() { cout << "Hello, Lambda Thread!\n"; });
    thr3.join();
}
