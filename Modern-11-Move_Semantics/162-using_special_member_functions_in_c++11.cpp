#include <iostream>

using namespace std;

class Test {
  public:
    // Default constructor
    Test() = default;

    /**
     *  The copy operators are declared as deleted
     */
    // Copy constructor
    Test(const Test &other) = delete;
    // Copy assignment operator
    Test &operator=(const Test &other) = delete;

    /**
     * The compiler does not generate any move operators.
     *
     * Move constructor and move assignment are not implicitly declared if we explicitly declare
     * any copy operation (even if = delete).
     */
};

class Test2 {
  public:
    // Default constructor
    Test2() = default;

    // Copy constructor
    Test2(const Test2 &other) { cout << "Copy constructor called" << endl; }

    // Copy assignment operator
    Test2 &operator=(const Test2 &other) {
        cout << "Copy assignment operator called" << endl;
        return *this;
    }

    // The move operators are declared as deleted
    Test2(Test2 &&other) noexcept = delete;

    // Move assignment operator
    Test2 &operator=(Test2 &&other) noexcept = delete;
};

// g++ -std=c++20 -Wall -Wextra -pedantic 162-using_special_member_functions_in_c++11.cpp && ./a.out
int main() {
    Test test; // OK - uses default constructor

    // Test test2(std::move(test)); // Error! Use of deleted function
    // Test test3(test); // Error! Use of deleted function

    cout << "\n--------------------------------\n" << endl;

    Test2 test2; // OK - uses default constructor
    // Test2 test3(std::move(test2)); // Does not fall back to copy operator
    Test2 test4(test2); // OK - uses copy constructor
}