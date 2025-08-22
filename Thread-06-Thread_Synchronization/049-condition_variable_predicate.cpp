/**
 * Condition variable with predicate
 *
 * The example in `048-condition_variable.cpp` has a problem. `condition_variable.wait()` will block
 * until the condition variable is notified. If the writer calls `notify_one()` before the reader
 * thread calls `wait()`, the reader will miss the notification and will wait indefinitely. This is
 * known as a "lost wakeup".
 *
 * Moreover, the reader thread will be "spuriously" woken up, meaning that it can wake up anyway
 * without the writer thread calling `notify_one()`. WHAT!!! C++ is crazy!
 *
 * Fortunately (of course), C++ provides a way to avoid "lost wakeups" and "spurious wakeups".
 */

#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono;

/**
 * Example of a "lost wakeup"
 *
 * The writer thread sends its notification before the reader calls wait()
 * The reader never receives the notification
 * The reader thread blocks indefinitely
 */
std::string sdata;                // The shared data
std::mutex mut;                   // Mutex to protect critical sections
std::condition_variable cond_var; // The condition variable
void reader() {
    // Lock the mutex
    std::cout << "Reader thread locking mutex\n";
    std::unique_lock<std::mutex> uniq_lck(mut); // blocking until mutex is available
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

    // Notify the condition variable
    std::cout << "Writer thread sends notification\n";
    cond_var.notify_one();
}

////////////////////////////////////////////////////////////

/**
 * Condition variable with predicate
 *
 * The reader thread will wait until "condition" becomes true
 * This avoids lost and spurious wakeups
 */
std::string sdata2;                // The shared data
std::mutex mut2;                   // Mutex to protect critical sections
std::condition_variable cond_var2; // The condition variable
bool condition2 = false;           // bool flag for predicate
void reader2() {
    // Lock the mutex
    std::cout << "Reader thread locking mutex\n";
    std::unique_lock<std::mutex> uniq_lck(mut2);
    std::cout << "Reader thread has locked the mutex\n";

    // Call wait()
    // This will unlock the mutex and make this thread
    // sleep until the condition variable wakes us up
    std::cout << "Reader thread sleeping...\n";

    // Lambda predicate that checks the flag
    cond_var2.wait(uniq_lck, [] { return condition2; });

    // The condition variable has woken this thread up
    // and locked the mutex
    std::cout << "Reader thread wakes up\n";

    // Display the new value of the string
    std::cout << "Data is \"" << sdata2 << "\"\n";
    std::cout << "Reader thread unlocks the mutex\n";
}
void writer2() {
    {
        // Lock the mutex
        std::cout << "Writer thread locking mutex\n";

        // Lock the mutex
        // This will not be explicitly unlocked
        // std::lock_guard is sufficient
        std::lock_guard<std::mutex> lck_guard(mut2);
        std::cout << "Writer thread has locked the mutex\n";

        // Pretend to be busy...
        std::this_thread::sleep_for(2s);

        // Modify the string
        std::cout << "Writer thread modifying data...\n";
        sdata2 = "Populated2";

        // Set the flag
        condition2 = true;

        std::cout << "Writer thread unlocks the mutex\n";
    }

    // Notify the condition variable
    std::cout << "Writer thread sends notification\n";
    cond_var2.notify_one();
}

////////////////////////////////////////////////////////////

/**
 * Condition variable with predicate with multiple waiting threads
 */
std::string sdata3;                // The shared data
std::mutex mut3;                   // Mutex to protect critical sections
std::condition_variable cond_var3; // The condition variable
bool condition3 = false;           // bool flag for predicate
void reader3() {
    // Lock the mutex
    std::cout << "Reader thread locking mutex\n";
    std::unique_lock<std::mutex> uniq_lck(mut3);
    std::cout << "Reader thread has locked the mutex\n";

    // Call wait()
    // This will unlock the mutex and make this thread
    // sleep until the condition variable wakes us up
    std::cout << "Reader thread sleeping...\n";

    // Lambda predicate that checks the flag
    cond_var3.wait(uniq_lck, [] { return condition3; });

    // The condition variable has woken this thread up
    // and locked the mutex
    std::cout << "Reader thread " << std::this_thread::get_id() << " wakes up\n";

    // Display the new value of the string
    std::cout << "Data is \"" << sdata3 << "\"\n";
    std::cout << "Reader thread unlocks the mutex\n";
}
void writer3() {
    {
        // Lock the mutex
        std::cout << "Writer thread locking mutex\n";

        // Lock the mutex
        // This will not be explicitly unlocked
        // std::lock_guard is sufficient
        std::lock_guard<std::mutex> lck_guard(mut3);
        std::cout << "Writer thread has locked the mutex\n";

        // Pretend to be busy...
        std::this_thread::sleep_for(2s);

        // Modify the string
        std::cout << "Writer thread modifying data...\n";
        sdata3 = "Populated3";

        // Set the flag
        condition3 = true;

        std::cout << "Writer thread unlocks the mutex\n";
    }

    // Notify the condition variable
    std::cout << "Writer thread sends notification\n";

    cond_var3.notify_all(); // Notify all waiting threads
    /**
     * If notify one by one, how does it guarantee that all waiting threads will be notified?
     * It may notify the same waiting thread more than once? Right?
     *
     * for (int i = 0; i < 2; ++i)
     *    cond_var.notify_one();
     */
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 049-condition_variable_predicate.cpp && ./a.out
int main() {

    /**
     * The writer thread calls `notify_one` before the reader calls `wait()`.
     *
     * This section will wait indefinitely.
     */
    // sdata = "Empty";
    // std::cout << "Data is \"" << sdata << "\"\n";
    // std::thread write(writer);
    // std::this_thread::sleep_for(500ms);
    // std::thread read(reader);
    // write.join();
    // read.join();

    std::cout << "--------------------------------\n";

    /**
     * The notification is not lost, even if the writer thread finishes before the reader thread
     * starts.
     * Or there is a "spurious wakeup" (wait returns without a notification)
     */
    sdata2 = "Empty2";
    std::cout << "Data is \"" << sdata2 << "\"\n";
    std::thread write2(writer2);
    std::this_thread::sleep_for(500ms);
    std::thread read2(reader2);
    write2.join();
    read2.join();

    std::cout << "--------------------------------\n";

    /**
     * Multiple reader threads
     */
    sdata3 = "Empty3";
    std::cout << "Data is \"" << sdata3 << "\"\n";
    std::thread write3(writer3);
    std::thread read31(reader3);
    std::this_thread::sleep_for(10ms);
    std::thread read32(reader3);
    std::this_thread::sleep_for(10ms);
    std::thread read33(reader3);
    std::this_thread::sleep_for(10ms);
    write3.join();
    read31.join();
    read32.join();
    read33.join();
}
