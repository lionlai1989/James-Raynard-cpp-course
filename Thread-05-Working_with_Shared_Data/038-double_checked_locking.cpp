/**
 * Double-checked Locking algorithm for multi-threaded Lazy initialization
 *
 * What is wrong with single check? Given the code:
 *
 * ```
 *     if (!ptest) {
 *         std::lock_guard<std::mutex> lck_guard(mtx);
 *         ptest = new Test;
 *     }
 * ```
 *
 * The following can happen:
 * - Thread A checks `ptest`, finds it null
 * - Thread B checks `ptest`, finds it null
 * - Thread B locks the mutex
 * - Thread B initializes `ptest`
 * - Thread B unlocks the mutex
 * - Thread A locks the mutex and initializes `ptest` again!!!
 *
 * `ptest` is initialized twice, which is a memory leak.
 */

#include <iostream>
#include <mutex>
#include <thread>

/**
 * Double-checked Locking pattern prior to C++17
 *
 * We use double-checked locking to ensure that `ptest` is only initialized once to avoid the double
 * initialization issue as explained above. This should solve our problem.
 *
 * Or does it?
 *
 * In fact, the code below is still not thread-safe in C++11 and C++14. Here is why:
 * Given the code, `ptest = new Test;`, it has sevaral steps:
 * - Allocate memory to store the `Test` object
 * - Call the constructor of `Test` to initialize the object
 * - Assign the address of the newly created object to `ptest`
 * The problem is that the compiler allows these steps to be performed in a different order, e.g.,
 * 1. Allocate memory to store the `Test` object
 * 2. Assign the address of the memory to `ptest`
 * 3. Call the constructor of `Test`
 *
 * Thus, the code block below can lead to a situation where:
 * - Thread A checks `ptest`, finds it null, locks the mutex
 * - Thread A executes `ptest = new Test;`, which allocates memory and assigns the address to
 *   `ptest`, but does not call the constructor yet.
 * - Thread B checks `ptest`, finds it not null, and jumps out of the if block.
 * - Thread B calls `ptest->func()`, which leads to undefined behavior (UB) because the object is
 *   not initialized yet.
 *
 * However, the code below is thread-safe in C++17 and later versions because the compiler
 * guarantees that the initialization of `ptest` is done in a single, atomic operation.
 * - Allocate memory to store the `Test` object
 * - Call the constructor of `Test` to initialize the object
 * - Assign the address of the newly created object to `ptest`
 * Thus, double-checked locking works correctly in C++17 and later versions.
 */
class Test {
    // ...
  public:
    Test() { std::cout << "Test constructor called\n"; }
    void func() { /*...*/ }
};
Test *ptest = nullptr; // Variable to be lazily initialized
std::mutex mut;
void process() {
    if (!ptest) { // First check of ptest
        std::lock_guard<std::mutex> lck_guard(mut);

        if (!ptest)           // Second check of ptest
            ptest = new Test; // Initialize ptest
    }
    ptest->func();
}

/**
 * The second way to solve the problem above is to use `std::call_once()`.
 * - A given function is only called once, no matter how many threads call it.
 * - It is done in one thread.
 * - The thread cannot be interrupted until the function call completes.
 */
class Test2 {
    // ...
  public:
    Test2() { std::cout << "Test2 constructor called\n"; }
    void func() { /*...*/ }
};
Test2 *ptest2 = nullptr;    // Variable to be lazily initialized
std::once_flag ptest2_flag; // The flag stores synchronization data
void process2() {
    // Pass a callable object which performs the initialization.
    // It is thread-safe and ensures that `ptest2` is initialized only once.
    // It is also less overhead than using a mutex.
    std::call_once(ptest2_flag, []() { ptest2 = new Test2; });
    ptest2->func();
}

/**
 * The third way to solve the problem above is to use Meyers singleton (name after Scott Meyers).
 * This is actually a recommended way if `ptest` is not used outside the function.
 */
class Test3 {
    // ...
  public:
    Test3() { std::cout << "Test3 constructor called\n"; }
    void func() { /*...*/ }
};
void process3() {
    static Test3 ptest; // Variable which is lazily initialized
    ptest.func();
}

/**
 * In conclusion, there are four ways to do thread-safe lazy initialization in C++:
 * 1. Naive use of mutexes (inefficient)
 * 2. Use std::call_once() (efficient)
 * 3. Use double-checked locking (efficient, but only in C++17 and later)
 * 4. Use Meyers singleton with static local variable
 */

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 038-double_checked_locking.cpp && ./a.out
int main() {
    std::thread thr1(process);
    std::thread thr2(process);
    thr1.join();
    thr2.join();

    std::cout << "--------------------------------\n";

    std::thread thr3(process2);
    std::thread thr4(process2);
    thr3.join();
    thr4.join();

    std::cout << "--------------------------------\n";

    std::thread thr5(process3);
    std::thread thr6(process3);
    thr5.join();
    thr6.join();

    return 0;
}