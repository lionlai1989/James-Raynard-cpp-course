/**
 * Lvalue references:
 *    int x;
 *    int &lr = x; // lvalue reference
 * We cannot bind an lvalue reference to an rvalue.
 *     int &x = 3; // Error!
 * Unless the reference is const.
 *     const int &x = 3; // OK
 *
 * Rvalue references:
 * It's just a syntactic way to indicate that a function's argument must be a moveable rvalue.
 *     void func(int &&s);
 *     func(2); // OK
 *     int y = 2;
 *     func(y); // Error!
 *
 * There are 4 ways to pass an argument to a function:
 * 1. lvalue. func(int x):
 * - `func(x);` We can pass an lvalue and the function will make a copy of it.
 * - `func(2);` Or we can pass a moveable rvalue and now the function owns the passed object.
 *
 * 2. lvalue reference. func(int &x):
 * - `func(x);` We can pass an lvalue but not an rvalue.
 *
 * 3. const lvalue reference. func(const int &x):
 * - `func(x); func(2);` We can pass an lvalue or an rvalue.
 *
 * 4. rvalue reference. func(int &&x)
 * - `func(2);` We can pass a moveable rvalue but not an lvalue. The function will now own the passed object.
 *
 */

/**
 * Characteristics of lvalues:
 * lvalues represent persistent objects. They occupy memory (either on the stack or heap) which is accessible by the
 * programmer. They remain valid until they go out of scope or are deleted. They include:
 * - Local variables
 * - Global variables
 * - Static variables
 * - Function arguments
 *
 * Characteristics of rvalues:
 * rvalues are stored in locations that are not accessible by the programmer, such as processor registers. They are
 * temporary objects that are destroyed after the expression that creates them is evaluated.
 *
 * C++ has three "Value Categories":
 * - Literals: They have no name and can not be referred to again. They are called pure rvalues or "prvalues".
 * - Temporary objects: They represent an object and their data can be moved. They are called "xvalues" (eXpiring
 * values).
 * - lvalues: They are objects that have a name and can be referred to again.
 */
#include <iostream>
#include <string>

using namespace std;

void func(int &&x) { // func's argument is an "rvalue reference"
    cout << "Called with argument: " << x << endl;
}

void test(const string &s) { cout << "Lvalue reference version. " << s << endl; }

void test(string &&s) { cout << "Rvalue reference version. " << s << endl; }

// g++ -std=c++20 -Wall -Wextra -pedantic 156-lvalue_and_rvalue_references.cpp && ./a.out
int main() {
    func(2); // 2 is an rvalue. OK
    // int y{2};
    // func(y); // Error: y is an lvalue

    string l{string{"Perm"}};
    string &lr{l};

    cout << "Temporary object: ";
    test(string{"Temp"});

    cout << "Lvalue variable: ";
    test(l);

    cout << "Lvalue reference: ";
    test(lr);

    /**
     * If we want to pass an lvalue to a function that takes an rvalue reference, we must cast it to an rvalue.
     * std::move() does not move anything. All it does is cast an lvalue to an rvalue.
     * This will move the object "l" into the function argument.
     * After `l` is moved, `l`'s data may be empty or unusable. If we want to use `l` again, we must reassign its data.
     */
    cout << "std::move(): \n";
    test(std::move(l)); // l can no longer be used
    cout << "\n";

    /**
     * Although r is declared as an rvalue reference, it is actually an lvalue! Because r fulfills the definition of an
     * lvalue: it has an identity and a name.
     */
    string &&r{string{"Temp"}};
    cout << "Rvalue variable: ";
    test(r); // lvalue reference version is being called. What!
    cout << "std::move():\n";
    test(std::move(r));

    return 0;
}
