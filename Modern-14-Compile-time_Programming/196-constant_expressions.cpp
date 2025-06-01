/**
 * A constant expression has a value that is evaluated at compile time.
 * - A literal
 * - A value computed from literals
 * - A value computed from other constant expressions
 */

#include <iostream> // cout

using namespace std;

// g++ -std=c++20 -Wall -Wextra -pedantic 196-constant_expressions.cpp && ./a.out
int main() {
    /**
     * A variable can be a constant expression if it's initialized by a constant expression and it cannot subsequently
     * be modified.
     */
    cout << "Constant expressions:" << endl;

    // i and j are constant expressions. i + j is also a constant expression.
    const int i{42}, j{99};

    // NB Compile with -pedantic with g++
    int arr[i + j]; // Array dimension MUST be a constant expression

    // x and y are not constant expressions. x + y is not a constant expression.
    int x{42}, y{99};

    // int arr2[x + y]; // Error! Array dimension is not a constant expression

    /**
     * constexpr vs const:
     * A const variable cannot be modified.
     * A constexpr variable has a value which is known at compile time and cannot be modified.
     */
    int input;
    cin >> input;
    const int input_const{input};
    // constexpr int input_const2{input}; // Error! We cannot know the value at compile time.
    constexpr int input_const2{42}; // OK! We know the value at compile time.

    return 0;
}
