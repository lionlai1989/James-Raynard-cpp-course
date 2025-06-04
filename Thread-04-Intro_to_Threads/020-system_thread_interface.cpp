/**
 * System Thread Interface. std::thread uses the system's thread implementation. We could use
 * the system's thread implementation directly but some functionalities are not available in
 * standard C++ such as thread priority and thread affinity.
 */

#include <iostream> // cout
#include <thread>   // thread

using namespace std;

void hello() { cout << "Hello, Thread!" << endl; }

// Task function
// Displays the thread's ID
void hello_showID() { cout << "Hello from thread with ID " << this_thread::get_id() << '\n'; }

void hello_pause() {
    // std::this_thread::sleep_for(std::chrono::seconds(2));
    this_thread::sleep_for(2s);
    cout << "Hello, Thread!\n";
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 020-system_thread_interface.cpp && ./a.out
int main() {
    /**
     * Each execution thread has a handle, which is used internally by the system's thread
     * implementation.
     */
    thread thr(hello);
    // Display the child thread's native handle
    cout << "Hello thread has native handle " << thr.native_handle() << '\n';
    thr.join();
    // Display the child thread's native handle again
    cout << "Hello thread now has native handle " << thr.native_handle() << '\n'; // nullptr

    cout << "--------------------------------" << endl;

    /**
     * Each execution thread has a unique ID. If two threads have the same ID, they are the same
     * object.
     * A new thread may get the same ID as the earlier thread which has completed.
     */
    // Display the main thread's ID
    cout << "Main thread has ID " << this_thread::get_id() << '\n';
    // Create an std::thread object
    thread thr2(hello_showID);
    // Display the child thread's ID
    cout << "Hello thread has ID " << thr2.get_id() << '\n';
    // Wait for the thread to complete
    thr2.join();
    // Display the child thread's ID again
    cout << "Hello thread now has ID " << thr2.get_id() << '\n';

    cout << "--------------------------------" << endl;

    // Create an std::thread object
    cout << "Starting paused thread...\n";
    thread thr3(hello_pause);
    // Wait for the thread to complete
    thr3.join();
}
