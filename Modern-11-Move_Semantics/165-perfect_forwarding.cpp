/**
 * Perfect Forwarding
 * A function that passes some or all of its arguments to another function is said to "forward"
 * them.
 * ```
 * void f(Test x) {
 *    g(x); // f() forwards the argument x to g()
 * }
 * ```
 *
 * With perfect forwarding, a function can forward its arguments while preserving their value
 * category (lvalue, rvalue, etc.) and cv-qualification (const, volatile, etc.).
 * - If x is modifiable in f(), then g() receives a modifiable argument.
 * - If x is immutable in f(), then g() receives an immutable argument.
 * - If x is moved into f()'s argument, then it will be moved into g()'s argument.
 */

#include <iostream>

using namespace std;

class Test {};

void g(Test &x) { cout << "Modifiable version of g called\n"; }

void g(const Test &x) { cout << "Immutable version of g called\n"; }

void g(Test &&x) { cout << "Move version of g called\n"; }

template <class T> void f(T &&x) { // rvalue instatiation of f()
    // x has a name and an address, so it is an lvalue
    g(x); // always calls the lvalue version of g()
}

template <class T> void f2(T &&x) {
    g(std::move(x)); // always calls the rvalue version of g()
}

/**
 * Now, the problem with f() and f2() is that they do not preserve the value category of their
 * argument x. Here comes perfect forwarding to the rescue.
 * The behaviour of `std::forward<T>(x)`:
 * - If x is of type T&, it will be left as an lvalue reference to T.
 * - If x is of type T or T&&, it will be cast to an rvalue reference to T.
 */
template <class T> void perfect_forward_f(T &&x) { g(std::forward<T>(x)); }

// g++ -std=c++20 -Wall -Wextra -pedantic 165-perfect_forwarding.cpp && ./a.out
int main() {
    Test x;
    const Test cx;

    cout << "Calling f() with lvalue argument\n";
    f(x);
    cout << "\nCalling f() with const lvalue argument\n";
    f(cx);
    cout << "\nCalling f() with rvalue argument\n";
    f(std::move(x));
    /**
     * Output:
     * Calling f() with lvalue argument
     * Modifiable version of g called
     *
     * Calling f() with const lvalue argument
     * Immutable version of g called
     *
     * Calling f() with rvalue argument
     * Modifiable version of g called
     *
     * Notice that in the last case, the modifiable version of g() is called instead of the move
     * version.
     */

    cout << "\n--------------------------------\n" << endl;

    cout << "Calling f2() with lvalue argument\n";
    f2(x);
    cout << "\nCalling f2() with const lvalue argument\n";
    f2(cx);
    cout << "\nCalling f2() with rvalue argument\n";
    f2(std::move(x));
    /**
     * Output:
     * Calling f2() with lvalue argument
     * Move version of g called
     *
     * Calling f2() with const lvalue argument
     * Immutable version of g called
     *
     * Calling f2() with rvalue argument
     * Move version of g called
     *
     * Now, the move version of g() is called when f2() is called with a moved argument. But the
     * lvalue argument also calls the move version of g(), which is not what we want.
     */

    cout << "\n--------------------------------\n" << endl;
    cout << "Calling perfect_forward_f with lvalue argument\n";
    perfect_forward_f(x);
    cout << "\nCalling perfect_forward_f with const lvalue argument\n";
    perfect_forward_f(cx);
    cout << "\nCalling perfect_forward_f with rvalue argument\n";
    perfect_forward_f(std::move(x));
}
