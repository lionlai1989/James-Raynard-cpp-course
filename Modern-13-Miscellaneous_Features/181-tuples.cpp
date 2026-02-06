/**
 * std::pair vs std::tuple
 *
 * std::pair is a compound type which has two elements of any type, accessed via .first and .second.
 * std::tuple is similar to std::pair, but can have any fixed number of elements. Elements are
 * accessed via `std::get<index>(tuple)`.
 *
 * When to use std::tuple?
 * - Useful as an ad-hoc data type
 * - When we want somewhere to store data in the short term that
 *   - Doesn't need member functions
 *   - Doesn't need to be reused
 *   - Has elements of different types
 *
 * Returning multiple values from a function:
 * Traditionally we would construct a struct or class to return multiple values from a function
 * call. However, this can be verbose and unnecessary for simple cases.
 */

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

tuple<double, int, string> func() {
    return {1.0, 2, "Three"s}; // Return the tuple from the function
}

// g++ -std=c++17 -Wall -Wextra -pedantic 181-tuples.cpp && ./a.out
int main() {
    // We can create a tuple instance explicitly
    tuple<double, int, string> numbers(1.0, 2, "Three"s);

    // Or use make_tuple() to create a tuple instance
    // auto numbers{make_tuple(1.0, 2, "Three"s)};

    cout << "First element is " << get<0>(numbers) << endl;

    cout << "Setting second element to 3" << endl;
    get<1>(numbers) = 3; // Set second element to 3

    // C++14 allows us to use the type as the parameter, if unique
    cout << "Value of int element is " << get<int>(numbers) << endl;

    cout << "--------------------------------" << endl;

    /**
     * A tuple can be unpacked into individual variables using `std::tie`.
     */

    double d;
    int i;
    string str;

    tie(d, i, str) = numbers; // Store all elements in variables

    cout << "Tuple elements are: " << d << ", " << i << R"(, ")" << str << R"(")" << endl;

    cout << "--------------------------------" << endl;

    tie(d, i, str) = func(); // Unpack the tuple in the caller

    cout << "Elements of returned tuple are: " << d << ", " << i << R"(, ")" << str << R"(")"
         << endl;
}
