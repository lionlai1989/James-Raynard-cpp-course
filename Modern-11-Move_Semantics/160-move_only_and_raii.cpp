/**
 * Move-only class:
 * We can make a class move-only by deleting the copy constructor and copy assignment operator.
 *
 * class Test{
 *   public:
 *     Test(const Test &) = delete; // Delete copy constructor
 *     Test &operator=(const Test &) = delete; // Delete copy assignment operator
 *
 *     Test(Test &&) noexcept; // Implement move constructor
 *     Test &operator=(Test &&) noexcept; // Implement move assignment operator
 *     ...
 * };
 *
 * In standard library, there are some move-only classes.
 * - fstream, iostream
 * - classes used in multithreading
 * - smart pointers classes
 * There types follow the RAII idiom.
 * - Only one object can own a given resource instance at a time
 * - The object acquires ownership of the resource in the constructor
 * - The object releases ownership of the resource in the destructor
 *
 * The ownership of the resource can be transferred from one object to another using move semantics.
 *
 * Here is an example of a move-only class, fstream.
 * fstream has a file handle as a data member. The fstream constructor opens the file and the
 * destructor closes the file. An fstream object cannot be copied, but it can be moved.
 * - The moved-from object no longer owns the file handle. I.e., it has a null file handle.
 * - The moved-to object now becomes the owner of the file handle. The file will
 *
 *
 * Lambda capture and move-only objects:
 * C++11 lambda expression are not good at capturing move-only objects. E.g.,
 *
 * fstream fs("file.txt");
 *
 * What syntax should we use to capture the file handle, fs?
 *
 * [fs] // Capture by value. ERROR! Does not compile.
 * [&fs] // Capture by reference. Can compile, but no transfer of ownership.
 *
 * In C++14, it has "generalized" lambda capture.
 * A variable in the outer scope can be moved into a lambda-local variable.
 *
 * fstream fs("file.txt");
 * [local_fs = std::move(fs)] { // Capture by move
 *   // local_fs is now a lambda-local variable.
 *   // The original fs is moved-from.
 *   // local_fs is the owner of the file handle.
 * }();
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MyClass {
  public:
    MyClass() = default;
    MyClass(const MyClass &) = default;
    MyClass &operator=(const MyClass &) = default;
    MyClass(MyClass &&) = default;
};

class Test {
  private:
    int i{0};
    MyClass m;

  public:
    Test() = default;

    Test(const Test &) = delete;            // Delete copy constructor
    Test &operator=(const Test &) = delete; // Delete copy assignment operator

    Test(Test &&arg) noexcept : i(arg.i), m(std::move(arg.m)) {
        cout << "Move constructor called" << endl;
    }

    Test &operator=(Test &&arg) noexcept {
        cout << "Move assignment operator called" << endl;

        if (this != &arg) {
            i = arg.i;
            m = std::move(arg.m); // Force move assignment operator to be called
        }
        return *this;
    }
};

// g++ -std=c++20 -Wall -Wextra -pedantic 160-move_only_and_raii.cpp && ./a.out
int main() {
    cout << "Constructing: " << endl;

    Test test; // Call default constructor

    // Test test2 = test; // ERROR! Copy constructor is deleted

    cout << "Moving temporary: " << endl;
    // Pay attention to the output. This statement is optimized out by the compiler.
    Test test3 = Test(); // Call move constructor by using temporary object

    cout << "Moving rvalue: " << endl;
    Test test4(std::move(test)); // Call move constructor by casting test to rvalue

    cout << endl;

    cout << "Assigning: " << endl;

    Test test5;
    // test5 = test; // ERROR! Copy assignment operator is deleted

    Test test6;
    cout << "Assigning from temporary: " << endl;
    test6 = Test(); // Call move assignment operator

    Test test7;
    cout << "Assigning from rvalue: " << endl;
    test7 = std::move(test6); // Call move assignment operator

    cout << "\n--------------------------------\n" << endl;

    Test test8;

    // We cannot capture test8 by value.
    // [test8]() { cout << "Lambda capturing by value\n"; }(); // ERROR! Copy constructor is deleted

    // Can we capture test8 by reference. Yes. But no transfer of ownership.
    [&test8]() { cout << "Lambda capturing by reference\n"; }();

    // In C++14, we can capture test8 by move.
    [local_test8 = std::move(test8)]() { cout << "Lambda capturing by move\n"; }();

    cout << "\n--------------------------------\n" << endl;

    vector<string> strings(5);

    cout << "Capture by reference" << endl;
    [&strings]() { cout << "Size in lambda = " << strings.size() << endl; }();
    cout << "After calling lambda, size in main = " << strings.size() << endl;

    cout << endl << "Capture by move" << endl;
    [vs = std::move(strings)]() { cout << "Size in lambda = " << vs.size() << endl; }();
    cout << "After calling lambda, size in main = " << strings.size() << endl << endl;

    return 0;
}
