#include <iostream> // cout, endl
#include <string>   // string

using namespace std;

/**
 * TestImplicit class defines a conversion operator int() that converts an object of TestImplicit to
 * an int implicitly.
 */
class TestImplicit {
    int i{42};
    string str;

  public:
    // The conversion operator will be called whenever an Test object is used where an int is
    // expected.
    operator int() const {
        cout << "Implicit conversion operator int() called" << endl;
        return i;
    } // Implicit conversion operator to integer
};

/**
 * A conversion operator is defined as explicit. Implicit conversion will now cause compilation
 * error.
 */
class TestExplicit {
    int i{42};
    string str;

  public:
    explicit operator int() const {
        cout << "Explicit conversion operator int() called" << endl;
        return i;
    } // Explicit conversion operator to integer

    explicit operator bool() const {
        cout << "Explicit conversion operator bool() called" << endl;
        return i;
    } // Explicit conversion operator to bool
};

class Test {
    int i;

  public:
    /**
     * A constructor with a single argument acts as an implicit conversion operator.
     */
    Test(int i) : i(i) {}
};

class Test2 {
    int i;

  public:
    /**
     * We can make the constructor explicit to avoid the implicit conversion disaster in Test.
     */
    explicit Test2(int i) : i(i) {}
};

// g++ -std=c++20 -Wall -Wextra -pedantic 053-conversion_operators.cpp && ./a.out
int main() {
    TestImplicit test;

    /**
     * First compiler tries to find an exact match but there is no + operator defined for Test. Then
     * it tries to find a conversion operator that converts Test to int. To be honest, this feature
     * is quite confusing to me because I don't know when the conversion operator will be called by
     * the compiler.
     */
    int x = test + 5;
    cout << x << endl;

    /**
     * It first looks like that the left shift << operator is defined for Test. But it's not. So the
     * compiler will look for a conversion operator that converts Test to int. This is known as
     * implicit conversion.
     * Implicit conversion is often surprising to the programmer.
     */
    cout << test << endl;

    cout << "--------------------------------" << endl;

    /**
     * To avoid implicit conversion, we can make the conversion operator explicit.
     */
    TestExplicit test2;
    // cout << test2 << endl; // Error: no operator "<<" matches these operands
    cout << static_cast<int>(test2) << endl;

    cout << "--------------------------------" << endl;

    /**
     * The bool conversion operator is explicit and the following code does not cast. But the
     * compiler will call the explicit bool conversion operator implicitly anyway!? WTF?
     * C++ is fucking confusing.
     */
    if (test2) {
        cout << "This is allowed!" << endl;
    }

    cout << "--------------------------------" << endl;

    /**
     * The following code will compile but DO NOT DO THIS!
     */
    Test test3 = 4;

    // The following code will not compile because the Test2 constructor is explicit.
    // Test2 test4 = 4; Error! cannot implicitly convert int to Test2

    Test2 test4 = Test2{4}; // We must explicitly construct a Test2 object.

    return 0;
}
