#include <iostream>
#include <string>
#include <cstddef>

using namespace std; // For brevity in this example

/**
 * Template specialization for Fibonacci numbers (intended for N >= 0).
 */
template <int N> int fibonacci() {
    // General case (N > 1)
    return fibonacci<N - 1>() + fibonacci<N - 2>();
}
template <> int fibonacci<1>() {
    // Specialization for N == 1
    return 1;
}
template <> int fibonacci<0>() {
    // Specialization for N == 0
    return 0;
}

/**
 * Using `if constexpr` instead of template specialization.
 *
 * `constexpr` on the function allows it to be evaluated at compile-time when called in a
 * constant expression context (e.g., `constexpr int result = fibonacci2<10>()`).
 *
 * `if constexpr (N > 1)` discards the unused branch at compile-time:
 * - When N > 1: only the recursive call is compiled
 * - When N <= 1: only the base case `return N` is compiled
 *
 * Benefits over template specialization:
 * - Single template definition (no need for separate specializations for N == 0 and N == 1)
 * - Cleaner and more readable code
 * - `if constexpr` eliminates unused code paths at compile-time, so unreachable or ill-formed
 *   branches are discarded during compilation
 */
template <int N> constexpr int fibonacci2() {
    if constexpr (N > 1)
        return fibonacci2<N - 1>() + fibonacci2<N - 2>();
    return N;
}

/**
 * Variadic template functions require an explicit base case to terminate recursion.
 *
 * The base case (non-variadic overload) matches when only one argument remains:
 * - func(i, d, s) → func(i, d) → func(i) [matches base case, stops recursion]
 *
 * Without this base case, the compiler would infinitely try to instantiate
 * func(Args...) with fewer and fewer arguments, eventually causing a compilation error.
 *
 * Compile-time vs Runtime:
 * - Compile-time: The compiler instantiates template specializations for each unique set of
 arguments
 *   - func(int, double, string) generates 3 function versions
 * - Runtime: The generated functions execute when called in main()
 *   - cout statements and actual function calls execute at runtime
 */
template <typename T> void func(T t) {
    cout << "Non-variadic template\n";
    cout << "Processing argument " << t << endl;
}
template <typename T, typename... Args> // Args is a list of types (template parameter pack)
void func(T t, Args... args) {          // args is a list of arguments whose types match Args
    size_t n_args = sizeof...(args) + 1;
    cout << "Variadic template: compiler has deduced variadic call with " << n_args
         << " argument(s)\n";
    cout << "Processing argument " << t << endl;
    func(args...);
}

/**
 * With `if constexpr`, we can avoid the need for an explicit base case.
 *
 * How it works:
 * - `if constexpr (sizeof...(args) > 0)` evaluates at compile-time
 * - When args is not empty: the recursive call is compiled
 * - When args is empty: the recursive call is discarded at compile-time
 *
 * Compile-time vs Runtime:
 * - Compile-time: The compiler instantiates template specializations for each recursive call
 *   - func2(int, double, string) → func2(double, string) → func2(string)
 *   - if constexpr discards the recursive call when sizeof...(args) == 0, so no infinite recursion
 * - Runtime: The generated functions execute when called in main()
 *   - cout statements and function calls execute at runtime
 *
 * About `constexpr` on func2:
 * - It *allows* the function to be evaluated at compile-time when it is called in a constant
 *   expression context and its body is valid in a constant expression.
 * - It does *not* force all calls to be evaluated at compile-time; normal calls still execute
 *   at runtime.
 * - In this example, because func2 uses `cout` (I/O), it cannot actually be used in a constant
 *   expression, so all calls are effectively runtime calls even though the function is marked
 *   `constexpr`.
 * - In other words, if removing all the `cout` statements, the function can be evaluated at compile-time.
 *
 * Advantages over func():
 * - No need for explicit base case specialization
 * - Cleaner and more concise code
 * - if constexpr handles termination automatically
 */
template <typename T, typename... Args>   // Args is a list of types (template parameter pack)
constexpr void func2(T t, Args... args) { // args is a list of arguments whose types match Args
    size_t n_args = sizeof...(args) + 1;
    cout << "Variadic template: compiler has deduced variadic call with " << n_args
         << " argument(s)\n";
    cout << "Processing argument " << t << endl;

    if constexpr (sizeof...(args) > 0)
        func2(args...);
}

// g++ -std=c++20 -Wall -Wextra -pedantic 205-constexpr_if_examples.cpp && ./a.out
int main() {
    constexpr int n{10};
    cout << "fibonacci<n>() number n=" << n << " is: " << fibonacci<n>() << endl;
    cout << "fibonacci2<n>() number n=" << n << " is: " << fibonacci2<n>() << endl;
    cout << "\n";

    int i{42};
    double d{0.0};
    string s{"text"};
    func(i, d, s); // Instantiated as func(int, double, string);
    cout << "\n";
    func2(i, d, s); // Instantiated as func2(int, double, string);
}
