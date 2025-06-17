/**
 * Data races are two or more threads accessing the same memory location concurrently, and at least
 * one of the threads modifies the value without thread synchronization.
 */

#include <iostream> // cout
#include <string>   // string
#include <thread>   // thread

void print(std::string str) {
    // A very artificial way to display a string!
    for (int i = 0; i < 5; ++i) {
        /**
         * Unsynchronized threads which make conflicting accesses.
         * But where is the shared memory location?
         * The std::cout is actually a global object of the class "std::basic_ostream<char>".
         * Here, we access the global object using left-shift operator which modifies the global
         * object.
         *
         * What will go wrong?
         * 1. Threads can be interrupted during output.
         * 2. Other threads can run and write their output.
         * 3. The output from different threads can be interleaved.
         */
        std::cout << str[0] << str[1] << str[2] << std::endl;
    }
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 024-data_races.cpp && ./a.out
int main() {
    std::thread thr1(print, "abc");
    std::thread thr2(print, "def");
    std::thread thr3(print, "xyz");

    // Wait for the tasks to complete
    thr1.join();
    thr2.join();
    thr3.join();
}
