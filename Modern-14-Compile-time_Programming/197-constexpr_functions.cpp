/**
 * A constexpr function:
 * - Arguments are constant expressions
 * - The return value is a constant expression
 * - The function is evaluated at compile time
 *
 * constexpr functions are useful for performing compile-time computations. The evaluation is done
 * once so there is no runtime overhead.
 *
 * constexpr functions can contain multiple statements, variable declarations which must be
 * initialized with a constant and non-static local variables.
 *
 * However, the body of a constexpr function may not contain any code which causes an action at
 * runtime such as new/delete, calling virtual functions, or throwing exceptions.
 *
 * A member function of a class can be made constexpr which takes constant expressions as arguments
 * and returns a constant expression. This is a different concept from a member function which is
 * const (cannot modify the state, this, of the object).
 *
 * A constexpr member function is allowed to modify "this" unless the member function is declared
 * with the "const" keyword.
 *
 * "class" and "struct" can have constexpr data members, which are initialized from constant
 * expressions and cannot be modified. They must also be declared as static. Otherwise, the data
 * members will not be available at compile time.
 */

#include <iostream> // cout

using namespace std;

// constexpr function
constexpr double miles_to_km(double miles) {
    /**
     * A constexpr function cannot modify its arguments and cannot modify any global or static
     * variables.
     */
    return miles * 1.602;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 197-constexpr_functions.cpp && ./a.out
int main() {
    // The argument is a constant expression
    // The return value is a constant expression
    // The function is evaluated at compile time
    const double dist1 = miles_to_km(40);
    cout << "dist1: " << dist1 << endl;

    // The argument is not a constant expression
    // The return value is not a constant expression
    // The function is evaluated at run time
    double arg{40};
    double dist2 = miles_to_km(arg);
    cout << "dist2: " << dist2 << endl;

    /**
     * A constexpr function can be called with arguments that are not constant expressions. In this
     * case, the return value will not be a constant expression. If the return value is required to
     * be a constant expression, there will be an error.
     */

    // The argument is not a constant expression
    // The return value is not a constant expression
    // The return value is required to be a constant expression
    constexpr double dist3 = miles_to_km(40);
    // constexpr double dist4 = miles_to_km(arg); Error!

    cout << "dist3: " << dist3 << endl;

    return 0;
}
