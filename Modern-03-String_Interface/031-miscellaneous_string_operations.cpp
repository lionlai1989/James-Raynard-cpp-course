/**
 * Bothe std::string and std::vector have a data() member function that returns a pointer to the
 * container's internal memory. For std::string, this memory stores a null-terminated character
 * array, equivalent to `c_str()`. For std::vector, this memory stores an array of elements.
 */

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

void print(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i)
        cout << arr[i] << ", ";
}

// g++ -std=c++17 -Wall -Wextra -pedantic 031-miscellaneous_string_operations.cpp && ./a.out
int main() {
    // This example shows how to use std::vector's data() member function to pass the
    // vector's internal memory to a function that expects a pointer to an array.
    vector<int> numbers{1, 2, 3, 4, 5};
    print(numbers.data(), numbers.size());

    cout << "--------------------------------" << endl;

    string s1{"Hello"};
    string s2{"Goodbye"};

    cout << "s1: " << s1 << ", s2: " << s2 << endl << endl;

    /**
     * Default implementation of swap()
     * It uses a temporary object:
     * ```cpp
     * T temp = a; // Copy constructor is called
     * a = b; // Assignment operator is called
     * b = temp; // Assignment operator is called
     * ```
     * For std::string, this copy-based approach is inefficient because:
     * 1. **Deep Copies**: Each step involves copying the entire character array (O(n) complexity).
     * 2. **Memory Allocation**: The copy constructor defines a new buffer on the heap.
     * 3. **Memory Management**: Assignments may trigger deallocation of existing buffers and
     * allocation of new ones. Net Result: 3 potential heap allocations and 3 full data copies,
     * compared to just swapping internal pointers.
     */
    cout << "Calling non-member function swap()\n";
    swap(s1, s2);
    cout << "s1: " << s1 << ", s2: " << s2 << endl << endl;

    /**
     * Member swap function
     * "s1.swap(s2);"
     * The `std::string` object acts as a "header" that manages the underlying data.
     * Swapping is efficient (O(1) constant time) because we only swap these headers:
     * - The pointers to the character buffers.
     * - The size and capacity members.
     * The actual data on the heap is not copied or moved; only ownership is transferred.
     */
    cout << "Calling member function swap()\n";
    s1.swap(s2);
    cout << "s1: " << s1 << ", s2: " << s2 << endl << endl;
}
