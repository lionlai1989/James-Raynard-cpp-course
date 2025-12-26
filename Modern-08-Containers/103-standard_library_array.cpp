/**
 * Containers:
 *
 * - Sequential containers: The order of elements depends on the sequence of insertion, not on their
 * values. Examples include std::vector, std::array, std::string, std::list, and std::deque.
 *
 * - Associative containers: The order of elements depends on their values (keys). Elements are
 * automatically sorted. Fast lookup via keys is supported. Since the position is determined by the
 * key, specific position insertion (like push_back) is not applicable. Examples include std::set,
 * std::map, std::multiset, and std::multimap.
 *
 * - Container adaptors: These provide a restricted interface to an underlying sequence container to
 * implement specific data structures. Examples include std::stack (LIFO), std::queue (FIFO), and
 * std::priority_queue.
 */

/**
 * Built-in array vs std::array
 *
 * C++ has a built-in array inherited from C:
 * ```cpp
 * int arr[] = {1, 2, 3, 4, 5};
 * ```
 *
 * Drawbacks of C arrays:
 * - No direct way to find the number of elements (often requires sizeof tricks).
 * - Silent conversion (decay) to pointers, losing size information.
 * - Passing arrays to functions is error-prone and often requires a separate size parameter.
 * - Arrays cannot be directly assigned or copied.
 *
 * Modern C++ introduces std::array, which resolves these issues while maintaining the performance
 * of C-style arrays.
 * An std::array object can only be created on the stack. The number of elements must be known at
 * compile time. A contiguous block of memory is allocated to store the elements.
 */

#include <array>    // array
#include <iostream> // cout, endl

using namespace std;

// Function that takes built-in array as pointer to int
// n is the number of elements in the array
void somefunc(int *pi, int n) {
    for (int i = 0; i < n; ++i)
        cout << pi[i] << ", ";
    cout << endl;
}

// Function that takes std::array of 5 elements
void somefunc(array<int, 5> arr) {
    for (auto el : arr)
        cout << el << ", ";
    cout << endl;
}

// g++ -std=c++17 -Wall -Wextra -pedantic 103-standard_library_array.cpp && ./a.out
int main() {
    // std::array can be list-initialized
    array<int, 5> arr{1, 2, 3, 4, 5};

    // Elements can be accessed and assigned to using indexing
    cout << "arr[3] = " << arr[3] << endl;

    arr[2] = 6;
    cout << "After assignment, arr[2] = " << arr[2] << endl;

    cout << "Iterator loop: ";
    for (auto it = begin(arr); it != end(arr); ++it) // Explicit iterator loop
        cout << *it << ", ";
    cout << endl;

    cout << "Range-for loop: ";
    for (auto el : arr) // Range-for loop
        cout << el << ", ";
    cout << endl;

    cout << "Indexed loop: ";
    for (size_t i = 0; i < arr.size(); ++i) // Indexed loop
        cout << arr[i] << ", ";
    cout << endl;

    // Arrays of the same type and size can be assigned
    std::array<int, 5> five_ints;
    five_ints = arr;

    cout << "Elements of five_ints: ";
    for (auto el : five_ints) // Range-for loop
        cout << el << ", ";
    cout << endl;

    cout << "Built-in C array\n";
    int c_arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(c_arr) / sizeof(c_arr[0]);
    somefunc(c_arr, n); // &pa[0] will be passed to function

    cout << "std::array\n";
    std::array<int, 5> std_arr{1, 2, 3, 4, 5};
    somefunc(std_arr);
}
