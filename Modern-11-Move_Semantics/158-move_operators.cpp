/**
 * Rvalue references and overloading:
 * We can overload a function so that it behaves differently depending on whether the argument is an
 * lvalue or an rvalue.
 *
 * void func(const MyClass &obj); // Called when argument is an lvalue
 * void func(MyClass &&obj); // Called when argument is an rvalue
 *
 * If we copy an rvalue which does not have a move constructor, the copy constructor will be called
 * instead.
 *
 * If we assign an rvalue object which does not have a move assignment operator, the copy assignment
 * operator will be called instead.
 */

#include <iostream> // cout

using namespace std;

class MyClass {};

class Test {
  private:
    int i{0};  // built-in type
    MyClass m; // class type

  public:
    /**
     * Because a copy constructor is defined by me, the compiler will not generate a default
     * constructor. Therefore, we need to define a default constructor.
     * This default constructor will call m's default constructor.
     */
    Test() = default;

    /**
     * Copy constructor
     */
    Test(const Test &arg) : i(arg.i), m(arg.m) { cout << "Copy constructor called" << endl; }

    /**
     * Move constructor
     * Notice that arg cannot be const because we are moving it which modifies the state of arg.
     * The move constructor should not throw any exceptions because there is no simple way to
     * recover from a partially moved object. Also, STL containers will only call an object's move
     * constructor if the object's move constructor is noexcept.
     *
     * Why use std::move(arg.m)? Because "arg.m" is an lvalue, and we need to cast it to an rvalue
     * so that the move constructor can be called.
     */
    Test(Test &&arg) noexcept : i(arg.i), m(std::move(arg.m)) {
        cout << "Move constructor called" << endl;
    }

    /**
     * Copy assignment operator
     */
    Test &operator=(const Test &arg) {
        cout << "Copy assignment operator called" << endl;
        if (this != &arg) {
            i = arg.i;
            m = arg.m;
        }
        return *this;
    }

    /**
     * Move assignment operator
     * Notice that arg cannot be const because we are moving it which modifies the state of arg.
     * The move assignment operator should not throw any exceptions because there is no simple way
     * to recover from a partially moved object. Also, STL containers will only call an object's
     * move assignment operator if the object's move assignment operator is noexcept.
     */
    Test &operator=(Test &&arg) noexcept {
        cout << "Move assignment operator called" << endl;
        if (this != &arg) {
            i = arg.i;
            m = std::move(arg.m); // Force move assignment operator to be called
        }
        return *this;
    }
};

// g++ -std=c++20 -Wall -Wextra -pedantic 158-move_operators.cpp && ./a.out
int main() {
    Test test; // Call default constructor
    cout << "Copying: ";
    Test test2 = test; // Call copy constructor
    cout << "\nMoving temporary: ";
    Test test3 = Test(); // Call move constructor by using temporary object
    cout << "\nMoving rvalue: ";
    Test test4(std::move(test)); // Call move constructor by casting test to rvalue

    cout << "--------------------------------" << endl;

    Test test5;
    cout << "\nAssigning: ";
    test5 = test2; // Call copy assignment operator

    Test test6;
    cout << "\nAssigning from temporary: ";
    test6 = Test(); // Call move assignment operator
}
