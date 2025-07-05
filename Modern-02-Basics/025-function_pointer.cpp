/**
 * Function Pointer
 * A function's execution code is stored in memory. A function pointer is a variable that stores the
 * address of the function in memory.
 *
 * A function pointer is a callable object. It behaves like a variable and can be called like a
 * function.
 *
 * A function pointer is a "first class object":
 * - We can pass a function pointer as an argument to another function.
 * - We can return a function pointer from a call to another function.
 *
 */

#include <iostream>

using namespace std;

void func(int x, int y) { cout << x << " + " << y << " = " << x + y << endl; }

using pfunc = void (*)(int, int); // The * is NOT optional!
// typedef void (*)(int, int) pfunc; // older C++

void some_func(int x, int y, pfunc func_ptr) {
    (*func_ptr)(x, y); // Call the function by dereferencing the pointer

    func_ptr(x, y); // The * is optional
}

pfunc other_func() {
    // Return a pointer to the func function
    return &func;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 025-function_pointer.cpp && ./a.out
int main() {
    /**
     * func_ptr is a pointer to a function that takes two ints and returns void.
     */
    void (*func_ptr)(int, int) = &func;
    auto func_ptr2 = &func;
    auto func_ptr3 = func; // The & is optional. BETTER to KEEP the & for consistency

    // Call the function by dereferencing the pointer
    (*func_ptr)(1, 2);
    func_ptr(1, 2); // The * is optional. BETTER to KEEP the * for consistency
    func_ptr2(1, 2);
    func_ptr3(1, 2);

    cout << "--------------------------------" << endl;

    auto func_ptr4 = other_func();

    some_func(1, 2, func_ptr4);

    return 0;
}
