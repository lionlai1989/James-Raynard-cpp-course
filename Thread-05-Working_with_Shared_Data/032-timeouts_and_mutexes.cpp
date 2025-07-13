/**
 * It a thread locks an std::mutex, it must not call lock() again until it has called unlock().
 * - Undefined behavior
 * - Usually the program blocks indefinitely
 *
 * std::recursive_mutex is a mutex that can be locked multiple times by the same thread.
 * You probably don't need it. If you do, it's probably a BAD design!
 */

#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

std::recursive_mutex remtx;
std::mutex mtx;

int bad_factorial(int n) {
    if (n <= 1) {
        std::cout << "Returning " << 1 << '\n';
        return 1;
    }

    std::lock_guard<std::recursive_mutex> lck_guard(remtx);

    // Start of critical section
    int retval = n * bad_factorial(n - 1);
    std::cout << "Returning " << retval << std::endl;
    // End of critical section

    return retval;
}

int worst_factorial(int n) {
    if (n <= 1) {
        std::cout << "Returning " << 1 << '\n';
        return 1;
    }

    mtx.lock();

    // Start of critical section
    int retval = n * worst_factorial(n - 1);
    std::cout << "Returning " << retval << std::endl;
    // End of critical section

    mtx.unlock();
    return retval;
}

////////////////////////////////////////////////////////////

std::timed_mutex timed_mtx;

void task1() {
    std::cout << "Task1 trying to lock the mutex\n";
    timed_mtx.lock();
    std::cout << "Task1 locks the mutex\n";
    std::this_thread::sleep_for(5s);
    std::cout << "Task1 unlocking the mutex\n";
    timed_mtx.unlock();
}

void task2() {
    std::this_thread::sleep_for(500ms);
    std::cout << "Task2 trying to lock the mutex\n";

    // Try for 1 second to lock the mutex
    while (!timed_mtx.try_lock_for(1s)) {
        // Returned false
        std::cout << "Task2 could not lock the mutex\n";

        // Try again on the next iteration
    }

    // Returned true - the mutex is now locked

    // Start of critical section
    std::cout << "Task2 has locked the mutex\n";
    // End of critical section

    timed_mtx.unlock();
}

////////////////////////////////////////////////////////////

std::timed_mutex timed_mtx2;

void task3() {
    std::cout << "Task1 trying to get lock\n";
    timed_mtx2.lock();
    std::cout << "Task1 locks the mutex\n";
    std::this_thread::sleep_for(5s);
    std::cout << "Task1 unlocking the mutex\n";
    timed_mtx2.unlock();
}

void task4() {
    std::this_thread::sleep_for(500ms);
    std::cout << "Task2 trying to lock the mutex\n";
    auto deadline = std::chrono::system_clock::now() + 900ms;

    // Try until "deadline" to lock the mutex
    while (!timed_mtx2.try_lock_until(deadline)) {
        // Returned false
        // Update "deadline" and try again
        deadline = std::chrono::system_clock::now() + 900ms;
        std::cout << "Task2 could not lock the mutex\n";
    }

    // Returned true - the mutex is now locked

    // Start of critical section
    std::cout << "Task2 has locked the mutex\n";
    // End of critical section

    timed_mtx2.unlock();
}

////////////////////////////////////////////////////////////

std::timed_mutex timed_mtx3;

void task5() {
    std::cout << "Task1 trying to lock the mutex\n";
    std::lock_guard<std::timed_mutex> lck_guard(timed_mtx3);
    std::cout << "Task1 locks the mutex\n";
    std::this_thread::sleep_for(5s);
    std::cout << "Task1 unlocking the mutex\n";
}

void task6() {
    std::this_thread::sleep_for(500ms);
    std::cout << "Task2 trying to lock the mutex\n";

    // Use std::defer to avoid the std::unique_lock contructor to lock the mutex.
    // If std::defer_lock is not used, the program will exit with an error (undefined behavior).
    // The reason is that the std::unique_lock constructor will lock the mutex.
    // try_lock_for will also call lock() to lock the mutex again. And we are calling lock()
    // twice without calling unlock(). This is undefined behavior.
    std::unique_lock<std::timed_mutex> uniq_lck(timed_mtx3, std::defer_lock);

    // Try for 1 second to lock the mutex
    while (!uniq_lck.try_lock_for(1s)) {
        // Returned false
        std::cout << "Task2 could not lock the mutex\n";

        // Try again on the next iteration
    }

    // Returned true - the mutex is now locked

    // Start of critical section
    std::cout << "Task2 has locked the mutex\n";
    // End of critical section
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 032-timeouts_and_mutexes.cpp && ./a.out
int main() {
    // This will block indefinitely or undefined behavior
    // std::thread thr1(worst_factorial, 10);
    // thr1.join();

    std::thread thr2(bad_factorial, 10);
    thr2.join();

    std::cout << "--------------------------------\n";

    std::thread thr3(task1);
    std::thread thr4(task2);
    thr3.join();
    thr4.join();

    std::cout << "--------------------------------\n";

    std::thread thr5(task3);
    std::thread thr6(task4);
    thr5.join();
    thr6.join();

    std::cout << "--------------------------------\n";

    std::thread thr7(task5);
    std::thread thr8(task6);

    thr7.join();
    thr8.join();

    return 0;
}
