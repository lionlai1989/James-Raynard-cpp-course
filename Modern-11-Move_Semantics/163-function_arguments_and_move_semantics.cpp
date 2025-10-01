/**
 * Function Arguments and Move Semantics
 *
 * 1. Pass by value
 *  - Copy constructor is called
 *  - Function has its own copy of the caller's object
 *  - Caller's object is unmodified
 *
 * 2. Pass by const reference
 *  - Function has read-only access to the caller's object
 *  - Caller's object is unmodified
 *
 * 3. Pass by non-const reference or pass by address
 *  - Function has read-write access to the caller's object
 *  - Caller's object can be modified
 *
 * 4. Pass by move
 *  - Move constructor is called
 *  - Function takes ownership of the caller's object
 *  - Caller's object is left in a valid but unspecified state
 *
 * In older C++ standards (pre C++11), the convention was to pass objects by value if objects were
 * built-in types (int, char, double, etc.) or small structs (typically less than 16 bytes). Larger
 * structs and classes were passed by const reference to avoid the overhead of copying.
 *
 * Does this convention still hold in modern C++ with move semantics?
 *
 * Let's consider a class which contains a std::string member. And we want to initialize this
 * std::string member using both lvalues and rvalues.
 * What is the most efficient way to do this?
 *
 * ```
 * class Test {
 *     string m_str;
 *   public:
 *     Test(???) : m_str(???) {}
 * };
 * ```
 *
 *
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * Pass by const reference
 * - The argument is bound to the passed lvalue or rvalue
 * - The argument is copied into the data member
 */
class Test {
    string m_str;

  public:
    Test(const string &str) : m_str(str) {}
};

/**
 * Pass by value or move
 * - Lvalues are passed by copy
 * - Rvalues are passed by move
 * - The argument is copied into the data member
 */
class Test2 {
    string m_str;

  public:
    Test2(string str) : m_str(str) {}
};

/**
 * Pass by value and move
 * - Lvalues are passed by copy
 * - Rvalues are passed by move
 * - The `str` argument in the constructor is a copy of the caller's object so we can actually do
 *   whatever we want with it. We can move it into the data member to avoid an unnecessary copy.
 */
class Test3 {
    string m_str;

  public:
    Test3(string str) : m_str(std::move(str)) {}
};

/**
 * Pass by rvalue reference
 * - Lvalues cannot be bound to an rvalue reference
 * - Rvalues are passed by move
 */
class Test4 {
    string m_str;

  public:
    Test4(string &&str) : m_str(std::move(str)) {}
};

/**
 * After considering all the above options, the best way is to write 2 constructors
 */
class Test5 {
    string m_str;

  public:
    // Called when an lvalue is passed
    Test5(const string &str) : m_str((str)) {}

    // Called when an rvalue is passed
    Test5(string &&str) : m_str(std::move(str)) {}
};

// g++ -std=c++20 -Wall -Wextra -pedantic 163-function_arguments_and_move_semantics.cpp && ./a.out
int main() {
    string name;
    Test ltest(name);            // Lvalue passed - str binds to name. str is copied into m_str
    Test rtest(std::move(name)); // Rvalue passed - str binds to name. str is copied into m_str

    cout << "\n--------------------------------\n" << endl;

    string name2;
    Test2 ltest2(name2); // Lvalue passed - name2 is copied into str. str is copied into m_str
    Test2 rtest2(
        std::move(name2)); // Rvalue passed - name is moved into str. str is copied into m_str

    cout << "\n--------------------------------\n" << endl;

    string name3;
    Test3 ltest3(name3); // Lvalue passed - name is copied into str. str is moved into m_str
    Test3 rtest3(
        std::move(name3)); // Rvalue passed - name is moved into str. str is moved into m_str

    cout << "\n--------------------------------\n" << endl;

    string name4;
    // Test4 ltest(name);            // Compiler error
    Test4 rtest4(std::move(name4)); // Rvalue passed - str binds to name. str is moved into m_str

    cout << "\n--------------------------------\n" << endl;

    string name5;
    Test5 ltest5(name5);            // Lvalue passed - str binds to name. str is copied into m_str
    Test5 rtest5(std::move(name5)); // Rvalue passed - str binds to name. str is moved into m_str
}