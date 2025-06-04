#include <iostream>
#include <thread>

class ThreadGuard {
    std::thread thr;

  public:
    // Constructor takes rvalue reference argument (std::thread is move-only)
    // Note that even though `thr` is declared as an rvalue reference, the name `thr` is itself an
    // lvalue inside the function body.
    explicit ThreadGuard(std::thread &&thr) : thr(std::move(thr)) {}

    // Destructor - join the thread if necessary
    ~ThreadGuard() {
        // A std::thread object can only be joined once. Thus, we check if it is joinable before
        // calling join(). The joinable() method returns false if the join() or detach() methods
        // have already been called. Or it the thread object is not associated with an execution
        // thread.
        if (thr.joinable())
            thr.join();
    }

    // Delete copy constructor to prevent copying
    ThreadGuard(const ThreadGuard &) = delete;
    // Delete copy assignment operator to prevent copying
    ThreadGuard &operator=(const ThreadGuard &) = delete;

    // The move assignment operator is not synthesized
};

// Callable object - thread entry point
void hello() { std::cout << "Hello, Thread!\n"; }

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 022-managing_a_thread.cpp && ./a.out
int main() {
    /**
     * The problem with the following code is that if an exception is thrown before the child thread
     * is joined, then we have a thread that is not joined before the program terminates.
     *
     * try {
     *     // Create an std::thread object
     *     std::thread thr(hello);
     *
     *     // Code that might throw an exception
     *     throw std::exception();
     *
     *     thr.join();
     * } catch (std::exception &e) {
     *     std::cout << "Exception caught: " << e.what() << '\n';
     *     thr.join();
     * }
     *
     */

    /**
     * An obvious solution to the problem above is to join the thread in the catch block.
     * However, this is very verbose and not an elegant solution.
     */
    // Create an std::thread object
    std::thread thr(hello);
    try {
        throw std::exception();
        thr.join();
    } catch (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << '\n';
        thr.join(); // Call join() before thr's destructor is called
    }

    std::cout << "--------------------------------" << std::endl;

    /**
     * A more elegant solution is to use the RAII idiom. We wrap the std::thread object in a class,
     * ThreadGuard, and the class's destructor calls join() on the std::thread object.
     */

    try {
        std::thread thr2(hello);
        ThreadGuard tguard{std::move(thr2)};

        // Or we can use the following syntax to create the ThreadGuard object
        // thread_guard tguard{std::thread(hello)};

        // Code which might throw an exception
        throw std::exception();

        // When tguard goes out of scope, its destructor "~ThreadGuard" will be called and join()
        // will be called on the std::thread object.
    } catch (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }

    std::cout << "--------------------------------" << std::endl;

    /**
     * The C++20 std::jthread class is a more modern and safer way to manage threads.
     *
     *     try {
     *         // Create an std::jthread object
     *         std::jthread thr(hello);
     *
     *         // Code that might throw an exception
     *         throw std::exception();
     *
     *         // std::jthread's destructor will call join() if necessary
     *     } catch (std::exception &e) {
     *         std::cout << "Exception caught: " << e.what() << '\n';
     *     }
     *
     */

    return 0;
}
