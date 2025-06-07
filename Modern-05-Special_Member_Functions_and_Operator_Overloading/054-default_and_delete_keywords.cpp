/**
 * Defaulted member functions
 * Modern C++ allows programmers to force the compiler to synthesize special member functions. This
 * is done by using "= default" after the function parameter list.
 *
 * Special member functions are synthesized as deleted:
 * Sometimes the compiler is not able to synthesize the default constructor, copy constructor with
 * "default". Usually this is the case when the class has a member that does not support it. If the
 * default version is not available, the compiler will synthesize a deleted version.
 */

#include <iostream>

using namespace std;

class Test {
  public:
    /**
     * It will force the compiler to synthesize the default constructor even if there are
     * other user-defined constructors in the class.
     * If this line is commented out, the compiler will not synthesize the default constructor.
     *
     */
    Test() = default;

    // User-defined copy constructor
    Test(const Test &other) { cout << "Copy constructor" << endl; }
};

class Test2 {
    /**
     * In traditional C++, we could prevent objects from being copied by make the copy constructor
     * and assignment operator private.
     *
     */

  private:
    Test2(const Test2 &other);            // Private copy constructor
    Test2 &operator=(const Test2 &other); // Private assignment operator

  public:
    Test2() {}
};

class Test3 {
    /**
     * In modern C++, we can do better than Test2 by using the delete keyword to prevent objects
     * from being copied.
     */

  public:
    Test3() = default; // Synthesized default constructor

    Test3(const Test3 &) = delete;            // Deleted copy constructor
    Test3 &operator=(const Test3 &) = delete; // Deleted assignment operator
};

// g++ -std=c++20 -Wall -Wextra -pedantic 054-default_and_delete_keywords.cpp && ./a.out
int main() {
    Test t1;
    Test t2(t1);

    Test2 t3, t4;
    // Test2 t(t3); // Error: copy constructor is private
    // t4 = t3;     // Error: assignment operator is private

    Test3 t5, t6; // Use defaulted constructor
    // Test3 t(t5);  // Error: use of deleted function
    // t6 = t5;      // Error: use of deleted function

    return 0;
}
