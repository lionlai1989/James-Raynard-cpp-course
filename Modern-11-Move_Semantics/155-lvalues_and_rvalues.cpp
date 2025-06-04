/**
 * C++ often uses value semantics, in which data is copied in:
 * Function calls:
 *     By default, function arguments are passed by value.
 *     By default, functions return by value.
 *
 * STL containers copy data into their elements.
 *
 * Value semantics avoid the need for a garbage collector.
 *
 * In C++, an object can be either an lvalue or an rvalue.
 * An lvalue represents a named memory location. It has a name and we can take its address using the
 * & operator. And everything that is not an lvalue is an rvalue.
 *
 * x = 2; // x is an lvalue, 2 is an rvalue
 * x = func(); // x is an lvalue, return value of func() is an rvalue
 *
 * lvalues and rvalues can behave differently when passed to functions.
 *
 * Pass value of a variable:
 *
 * void func(int);
 * int x = 2;
 * func(x); // Pass lvalue
 * func(2); // Pass rvalue
 *
 * Pass address of a variable:
 *
 * void func(int*);
 * int x = 2;
 * func(&x); // Pass lvalue
 * func(&2); // Pass rvalue. Error!
 *
 * Passing address of a variable or non-const reference to a function usually means that the
 * function will modify the value of the variable. It makes no sense to pass an rvalue to such a
 * function. Thus, it's not allowed.
 *
 * In C++11, the argument can be moved if an object is an rvalue and type if "moveable".
 * An object will be copied if it's an lvalue or type is not "moveable".
 */

#include <iostream>

using namespace std;

int get() { return 2; } // Function returning an int

void func(const int &ri) { // Function taking int by const reference
    cout << ri << endl;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 155-lvalues_and_rvalues.cpp && ./a.out
int main() {
    func(get()); // Return value from get() is an rvalue
                 // The rvalue is passed by const reference
}
