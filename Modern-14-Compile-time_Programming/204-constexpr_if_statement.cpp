#include <iostream>
#include <string>
#include <type_traits>

using namespace std; // For brevity in this example

/**
 * The reason why get_string() does not compile is that both branches of the runtime `if` statement
 * are instantiated during template compilation, regardless of the condition. When T is `int`, the
 * compiler tries to compile `return arg;` (which fails because arg is int, not string). When T is
 * `std::string`, the compiler tries to compile `return to_string(arg);` (which fails because
 * to_string() doesn't accept string arguments).
 *
 * The problem is that all the branches of a regular `if` statement must compile, even if they are
 * not executed at runtime.
 *
 * Solution: Use `if constexpr` instead. The compiler will discard the unused branch at
 * compile-time, so only valid code is instantiated for each template specialization.
 */
template <typename T> string get_string(const T &arg) {
    if (std::is_same_v<std::string, T>) // Replaced by "true" if T is a string, else "false"
        return arg;                     // Error if T is a built-in type
    else
        return to_string(arg); // Error if T is std::string
}

/**
 * With `if constexpr`, only the relevant branch is compiled.
 *
 * Why `if constexpr` is the best choice for this scenario:
 * - Simplicity: Single template definition instead of multiple specializations
 * - Readability: Logic is clear and localized in one place
 * - Maintainability: Changes to either branch don't require managing separate templates
 * - Modern C++: Idiomatic C++17+ approach (cleaner than SFINAE or explicit specialization)
 * - Compile-time decision: The condition is evaluated at compile-time, unused branches are
 *   discarded completely, resulting in no overhead compared to hand-written specializations
 * - Flexibility: Can have multiple conditions and complex branching logic within one template
 *
 * Comparison:
 * - if constexpr: Simple, readable, one template → PREFERRED ✓
 * - Template specialization: Requires multiple definitions, order-dependent → Pre-C++17 workaround
 * - SFINAE: Complex syntax, harder to understand, verbose → Rarely needed nowadays
 */
template <typename T> string get_string2(const T &arg) {
    if constexpr (std::is_same_v<std::string, T>)
        return arg; // Not compiled if T is built-in type
    else
        return to_string(arg); // Not compiled if T is std::string
}

/**
 * Before C++17, we could achieve similar behavior using template specialization.
 *
 * Template specialization allows you to provide different implementations for different types:
 * - Primary template: handles the general case (all types)
 * - Explicit specialization: handles specific types (e.g., std::string)
 *
 * When the compiler instantiates get_string3, it chooses the most specific matching template:
 * - get_string3(42) matches the primary template with T = int
 * - get_string3(str) (where str is std::string) matches the explicit specialization for std::string
 *
 * Advantages:
 * - Works in C++98 and later
 * - Clean separation of different implementations
 *
 * Disadvantages:
 * - Requires writing multiple template definitions
 * - Less elegant than if constexpr for simple cases
 * - Order matters: primary template must be declared before specializations
 */
// Template function for the general case
template <typename T> string get_string3(const T &arg) { return to_string(arg); }
// Template specialization for std::string
template <> string get_string3(const string &arg) { return arg; }

/**
 * SFINAE (Substitution Failure Is Not An Error):
 * When the compiler attempts to instantiate a template, if substituting a type into the template
 * parameters results in an invalid type or expression, the compiler doesn't treat it as a hard
 * error. Instead, it silently removes that template specialization from the candidate set and
 * continues looking for other matching templates.
 *
 * In get_string4, we use std::enable_if_t to control which overload is valid:
 * - The first overload is only valid when T is NOT std::string (using !std::is_same_v)
 * - The second overload is only valid when T IS std::string
 * If a type doesn't satisfy the condition, that overload is removed from consideration, and the
 * compiler selects the remaining valid overload. This allows us to provide different
 * implementations for different types without explicit template specialization.
 */
// Not instantiated if T is std::string
template <typename T, std::enable_if_t<!std::is_same_v<std::string, T>, int> = 99>
string get_string4(const T &arg) {
    return to_string(arg);
}
// Instantiated only if T is std::string
template <typename T, std::enable_if_t<std::is_same_v<std::string, T>, int> = 99>
string get_string4(const T &arg) {
    return arg;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 204-constexpr_if_statement.cpp && ./a.out
int main() {
    int x{42};
    string str{"hello"};
    cout << "x: " << x << endl;
    cout << "str: " << str << endl;

    // Compilation error:
    // cout << "get_string(x): " << get_string(x) << endl;
    // cout << "get_string(str): " << get_string(str) << endl;

    // With if constexpr:
    cout << "get_string2(x): " << get_string2(x) << endl;
    cout << "get_string2(str): " << get_string2(str) << endl;

    // With template specialization:
    cout << "get_string3(str): " << get_string3(str) << endl;
    cout << "get_string3(x): " << get_string3(x) << endl;

    // With SFINAE:
    cout << "get_string4(x): " << get_string4(x) << endl;
    cout << "get_string4(str): " << get_string4(str) << endl;
}