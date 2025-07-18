/**
 * Multiple reader, single writer
 * In a scenario where multiple threads read from a shared resource, and only one thread writes
 * to it, we need mutex to synchronize the access to the shared resource. If mutex is used, all
 * threads are synchronized, which means they must execute the critical section sequentially even
 * when it's NOT necessary. This is HARMFUL to the performance. It WASTES the CPU time.
 *
 * For example, if there are 40 readers and 2 writers, and the readers are reading the shared
 * resource, these 40 readers actually DO NOT NEED TO BE SYNCHRONIZED, because they are not writing
 * to the shared resource.
 *
 * This issue can be solved by using a Read-Write Lock. It locks when there is a thread writing. It
 * does not lock when there are only reading threads.
 *
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mut;

// Shared variable
int x = 0;

void writer() {
    std::lock_guard<std::mutex> lck_guard(mut);

    // Start of critical section
    ++x;
    // End of critical section
}

void reader() {
    // Think harder. Why do we need to lock the mutex here when this thread is only reading?
    std::lock_guard<std::mutex> lck_guard(mut);

    // Start of critical section
    using namespace std::literals;
    std::this_thread::sleep_for(100ms); // simulate the time taken to read the shared resource
    // End of critical section
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 033-multiple_reader_single_writer.cpp && ./a.out
int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 20; ++i)
        threads.push_back(std::thread(reader)); // move semantics

    threads.push_back(std::thread(writer));
    threads.push_back(std::thread(writer));

    for (int i = 0; i < 20; ++i)
        threads.push_back(std::thread(reader));

    // There are 40 readers and 2 writers. Each reader takes 100ms to read the shared resource.
    // Therefore, this program should take 100ms * 40 = 4000ms = 4s to finish.
    for (auto &thr : threads)
        thr.join();
}