/**
 * std::shared_ptr
 *
 * std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer.
 * Several shared_ptr objects may own the same object. The object is destroyed and its memory
 * deallocated when the last shared_ptr owning the object is destroyed.
 *
 * Mechanism:
 * - When a shared_ptr is copied or assigned, the reference counter is incremented. No memory
 * allocation for the object is performed.
 * - When a shared_ptr is destroyed, the reference counter is decremented.
 * - When the counter reaches zero, the memory is released.
 *
 * Implementation:
 * shared_ptr typically stores two pointers:
 * 1. A pointer to the allocated memory (the managed object).
 * 2. A pointer to a control block (contains the reference counter and other data).
 *
 * shared_ptr vs unique_ptr:
 * - unique_ptr: Zero overhead compared to a raw pointer (exclusive ownership).
 * - shared_ptr: Additional overhead for the control block and atomic reference counting.
 */

#include <iostream> // cout
#include <memory>   // shared_ptr, make_shared

using namespace std;

// g++ -std=c++20 -Wall -Wextra -pedantic 174-shared_pointer.cpp && ./a.out
int main() {
    /**
     * shared_ptr has two main data members:
     * 1. pointer to the allocated memory
     * 2. pointer to the control block which contains the reference counter
     */

    /**
     * If we call `new` to allocate memory ourself, the control block is allocated separately. This
     * means that the allocated memory and the control block are not contiguous in memory.
     */
    shared_ptr<int> p1{new int(42)}; // less efficient. Not recommended.

    /**
     * make_shared performs a single allocation for the shared memory and the control block in one
     * single contiguous block of memory. This is more efficient than the previous example.
     */
    auto p2{make_shared<int>(42)};

    cout << *p1 << endl; // Single object can be dereferenced
    // ++p1;                // Error - pointer arithmetic not supported
    // ++p2;                // Error - pointer arithmetic not supported

    /**
     * p3 is copy constructed from p2. This means that p3 and p2 now share the same control block.
     * And the reference counter is incremented.
     */
    shared_ptr<int> p3(p2);

    /**
     * The counter in p2 is incremented.
     * The counter in p1 is decremented.
     */
    p1 = p2;
    // Now p1's shared memory pointer and control block pointer are now the same as p2's.

    /**
     * When a shared_ptr is moved-from, its memory allocation pointer is set to nullptr. i.e., p2's
     * memory allocation pointer is set to nullptr. And the reference counter is unchanged.
     * In another word, p4 steals the memory allocation and the control block from p2.
     */
    shared_ptr<int> p4(std::move(p2));

    p1 = nullptr; // Calls delete on the pointer member
                  // and sets the pointer to nullptr
}
