#include <iostream>

using namespace std;

class Test {
  public:
    // Default constructor
    Test() = default;

    /**
     * Here, we did not define the copy constructor and copy assignment operator.
     * The compiler will synthesize them as deleted automatically.
     *
     * Copy constructor
     * Test(const Test&other) = delete;
     *
     * Copy assignment operator
     * Test& operator =(const Test& other) = delete;
     *
     * The class should define its own copy constructor and copy assignment operator if it needs
     * them. Otherwise, the compiler will synthesize them as deleted. And the class will be
     * non-copyable or move-only.
     */

    // Move constructor
    Test(Test &&other) noexcept { cout << "Move constructor called" << endl; }

    // Move assignment operator
    Test &operator=(Test &&other) noexcept {
        cout << "Move assignment operator called" << endl;
        return *this;
    }
};

// g++ -std=c++20 -Wall -Wextra -pedantic 161-special_member_fns_in_c++11.cpp && ./a.out
int main() {
    Test test;                   // OK - uses default constructor
    Test test2(std::move(test)); // OK - uses move constructor
    test2 = std::move(test);     // OK - uses move assignment operator
    // Test test3(test);            // Error! Use of deleted function

    return 0;
}
