/**
 * Compile-time Programming
 * compile-time programming is a programming paradigm that allows the programmer to write code that is executed at
 * compile time. The result of the computation is available in the program and no runtime overhead is incurred.
 */
#include <iostream>    // cout
#include <type_traits> // is_arithmetic, is_floating_point, is_class, is_pointer

using namespace std;

// The max macro is problematic because it evaluates the arguments multiple times.
#define Max(x, y) ((x) > (y) ? (x) : (y))

class A {};

// g++ -std=c++20 -Wall -Wextra -pedantic 195-compile_time_programming.cpp && ./a.out
int main() {
    int a{5}, b{2};
    cout << "a = " << a << ", b = " << b << endl;
    cout << "Max(a, b): " << Max(a, b) << endl;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "Max(a++, b): " << Max(++a, b) << endl; // Replaced by ((++a) > (b) ? (++a) : (b))
    cout << "a = " << a << ", b = " << b << endl;   // a may be incremented twice

    cout << boolalpha;
    cout << "is_arithmetic<int>: " << is_arithmetic<int>::value << '\n';             // true
    cout << "is_floating_point<int>: " << is_floating_point<int>::value << '\n';     // false
    cout << "is_class<A>: " << is_class<A>::value << '\n';                           // true
    cout << "is_pointer<const char *>: " << is_pointer<const char *>::value << '\n'; // true
}
