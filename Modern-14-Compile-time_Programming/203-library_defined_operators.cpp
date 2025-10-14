/**
 * Library-defined Operator Objects
 * C++11 defines several generic operator classes in the <functional> header. E.g., `less<T>`
 * operator calls the `<` operator of type T.
 *  - Arithmetic: plus, minus, multiplies etc.
 *  - Comparison: equal_to, not_equal_to, less_equal etc.
 *  - Logical: logical_and, logical_or, logical_not etc.
 *  - Bitwise: bit_and, bit_or, bit_xor etc.
 * The above operator classes are function objects (functors) that overload the `operator()`. Thus,
 * we need to create an instance of the class and call the `operator()`.
 * ```
 *     less()(t1, t2); // calls t1 < t2
 * ```
 *
 * We can use these operator classes as default template parameters for function templates.
 *
 */

#include <functional>
#include <iostream>

using namespace std;

// Function template with parameter T and Func
// If caller does not provide a callable object, use T's operator <
template <typename T, typename Func = less<T>>
bool compare(const T &t1, const T &t2, Func f = Func()) {
    // f is a callable object. The default is less<T>.
    return f(t1, t2);
}

// g++ -std=c++20 -Wall -Wextra -pedantic 203-library_defined_operators.cpp && ./a.out
int main() {
    int x{1}, y{2};
    cout << "x = " << x << ", y = " << y << endl;

    auto b = compare(x, y, [](int i1, int i2) { return i1 > i2; }); // Pass a callable object
    cout << "Result of calling compare with lambda: " << boolalpha << b << endl;

    auto b2 = compare(x, y); // Use default less<int>
    cout << "Result of calling compare with default: " << boolalpha << b2 << endl;
}