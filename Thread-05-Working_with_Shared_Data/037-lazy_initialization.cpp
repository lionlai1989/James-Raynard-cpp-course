/**
 * Lazy Initialization
 * A variable is initialized only when it is first used. This is useful when a variable is expensive
 * to construct or when it may not be needed at all.
 * It can be used in multi-threaded code, but we need to avoid data races.
 */

#include <mutex>

/**
 * Lazy initialization (single-threaded)
 *
 * `ptest` is initialized only when first used. `ptest` starts as nullptr and the object is created
 * only when `ptest` is first accessed.
 * The problem is that it is not thread-safe in a multi-threaded context.
 */
class Test {
    // ...
  public:
    void func() { /*...*/ }
};
Test *ptest = nullptr; // Variable to be lazily initialized
void process() {
    if (!ptest)           // First time variable has been used
        ptest = new Test; // Initialize it
    ptest->func();        // Use it
}

/**
 * Lazy initialization (multi-threaded)
 *
 * This approach uses a mutex to protect the initialization of the variable.
 * However, it is INEFFICIENT because every call acquires the mutex even after initialization.
 */
class Test2 {
    // ...
  public:
    void func() { /*...*/ }
};
Test2 *ptest2 = nullptr; // Variable to be lazily initialized
std::mutex mut;
void process2() {
    std::unique_lock<std::mutex> uniq_lck(mut); // Protect ptest2

    if (!ptest2)
        ptest2 = new Test2;

    uniq_lck.unlock();

    ptest2->func();
}

/**
 * Double-checked Locking pattern
 * Efficient thread-safe Lazy initialization (multi-threaded)
 * Explain why `ptest3` is checked twice. The answer is in `038-double_checked_locking.cpp`.
 */
class Test3 {
    // ...
  public:
    void func() { /*...*/ }
};
Test3 *ptest3 = nullptr; // Variable to be lazily initialized
std::mutex mut2;
void process3() {
    if (!ptest3) { // First check of ptest
        std::lock_guard<std::mutex> lck_guard(mut2);

        if (!ptest3)            // Second check of ptest
            ptest3 = new Test3; // Initialize ptest
    }
    ptest3->func();
}
