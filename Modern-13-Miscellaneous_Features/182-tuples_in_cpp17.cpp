/**
 * Tuples in C++17
 */

#include <iostream> // cout
#include <string>   // string
#include <tuple>    // tuple, apply

using namespace std;

tuple<double, int, string> func() {
    /**
     * In C++11/14, we need to specify the type of the tuple.
     * tuple<int, double, string> tup{1, 2.0, "three"s};
     *
     * In C++17, we can use Constructor Template Argument Deduction (CTAD)
     */
    tuple tup{1, 2.0, "three"s};

    return tup; // Return the tuple from the function
}

void func2(int i, double d, string s) {
    cout << "i = " << i << ", d = " << d << ", s = " << s << endl;
}

struct Test {
    int i;
    double d;
    string s;
    Test(int i, double d, string s) : i(i), d(d), s(s) {}
    void print() { cout << "i = " << i << ", d = " << d << ", s = " << s << endl; }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 182-tuples_in_cpp17.cpp && ./a.out
int main() {
    /**
     * Use C++17 structured binding
     */
    auto [d, i, str] = func(); // Unpack the tuple in the caller

    cout << "The elements of the returned tuple are: " << d << ", " << i << R"(, ")" << str
         << R"(")" << endl;

    cout << "--------------------------------" << endl;

    /**
     * Unpacking tuple elements as function arguments
     */
    apply(func2, tuple(1, 2.0, "three"s)); // Calls func2(1, 2.0, "three"s);

    cout << "--------------------------------" << endl;

    /**
     * Unpacking tuple elements as constructor arguments
     */
    auto test = make_from_tuple<Test>(tuple(1, 2.0, "three"s)); // Calls Test(1, 2.0, "three"s);
    test.print();
}
