/**
 * Variadic Functions:
 * A variadic function in C can take any number of arguments. In the declaration of a variadic
 * function, the last parameter is the parameter pack "...". For example, `printf` in C takes a
 * format string followed by variable number of arguments.
 * ```
 *     int printf(const char *fmt, ...);
 * ```
 * Notice that it's not type safe. We can write `printf("%s", 42);` and it will compile. But it will
 * crash the program at runtime.
 * ```
 *     // The program will dereference the integer 42 as a pointer to a string.
 *     printf("%s\n", 42); // Segmentation fault (core dumped).
 * ```
 * Parameter pack in C only works properly with C types, and the arguments are processed at runtime.
 *
 * C++11 introduced variadic template functions. It is type safe and the compiler will deduce the
 * number of arguments and their types at compile time.
 * The list of template parameter types is written as "typename... T".
 * The list of function parameter types is written as "T...".
 * ```
 *     // Template function with a variable number of arguments
 *     template <typename... Args> // Args is a list of template parameter types
 *     void func(Args... args)     // args is a list of arguments whose types match Args
 * ```
 *
 * Parameter Packs:
 * Parameter packs are only available at compile time. We can do three things with a parameter pack.
 * - Use "sizeof...()" to get the number of elements
 * - Use "make_tuple" to store them in an std::tuple
 * - Iterate over the elements, using template recursion
 *
 * Template Recursion:
 * We can have recursive template function calls.
 * ```
 *     template<typename T, typename U, typename V>
 *     void func(T t, U u, V v) {
 *         func(u, v); // Recursive call
 *     }
 *
 *     template<typename U, typename V>
 *     void func(U u, V v) {
 *         func(v); // Recursive call
 *     }
 *
 *     template<typename V>
 *     void func(V v) {
 *         // End of recursion
 *     }
 * ```
 *
 * Pack Processing:
 * We can process a variadic template's pack by making recursive calls. Each call removes the first
 * element from the list.
 * ```
 *     template <typename T, typename... Args>
 *     void func(T t, Args... args) {
 *         // process t here.
 *         ...
 *
 *         func(args...); // Recursive call, passing the remainder of the list
 *     }
 * ```
 * To terminate the recursion, we write another template with a single argument, which will be
 * passed the final element in the list.
 * ```
 *     template <typename T>
 *     void func(T t) {
 *         cout << "The last argument";
 *     }
 * ```
 * Note that this `void func(T t);` must be declared above the variadic template in the source code.
 */

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

template <typename... Args> // Args is a list of types (template parameter pack)
void func(Args... args) {   // args is a list of arguments whose types match Args
    cout << "Compiler has deduced call with " << sizeof...(args) << " argument(s)\n";
}

template <typename... Args>               // Args is a list of types (template parameter pack)
void func2(Args... args) {                // args is a list of arguments whose types match Args
    auto arg_tuple = make_tuple(args...); // Store the arguments in a tuple
    auto first = get<0>(arg_tuple);
    cout << "First argument is " << first << endl;
}

template <typename T> // Non-variadic template
void func3(T t) {
    cout << "Non-variadic template\n";
    cout << "Processing argument " << t << endl;
}

template <typename T, typename... Args> // Args is a list of types (template parameter pack)
void func3(T t, Args... args) {         // args is a list of arguments whose types match Args
    size_t n_args = sizeof...(args) + 1;
    cout << "Variadic template: compiler has deduced variadic call with " << n_args
         << " argument(s)\n";
    cout << "Processing argument " << t << endl;
    func3(args...);
}

// g++ -std=c++20 -Wall -Wextra -pedantic 201-variadic_templates.cpp && ./a.out
int main() {
    int i{42};
    double d{0.0};
    string s{"text"};

    func(s);       // Instantiated as func(string);
    func(i, d, s); // Instantiated as func(int, double, string);

    cout << "--------------------------------\n";

    func2(i, d, s); // Instantiated as func(int, double, string);

    cout << "--------------------------------\n";

    func3(i, d, s); // Instantiated as func(int, double, string);

    return 0;
}
