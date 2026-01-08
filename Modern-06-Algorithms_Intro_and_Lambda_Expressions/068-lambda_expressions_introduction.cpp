/**
 * Lambda Expressions Introduction
 * - Can be thought of as an anonymous function
 * - Similar to "closures" in other languages
 * - When the compiler encounters a lambda expression, it will generate code that defines a function
 *   object (a.k.a. "functor"). This functor will have a unique name chosen by the compiler and is
 *   defined inline. The function call operator of the functor will have the same body as the lambda
 *   expression. It will have the same return type as the lambda expression.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Define a functor for the predicate
class is_odd {
  public:
    bool operator()(const int n) const { return (n % 2 == 1); }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 068-lambda_expressions_introduction.cpp && ./a.out
int main() {
    vector<int> vec{3, 1, 4, 1, 5, 9};

    // Pass a functor object
    auto odd_it = find_if(cbegin(vec), cend(vec), is_odd());
    // odd_it will be an iterator to the first odd element (if there is one)
    if (odd_it != cend(vec))
        cout << "First odd element is: " << *odd_it << endl;

    // Pass a lambda expression
    auto odd_it2 = find_if(cbegin(vec), cend(vec), [](int n) { return (n % 2 == 1); });
    // odd_it will be an iterator to the first odd element (if there is one)
    if (odd_it2 != cend(vec))
        cout << "First odd element is: " << *odd_it2 << endl;
}
