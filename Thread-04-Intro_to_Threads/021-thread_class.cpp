/**
 * std::thread class is implemented using RAII.
 * The constructor acquires a resource.
 * The destructor releases the resource.
 *
 * An std::thread object has OWNERSHIP of an execution thread. That is only one object can be
 * bound to an execution thread at a time. This also means that the thread object cannot be copied
 * because that mean we will have two objects bound to the same system resource at the same time.
 *
 * Thus, std::thread is a move-only class. When we use move operation to transfer the ownership of
 * the thread object, the source (moved-from) object is no longer associated with the execution
 * thread.
 *
 */

#include <iostream> // cout
#include <thread>   // thread

// The task function
void hello_pause() {
    using namespace std::literals;
    std::this_thread::sleep_for(1s);
    std::cout << "Hello, Thread!\n";
}

/**
 * Function taking a thread object as argument
 * The object must be moved into the argument
 */
void func(std::thread thr) {
    /**
     * std::thread is a move-only type (it cannot be copied). When we pass a move-only type to a
     * function by value, the compiler automatically uses move semantics. This is part of C++'s
     * special handling of move-only types to make them more convenient to use.
     */

    std::cout << "Received thread with ID " << thr.get_id() << '\n';

    // The function argument now "owns" the system thread
    // It is responsible for calling join()
    thr.join();
}

/**
 * Function taking a thread object as argument
 * The object must be moved into the argument
 */
void func2(std::thread &&thr) {
    std::cout << "Received thread with ID " << thr.get_id() << '\n';

    // The function argument now "owns" the system thread
    // It is responsible for calling join()
    thr.join();
}

/**
 * Function that throws an exception
 */
void hello_throw() {
    try {
        // Throw an exception
        throw std::exception();
    } catch (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
    std::cout << "Hello, Thread! (after exception)\n";
}

/**
 * Function that throws an exception
 */
void hello_throw2() {
    // Throw an exception
    throw std::exception();
    std::cout << "Hello, Thread! (after exception)\n";
}

// Function returning a std::thread object
std::thread generate_thread() {
    // Start the thread
    std::thread thr(hello_pause);
    // Return a local variable
    return thr; // thr is moved from
}

// Function returning a std::thread object
std::thread generate_thread2() {
    // Return a temporary object
    return std::thread(hello_pause); // thread is moved from
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 021-thread_class.cpp && ./a.out
int main() {
    // std::thread is a move-only object
    std::thread thr(hello_pause);
    // Display the child thread's ID
    std::cout << "Hello thread has ID " << thr.get_id() << '\n';
    // Pass a named object using std::move()
    func(std::move(thr));
    // We cannot call thr.join() here because thr has been moved from.

    // Pass a temporary object
    func2(std::thread(hello_pause));

    std::cout << "--------------------------------\n";

    // Call a function which return an std::thread object
    std::thread thr2 = generate_thread();
    std::cout << "Received thread with ID " << thr2.get_id() << '\n';
    std::thread thr3 = generate_thread2();
    std::cout << "Received thread with ID " << thr3.get_id() << '\n';

    // thr2 and thr3 objects now "own" the system thread
    // they are responsible for calling join()
    thr2.join();
    thr3.join();

    std::cout << "--------------------------------\n";

    /**
     * Each thread has its own execution stack. This stack is "unwound" when the thread throws an
     * exception.
     * - The destructors for all objects in scope are called.
     * - The program moves up the thread's stack until it finds a suitable handler.
     * - If no handler is found, the program terminates.
     *
     * Other threads, including the parent thread and the main thread, cannot catch the exception.
     * Exceptions can only be handled by the thread that threw them.
     */
    std::thread thr4(hello_throw);
    thr4.join();

    // Check that the program is still running
    std::cout << "Still running\n";

    std::cout << "--------------------------------\n";

    // The following code won't work because the main thread cannot catch the exception thrown by
    // the child thread.
    try {
        std::thread thr5(hello_throw2);
        thr5.join();
    } catch (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }

    std::cout << "Finished\n";

    return 0;
}
