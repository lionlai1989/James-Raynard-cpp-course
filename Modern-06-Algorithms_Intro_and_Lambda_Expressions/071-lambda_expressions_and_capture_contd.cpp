/**
 * Lambda Expressions and Capture by Reference
 * A lambda with capture-by-reference is also implemented as a "functor with state".
 * However, the private data member is a reference to the captured variable.
 *
 * Implicit Capture
 * A lambda can capture all the variables in the enclosing scope by value or by reference.
 * We can use the following syntax:
 * - [] : capture nothing
 * - [=] : capture all variables by value
 * - [&] : capture all variables by reference
 *
 * Capturing all local variables by refernece can make the code difficult to maintain and dangerous
 * because the lambda body could modify any variable in scope.
 * Usually, it is better to explicitly capture the variables by reference that the lambda needs to
 * alter.
 * [=, &var1, &var2, ...] : capture all variables by value, except var1, var2, ... which are
 * captured by reference.
 * [&, =var1, =var2, ...] : capture all variables by reference, except var1, var2, ... which are
 * captured by value.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ge_n {
  private:
    const int n;
    int &idx;

  public:
    ge_n(const int n, int &idx) : n(n), idx(idx) {}

    bool operator()(const string &str) const {
        ++idx;
        return str.size() > n;
    }
};

/**
 * Lambda Functions and Member Functions
 * A member function is called with an extra argument which is a pointer to the class instance it is
 * being called on.
 * ```
 * test.do_it()
 * // Called as Test::do_it(&test)
 * // &test is available in the member function body as "this"
 * ```
 * In effect, `this` is a variable in the scope of the member function.
 * When we have a lambda expression inside a member function, we can capture `this` by reference
 * using `[this]`. This allows the lambda expression to access data members and member functions
 * of the class.
 */
class Test {
  private:
    int time{10}; // Data member

  public:
    void countdown() { // Member function which calls a lambda expression

        // Capture class object by reference. [=this] and [&this] are not allowed.
        [this]() {
            // time is captured by reference
            if (this->time > 0)
                cout << this->time << endl;
            else if (this->time == 0)
                cout << "Liftoff!" << endl;
            --this->time;
        }(); // Call the lambda function
    }
};

/**
 * Capture by Value
 * If we want to capture the class object by value, we can use the following syntax:
 * [*this]
 * This will create a copy of the class object and capture it by value.
 */
class Test2 {
  private:
    int time{10}; // Data member

  public:
    void countdown() { // Member function which calls a lambda expression

        // Capture class object by value. By default, the lambda is const. We need to
        // add mutable to modify the captured object.
        [*this]() mutable {
            if (this->time > 0)
                cout << this->time << endl;
            else if (this->time == 0)
                cout << "Liftoff!" << endl;

            // It modifies the copy of the class object, not the one in main(), `test2`.
            --this->time;
        }(); // Call the lambda function
    }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 071-lambda_expressions_and_capture_contd.cpp && ./a.out
int main() {
    vector<string> words{"a", "collection", "of", "words", "with", "varying", "lengths"};

    int max{5}, idx{-1};

    // Capture max by value, idx by reference
    auto res = find_if(cbegin(words), cend(words), [max, &idx](const string &str) {
        ++idx;
        return str.size() > max;
    });
    if (res != cend(words)) {
        cout << R"(The first word which is more than )" << max << R"( letters long is ")";
        cout << *res << R"(")" << endl;
        cout << "Its index is " << idx << endl;
    }

    cout << "--------------------------------" << endl;

    int idx2{-1};
    // demonstrate a compiler's implementation of the lambda expression above.
    auto res2 = find_if(cbegin(words), cend(words), ge_n(max, idx2));
    if (res2 != cend(words)) {
        cout << R"(The first word which is more than )" << max << R"( letters long is ")";
        cout << *res2 << R"(")" << endl;
        cout << "Its index is " << idx2 << endl;
    }

    cout << "--------------------------------" << endl;

    Test test;
    for (int i = 0; i < 12; ++i)
        test.countdown();

    cout << "--------------------------------" << endl;

    Test2 test2;
    for (int i = 0; i < 12; ++i)
        test2.countdown();
}
