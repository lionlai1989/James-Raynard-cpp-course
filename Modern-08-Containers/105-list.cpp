/**
 * std::list is a doubly linked list.
 *
 * Characteristics:
 * - Bidirectional Access: Elements can be accessed sequentially in both directions (forward and
 * backward).
 * - No Random Access: Does not support `operator[]` or `at()`. Accessing an element by index is
 * O(N).
 * - Fast Insertions/Deletions: Adding or removing elements at any position is O(1), provided an
 * iterator to the position is known. This is significantly faster than `std::vector` for operations
 * in the middle.
 * - Memory Overhead: Each element requires extra memory for two pointers (prev/next) and
 * independent heap allocation, making it less memory efficient than `std::vector`.
 * - Cache Locality: Nodes are allocated individually on the heap, leading to poor cache locality
 * compared to the contiguous memory of `std::vector`.
 *
 * Use Case:
 * Use `std::list` when you frequently need to insert or remove elements from the middle of the
 * sequence and do not need random access.
 */

#include <iostream>
#include <list>

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 105-list.cpp && ./a.out
int main() {
    list<int> l{4, 3, 1};

    cout << "Initial elements in list" << endl;
    for (auto el : l) // Use a range-for loop to display all the elements
        cout << el << ", ";
    cout << endl;

    auto last = end(l);
    advance(last, -1);            // i is an iterator to the second element
    auto two = l.insert(last, 2); // Insert a new element before the last element

    cout << "Elements in list after inserting 2" << endl;
    for (auto el : l)
        cout << el << ", ";
    cout << endl;

    l.erase(two); // Remove this element

    cout << "Elements in list after erasing 2" << endl;
    for (auto node : l)
        cout << node << ", ";
    cout << endl;
}
