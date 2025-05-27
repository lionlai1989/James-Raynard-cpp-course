#include <iostream>

using namespace std;

int func() { // Function returning reference to const int
    return 5;
}

// g++ -std=c++17 -Wall -Wextra -pedantic 019-auto_keyword.cpp && ./a.out
int main() {
    auto i{42};           // Type of i is deduced as int
    auto str1 = "Hello";  // Type of str1 is deduced as const char*
    auto str2 = "World"s; // Type of str2 is deduced as std::string

    /**
     * Sometimes it is not easy to work out the type of a variable.
     * In modern C++, there are even situations in which it is impossible to know the type of a variable.
     */
    cout << "i * 2 = " << i * 2 << endl;
    cout << "*str1 = " << *str1 << endl;
    auto it = str2.begin(); // auto deduced as vector<char>::iterator
    cout << "First element of str2: " << *it << endl;

    cout << "--------------------------------" << endl;

    /**
     * auto will only give the underlying type of the variable. const, volatile, reference, etc. are not included.
     */
    const int &x{6};
    auto y = x;        // y is a normal int, not a const int
    const auto &z = x; // z is a const int
    ++y;
    // ++z; // This will cause a compilation error

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;

    cout << "--------------------------------" << endl;

    auto r = func(); // r has type int
    cout << r << endl;
}
