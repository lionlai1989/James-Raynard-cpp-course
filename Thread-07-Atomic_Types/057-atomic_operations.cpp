/**
 * Demonstrate member functions of atomic types
 *
 * store(): atomically replace the object's value with its argument
 *
 * load(): atomically return the object's value
 *
 * exchange(): atomically replace the object's value with its argument and return the previous value
 */

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

/**
 * std::atomic_flag is an atomic boolean type
 *
 * Use std::atomic_flag to implement a spin lock, which protects a critical section.
 * A spin lock is essentially a busy-wait loop that repeatedly checks the condition.
 * It is an alternative to locking a mutex or using a condition variable.
 * It is less efficient than a mutex or condition variable because it consumes CPU cycles while
 * waiting.
 *
 * So why use a spin lock?
 *
 * A spin lock remains active while waiting and can continue immediately when the lock is released.
 * With a mutex, the thread may needed to be reloaded or woken up, which can take time.
 *
 * A spin lock is useful when the wait time is expected to be very short (short critical section).
 * It is usually used in low-level programming, such as operating system kernels or real-time
 * systems.
 *
 * Hybrid Mutex:
 * Based on the discussion above, a better approach is to use a hybrid mutex.
 * A hybrid mutex starts with a spin lock with a timeout. If the thread acquires the lock within the
 * timeout, it enters the critical section. If the timeout expires, it falls back to a regular
 * mutex. This way, short waits are handled by the spin lock, while longer waits are handled by the
 * mutex.
 */
std::atomic_flag lock_cout = ATOMIC_FLAG_INIT; // The atomic_flag must be initialized as false
void task(int n) {
    // test_and_set()
    // Returns true if another thread set the flag
    // Returns false if this thread set the flag
    while (lock_cout.test_and_set()) {
    }

    // Start of critical section

    // do some work
    using namespace std::literals;
    std::this_thread::sleep_for(50ms);
    std::cout << "I'm a task with argument " << n << '\n';

    // End of critical section

    // Clear the flag, so another thread can set it
    lock_cout.clear();
}

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 057-atomic_operations.cpp && ./a.out
int main() {
    std::atomic<int> x = 0;
    std::cout << "After initialization: x = " << x << '\n';

    x = 2;     // Atomic assignment to x
    int y = x; // Atomic assignment from x. y can be non-atomic
    std::cout << "After assignment: x = " << x << ", y = " << y << '\n';

    x.store(3);
    std::cout << "After store: x = " << x.load() << '\n';

    std::cout << "Exchange returns " << x.exchange(y) << '\n';
    std::cout << "After exchange: x = " << x << ", y = " << y << '\n';

    std::cout << "--------------------------------\n";

    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(task, i));
    for (auto &thr : threads)
        thr.join();
}
