/**
 * Lambda Expressions and Capture
 * A lambda expression has access to non-local (global) variables. It also has access to static
 * variables in the same scope.
 * By default, lambda expressions have very limited access to local variables:
 * - A lambda expression can access local variables which are references and were initialized with a
 *   constant expression
 * - A lambda expression can read, but not modify, local variables which are integers or enums and
 *   were initialized with a constant expression.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ge_n {
  private:
    const int n;

  public:
    ge_n(const int n) : n(n) {}

    bool operator()(const string &str) const { return str.size() > n; }
};

int global{99}; // Non-local variable

// g++ -std=c++17 -Wall -Wextra -pedantic 070-lambda_expressions_and_capture.cpp && ./a.out
int main() { // Scope containing the lambda expression

    static int answer{42}; // Static variable in containing scope
    const int one{1};      // Local variable in containing scope
    const int &r_one{one}; // Local variable in containing scope

    auto lambda = []() { // the lambda has no capture-default
        ;
        cout << global << endl; // Lambda body can access non-local variables

        cout << answer << endl; // Lambda body can access static variables

        cout << one << endl; // Lambda body can read local variables

        // cout << r_one << endl; // error: ‘r_one’ is not captured

    }; // End of lambda body

    lambda();

    cout << "--------------------------------" << endl;

    vector<string> words{"a", "collection", "of", "words", "with", "varying", "lengths"};

    // Find the first element with more than 5 characters
    auto res =
        find_if(cbegin(words), cend(words), [](const string &str) { return str.size() > 5; });
    if (res != cend(words)) {
        cout << R"(The first word which is more than 5 letters long is ")";
        cout << *res << R"(")" << endl;
    }

    cout << "--------------------------------" << endl;

    int n{5};
    // Find the first element with more than n characters
    auto res2 = find_if(
        cbegin(words), cend(words),
        [n](const string &str) { return str.size() > n; } // Lambda captures local variable n
    );
    if (res2 != cend(words)) {
        cout << R"(The first word which is more than )" << n << R"( letters long is ")";
        cout << *res2 << R"(")" << endl;
    }

    cout << "--------------------------------" << endl;

    /**
     * Lambda Capture Implementation
     * A lambda with capture is implemented as "functor with state":
     * - The functor has a private data member
     * - It is initialized in the functor's constructor
     * - The data member is available in the operator()
     *
     * By default, the captured variable is passed to the functor's constructor by value
     * By default, the data member is const.
     */
    // ge_n is a demonstration of a compiler's implementation of the lambda expression above.
    auto res3 = find_if(cbegin(words), cend(words), ge_n(n));
    if (res3 != cend(words)) {
        cout << R"(The first word which is more than )" << n << R"( letters long is ")";
        cout << *res3 << R"(")" << endl;
    }

    cout << "--------------------------------" << endl;

    // We want to find the index of the match
    int idx{-1}; // Add another variable for the index of the match

    // auto res4 = find_if(cbegin(words), cend(words), [n, idx](const string &str) {
    //     ++idx; // error: increment of read-only variable ‘idx’
    //     return str.size() > n;
    // });

    // The mutable keyword allows the lambda to modify its captured variables
    auto res4 = find_if(cbegin(words), cend(words), [n, idx](const string &str) mutable {
        ++idx;
        return str.size() > n;
    });
    if (res4 != cend(words)) {
        cout << R"(The first word which is more than )" << n << R"( letters long is ")";
        cout << *res4 << R"(")" << endl;
        cout << "The index is " << idx << ". Notice that it always prints -1. Explain why." << endl;
    }

} // End of scope containing the lambda expression
