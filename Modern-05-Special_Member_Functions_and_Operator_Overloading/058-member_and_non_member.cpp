/**
 * Member and non-member Operators:
 * Most operators can be implemented as member functions or non-member functions.
 *
 * Usually, if you can, you should implement them as member functions because they have direct
 * access to the class's members.
 *
 * However, in some cases it is better to implement them as non-member functions. E.g., some
 * operators cannot be implemented as member functions.
 *
 * When to use member operators and when to use non-member operators?
 * 1. Operators which change the state of the object are best implemented as member functions.
 *     - Compound assignment operators like +=, -=, *=, /=.
 *     - increment ++, decrement --
 *
 * 2. Operators which are closely related to member types are best implemented as member functions.
 *     - dereference operator *
 *
 * 3. Some operators MUST be defined as member functions.
 *     - assignment operator =
 *     - subscript operator []
 *     - function call operator ()
 *     - arrow operator ->
 *
 * 4. Binary operators which might require a type conversion of either argument should be non-member
 * functions.
 *     - arithmetic operators +, -, *, /, %
 *     - relational operators ==, !=, <, >, <=, >=
 *     - bitwise operators &, |, ^, ~, <<, >>
 *     - equality operators ==, !=
 *
 * 5. Input/output operators <<, >> should be non-member functions.
 *
 */

#include <iostream>
#include <string>

using namespace std;

class String {
    string s;

  public:
    // Constructors
    String(const char *str) : s(str) {}
    String(const string &s) : s(s) {}

    // Member function
    String operator+(const String &arg) { return s + arg.s; }

    void print() { cout << s << endl; }
};

class String2 {
    string s;

  public:
    // Constructors
    String2(const char *str) : s(str) {}
    String2(const string &s) : s(s) {}

    friend String2 operator+(const String2 &arg1, const String2 &arg2);

    void print() { cout << s << endl; }
};

// Non-member function
String2 operator+(const String2 &arg1, const String2 &arg2) { return arg1.s + arg2.s; }

// g++ -std=c++20 -Wall -Wextra -pedantic 058-member_and_non_member.cpp && ./a.out
int main() {
    String h{"hello"}, w{"world"};
    String hw = h + w; // Calls h.operator + (w); OK
    cout << "hw:  ";
    hw.print();
    // String hi = "hello " + w; // Cannot call "hello".operator + (w); Compiler error!
    // hi.print();

    String2 h2{"hello"}, w2{"world"};
    String2 hw2 = h2 + w2; // Calls operator+(h2, w2); OK
    cout << "hw2: ";
    hw2.print();

    // The compiler will convert "hello" to String2 because it is a function argument.
    String2 hi2 = "hello" + w2; // Calls operator+(String2(h2), w2); OK
    cout << "hi2: ";
    hi2.print();
}
