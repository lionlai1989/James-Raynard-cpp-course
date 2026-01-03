/**
 * std::forward_list is a singly linked list.
 *
 * Memory Allocation:
 * - The `forward_list` object itself (typically just a head pointer) resides
 *   where it is declared (e.g., on the stack for local variables).
 * - The elements are stored in nodes individually allocated on the heap.
 * - Each node contains the value and a pointer to the next node.
 * - Memory is non-contiguous, unlike `std::vector`.
 *
 * Standard sequential containers usually provide `insert()` and `erase()` to operations
 * at a position (typically *before* the iterator). This works efficiently for containers
 * that support random access or bidirectional traversal.
 *
 * Since `std::forward_list` is singly linked and only supports forward iteration,
 * accessing the previous element (needed to insert *before* a node) is expensive (O(N)).
 * Therefore, it provides `insert_after()` and `erase_after()` to allow efficient O(1)
 * operations by working *after* a known element.
 */

#include <forward_list>
#include <iostream>

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 104-forward_list.cpp && ./a.out
int main() {
    forward_list<int> l{4, 3, 1};

    cout << "Initial elements in list" << endl;
    for (auto el : l) // Use a range-for loop to display all the elements
        cout << el << ", ";
    cout << endl;

    auto second = l.begin();
    advance(second, 1);        // i is an iterator to the second element
    l.insert_after(second, 2); // Insert a new element after the second element

    cout << "Elements in list after inserting 2" << endl;
    for (auto el : l)
        cout << el << ", ";
    cout << endl;

    l.erase_after(second); // Remove this element

    cout << "Elements in list after erasing 2" << endl;
    for (auto node : l)
        cout << node << ", ";
    cout << endl;
}
