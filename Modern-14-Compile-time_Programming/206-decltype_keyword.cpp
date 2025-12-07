/**
 * decltype keyword
 * Review "Modern-12-Smart_Pointers/170-unique_pointers_and_custom_deleters.cpp" to see how decltype
 * is used to get the type of a lambda expression.
 *
 * - decltype can only be used at compile-time.
 * - decltype gives the type of its argument.
 *   - The argument must be a valid expression or an object.
 * - decltype does not evaluate its argument.
 * - decltype does not cause any code to be executed.
 * - The compiler will replace decltype(expression) with the type of the expression. E.g.:
 *   - `decltype(1+2) y;` // Declare variable y with the same type as (1+2).
 * - From a named variable, decltype yields the declared type of the variable. E.g.:
 *   - `int x; decltype(x) y;` // Declare variable y with the same type as x, which is int.
 *
 * decltype vs auto:
 * - auto deduces the type of a variable from its initializer. E.g.:
 *   - `auto x{42};` // x is deduced to be of type int.
 * - decltype gives the type of an expression or an object. E.g.:
 *   - `int x; decltype(x) y;` // y is of type int.
 * - Unlike auto, decltype retains constness and reference qualifiers. E.g.:
 *   - `const int cx;` // the tpe of cx is const int
 *   - `auto y = cx;` // y is deduced to be of type int.
 *   - `decltype(cx) z;` // z is of type const int.
 *
 * decltype with lvalues:
 * - decltype with lvalue named variables:
 *   ```
 *   int x = 42;          // x is an lvalue of type int
 *   decltype(x) y = x;   // y is of type int
 *   ```
 * - decltype with lvalue expressions:
 *   - The result is an lvalue reference to the expression's deduced type.
 *     ```
 *     int x, y;
 *     decltype(x + y) z; // z is of type int&
 *     ```
 *   - This includes variables inside `()`.
 *     ```
 *     int x;
 *     decltype((x)) y; // y is of type int&
 *     ```
 * decltype with rvalues:
 * - decltype with prvalue (pure rvalues). The result is the deduced type of the argument.
 *   ```
 *   decltype(42) x; // x is of type int
 *   ```
 * - decltype with xvalues (eXpiring values). The result is an rvalue reference to the deduced type.
 *   ```
 *   class Test {};
 *   decltype(Test()) y; // y is of type int&&
 *   ```
 */

#include <iostream>
#include <vector>

using namespace std;

class Test {};

template <typename T, typename U> auto add(T t, U u) -> decltype(t + u) {
    // Return the sum of two arguments of any type
    return t + u;
}

auto make_vector = [](auto x, size_t n) {
    // Return a vector of n elements, initialized with value x
    return vector<decltype(x)>(n, x);
};

// g++ -std=c++20 -Wall -Wextra -pedantic 206-decltype_keyword.cpp && ./a.out
int main() {
    const int x{42};
    auto y = x;       // The type of y is int
    decltype(x) z{0}; // The type of z is const int
    cout << "y = " << y << ", z = " << z << endl;
    ++y;
    // ++z;                     // error: increment of read-only variable ‘z’
    cout << "y = " << y << ", z = " << z << endl;

    int x2{42};
    // decltype with lvalue variable
    decltype(x2) y2{0}; // The type of y is int
    // decltype with lvalue expression
    decltype((x2)) p{x2}; // The type of p is lvalue reference to int
    // decltype with prvalue
    decltype(42) z2; // The type of z is int
    // decltype with xvalue expression
    decltype(Test()) t2; // The type of t is Test&&

    /**
     * decltype(auto):
     * This works like auto, but preserves constness and reference qualifiers like decltype.
     * ```
     * const int & a{99};    // The type of a is const int&
     * auto b = a;           // b is of type int
     * decltype(auto) c = a; // c is of type const int&
     * ```
     * But why not just do this?
     * ```
     * const int & a{99};
     * decltype(a) c = a;   // c is of type const int&
     * ```
     */
    const int a3{99};       // The type of a3 is const int
    auto b3 = a3;           // The type of b3 is int
    decltype(auto) c3 = a3; // The type of c3 is const int
    cout << "b3 = " << b3 << ", c3 = " << c3 << endl;
    ++b3;
    // ++c3; // error: increment of read-only variable ‘c3’
    cout << "b3 = " << b3 << ", c3 = " << c3 << endl;

    cout << "add(2, 3) => " << add(2, 3) << endl;
    cout << R"(add("Hello", 2) => )" << add("Hello", 2) << endl;

    cout << R"(make_vector(2, 3) => )";
    auto vint = make_vector(2, 3);
    for (auto i : vint)
        cout << i << ", ";
    cout << endl;

    cout << R"(make_vector("Hello", 2) => )";
    auto vstr = make_vector("Hello", 2);
    for (auto s : vstr)
        cout << s << ", ";
    cout << endl;
}
