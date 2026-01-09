/**
 * Try-Catch Blocks
 * The exception handler should take the exception by reference. This allows polymorphism to work.
 * `what()` is a virtual member function. When `what()` is called, the most derived version of
 * `what()` is called.
 *
 * When the program is executing in a catch block, it may not be in a stable state. It should:
 * - Avoid allocating any new memory
 * - Avoid creating any new objects
 * - If possible, only use variables of built-in types
 * - Never do anything that might throw a new exception
 * - Keep the catch block as simple as possible
 */

#include <iostream>
#include <vector>

using namespace std;

// Function which throws an unhandled exception
void func(const vector<int> &vec) {
    cout << vec.at(2) << endl; // Throws an exception
}

// g++ -std=c++17 -Wall -Wextra -pedantic 140-try_catch_blocks.cpp && ./a.out
int main() {

    // Which catch block handles the exception?
    try {
        vector<int> vec;
        cout << vec.at(2) << endl; // May throw an exception of type std::out_of_range
    } catch (const exception &e) { // Will handle all sub-classes of std::exception
        cout << "std::exception\n";
    } catch (const out_of_range &e) { // Only handles exceptions of type std::out_of_range
        cout << "std::out_of_range\n";
    }

    cout << "--------------------------------" << endl;

    // Which catch block handles the exception?
    try {
        try {
            vector<int> vec;
            cout << vec.at(2) << endl; // Throws an exception
        } catch (const std::runtime_error &e) {
            cout << "Runtime error catch block\n";
            cout << "Exception caught: " << e.what() << endl;
        }
    } catch (const std::exception &e) { // Will handle all subclasses of std::exception
        cout << "std::exception catch block\n";
        cout << "Exception caught: " << e.what() << endl;
    }

    cout << "--------------------------------" << endl;

    // Catch any exceptions thrown by func()
    try {
        vector<int> vec;
        func(vec);
    } catch (const std::exception &e) {
        cout << "std::exception catch block\n";
        cout << "Exception caught: " << e.what() << endl;
    }
}
