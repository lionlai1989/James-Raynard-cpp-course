#include <iostream>

using namespace std;

class Test {
    string m_str;

  public:
    Test(const string &str) : m_str(str) {
        // Called when an lvalue is passed
        cout << "const string& constructor called\n";
    }
    Test(string &&str) : m_str(std::move(str)) {
        // Called when an rvalue is passed
        cout << "string&& constructor called\n";
    }
};

void g(string &x) { std::cout << "Modifiable version of g called\n"; }

void g(string &&x) { std::cout << "Move version of g called\n"; }

/**
 * The make_test() function template perfectly forwards its argument to both g() and
 * the Test constructor. This ensures that the right overloads are called based on
 * whether an lvalue or rvalue is passed to make_test().
 */
template <class T> Test make_test(T &&x) {
    g(std::forward<T>(x));

    // return by value. But NRVO (named return value optimization) will likely optimize away the
    // copy/move.
    return Test(std::forward<T>(x));
}

// g++ -std=c++20 -Wall -Wextra -pedantic 166-perfect_forwarding_practical.cpp && ./a.out
int main() {
    string hello{"Hello"};

    cout << "Calling make_test() with lvalue argument\n";
    Test t1 = make_test(hello);

    cout << "\n--------------------------------\n" << endl;

    cout << "Calling make_test() with rvalue argument\n";
    Test t2 = make_test(std::move(hello));
}
