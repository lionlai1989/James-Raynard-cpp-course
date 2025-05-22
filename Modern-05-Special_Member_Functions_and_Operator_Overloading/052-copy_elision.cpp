#include <iostream>

using namespace std;

class Test {
  public:
    Test() { cout << "Default constructor\n"; }
    Test(const Test &other) { cout << "Copy constructor\n"; } // Copy constructor with side effect
};

// Function returning a temporary object
Test func() { return Test(); }

// Function returning a local variable
Test func2() {
    Test test;
    return test;
}

// Function taking an argument by value
void func3(Test test) {}

// g++ -std=c++17 -fno-elide-constructors 052-copy_elision.cpp && ./a.out
// g++ -std=c++17 052-copy_elision.cpp && ./a.out
int main() {
    cout << "test1" << endl;
    Test test = func(); // How many times is "Copy constructor" printed out?
    /**
     * We should see 2 "Copy constructor" printed out. But due to copy elision, the compiler will optimize the code and
     * output no "Copy constructor" printed out. The reason is that copy elision has taken place, twice.
     * - The first time is when the copy of the temporary object into the funtion's return space has been elided.
     * - The second time is when the copy initialization of the variable test has been elided.
     *
     * It's also known as Return Value Optimization (RVO).
     */

    cout << "\ntest2" << endl;
    Test test2 = func2(); // How many times is "Copy constructor" printed out?

    cout << "\ntest3" << endl;
    func3(Test()); // How many times is "Copy constructor" printed out?
}
