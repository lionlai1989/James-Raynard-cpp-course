/**
 * Condition Variable Motivation
 *
 * The reader thread waits for a notification
 * The writer thread modifies the shared variable "sdata"
 * The writer thread sends a notification
 * The reader thread receives the notification and resumes
 * The reader thread uses the new value of the shared data
 *
 * std::condition_variable
 *  - wait()
 *      - Takes an argument of type std::unique_lock
 *      - It unlocks its argument and blocks the thread until notified
 *  - wait_for() and wait_until()
 *      - Re-locks their argument if a notification is not received in time
 *  - notify_one()
 *      - Wakes up one of the waiting threads
 *      - The scheduler decides which thread is woken up
 *  - notify_all()
 *	    - Wakes up all the waiting threads
 */

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

using namespace std::literals;

// The shared data
std::string sdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

// Waiting thread
void reader() {
    // Lock the mutex
    std::cout << "Reader thread locking mutex\n";
    // It must be a std::unique_lock because it can be unlocked manually by the condition variable
    std::unique_lock<std::mutex> uniq_lck(mut);
    std::cout << "Reader thread has locked the mutex\n";

    // Call wait()
    // This will unlock the mutex and make this thread
    // sleep until the condition variable wakes us up
    std::cout << "Reader thread sleeping...\n";
    cond_var.wait(uniq_lck);

    // The condition variable has woken this thread up
    // and locked the mutex
    std::cout << "Reader thread wakes up\n";

    // Display the new value of the string
    std::cout << "Data is \"" << sdata << "\"\n";
}

// Notifying thread
void writer() {
    {
        // Lock the mutex
        std::cout << "Writer thread locking mutex\n";

        // Lock the mutex
        // This will not be explicitly unlocked
        // std::lock_guard is sufficient
        std::lock_guard<std::mutex> lck_guard(mut);
        std::cout << "Writer thread has locked the mutex\n";

        // Pretend to be busy...
        std::this_thread::sleep_for(2s);

        // Modify the string
        std::cout << "Writer thread modifying data...\n";
        sdata = "Populated";
    }
    /**
     * The mutex is automatically unlocked at the end of the curly braces "{}". And then
     * `cond_var.notify_one();` is called.
     * If the curly braces were not used, the mutex would be unlocked only at the end of the
     * function, which means that `cond_var.notify_one();` is called before the mutex is unlocked.
     * And this would be wrong in my opinion.
     */

    // Notify the condition variable
    std::cout << "Writer thread sends notification\n";
    cond_var.notify_one(); // notify_one only wakes up one thread
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 048-condition_variable.cpp && ./a.out
int main() {
    // Initialize the shared string
    sdata = "Empty";

    // Display its initial value
    std::cout << "Data is \"" << sdata << "\"\n";

    // Start the threads
    std::thread read(reader);
    std::thread write(writer);

    write.join();
    read.join();
}