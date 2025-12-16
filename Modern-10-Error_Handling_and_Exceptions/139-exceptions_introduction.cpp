/**
 * Error Codes and Exceptions
 * In C, the only way to communicate errors is to return error codes from functions. E.g.:
 * ```c
 * if (!file) return ERR_FILE_NOT_FOUND;
 * ```
 * Disadvantages of Error Codes:
 * - Make the code more complex
 * - Difficult to maintain
 * - Do not work well with callback functions
 * - C++ constructors cannot return error codes
 */

#include <iostream>
#include <vector>

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 139-exceptions_introduction.cpp && ./a.out
int main() {
    vector<int> vec;

    /**
     * The following line of code do not have any compile-time errors. It is undefined behaviour.
     *
     * Output:
     * Segmentation fault (core dumped)
     */
    // cout << vec[2] << endl;

    /**
     * Explain why the following try-catch block does NOT catch any exceptions.
     *
     * Explanation:
     * The subscript operator [] for std::vector does not perform bounds checking.
     * Accessing an element out of bounds using [] results in undefined behavior
     * (such as a segmentation fault or accessing arbitrary memory), but it does NOT
     * throw a C++ exception. Therefore, the catch block is never executed.
     * To get bounds checking and exceptions (std::out_of_range), use the .at() member function.
     */
    // try {
    //     cout << vec[2] << endl;
    // } catch (const std::exception &e) {
    //     cout << "Exception caught: " << e.what() << endl;
    // }

    /**
     * In contrast, the following line of code has a specific runtime error. The program will
     * terminate and print the error message.
     *
     * Output:
     * terminate called after throwing an instance of 'std::out_of_range'
     *   what():  vector::_M_range_check: __n (which is 2) >= this->size() (which is 0)
     * Aborted (core dumped)
     */
    // cout << vec.at(2) << endl;

    /**
     * The following try-catch block catches the exception by reference.
     * `vec.at(2)` throws an exception of type `std::out_of_range`.
     */
    try {
        cout << vec.at(2) << endl;      // Throws an exception
    } catch (const std::exception &e) { // Use dynamic binding.
        cout << "Exception caught: " << e.what()
             << endl; // Print out a description of the error condition
    }

    /**
     * The following try-catch block catches the exception by value.
     */
    try {
        cout << vec.at(2) << endl;     // Throws an exception
    } catch (const std::exception e) { // Use static binding.
        cout << "Exception caught: " << e.what()
             << endl; // Print out a description of the error condition
    }

    cout << "Finished!" << endl;
}