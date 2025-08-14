#include <cassert>  // assert
#include <iostream> // cout

using namespace std;

/**
 * Default Template Parameters
 * We can implement a template class with a default type
 */
template <typename T = int> class number {
    T value; // value will have type int by default

  public:
    number(const T &value) : value(value) {}
    void print() { cout << "value: " << value << "\n"; }
};

////////////////////////////////////////////////////////////

/**
 * Template function with a default type
 */
template <typename T = int> void func(const T &t1, const T &t2) {
    cout << "The sum of " << t1 << " and " << t2 << " is " << (t1 + t2) << "\n";
};

// g++ -std=c++20 -Wall -Wextra -pedantic 202-miscellaneous_template_features.cpp && ./a.out
int main() {
    /**
     * assert()
     * - Defined in <cassert>
     * - Checks its argument at RUNTIME.
     * - Can be disabled by `#define NDEBUG`
     */
    int x = 42;
    assert(x == 42);

    cout << "--------------------------------\n";

    /**
     * static_assert()
     * - It takes a constant bool expression and a string literal
     * - The bool expression is checked during compilation
     *   - If false, the compilation stops
     *   - Otherwise, the compilation continues
     * - Mainly used in template metaprogramming
     *   `static_assert(std::is_copy_constructible<T>::value, "Argument must be copyable");`
     */
    static_assert(sizeof(int *) == 8, "This program requires a 64-bit compiler");

    cout << "--------------------------------\n";

    number<long double> high_precision(1.99999); // Instantiate number object with long double
    number<> default_number(2);                  // Instantiate number object with default (int)
    high_precision.print();
    default_number.print();

    cout << "--------------------------------\n";

    long double hp1{1.99999}, hp2{3.0004};
    int normal1{2}, normal2{3};
    func<long double>(hp1, hp2); // Instantiate function with long double
    func<>(normal1, normal2);    // Instantiate function with default (int)

    return 0;
}
