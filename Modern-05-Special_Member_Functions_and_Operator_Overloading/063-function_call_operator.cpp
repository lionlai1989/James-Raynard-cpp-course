/**
 * Callable Objects and Functional Programming
 * Procedural programming involves a sequence of commands. Functional programming involves a tree of
 * function calls.
 *
 * In C, it can create callable objects using function pointers. E.g.:
 * ```
 * float func(int, int);
 * float (*func_ptr)(int, int) = func; // Pointer to function taking two ints and returning an float
 * ```
 * The `func_ptr` is a data variable that can be passed around and called like a function,
 * `func_ptr(1, 2)`.
 *
 * In C++, it can define a class with the function call operator `operator()`. This allows us to
 * make callable objects.
 * A C++ class which implements `operator()` is called a functor.
 *
 * The benefit of functors over function pointers is that functors can have state (data members).
 * That is, functors can store values which need to be kept between function calls.
 */

#include <iostream>
#include <vector>

using namespace std;

class evenp { // Class with function call operator
  public:
    bool operator()(int n) { // Our function call operator
        return (n % 2 == 0); // Return true if exactly divisible by 2
    }
};

void do_it(const vector<int> &vec, evenp is_even) {
    for (auto v : vec)
        if (is_even(v))
            cout << v << " is even\n";
}

class divisible {
  private:
    int divisor{1};

  public:
    divisible(int d) : divisor(d) {}
    bool operator()(int n) { return (n % divisor == 0); }
};

void do_it2(const vector<int> &vec, divisible is_div) {
    for (auto v : vec)
        if (is_div(v))
            cout << v << " is divisible\n";
}

// g++ -std=c++20 -Wall -Wextra -pedantic 063-function_call_operator.cpp && ./a.out
int main() {
    evenp is_even;  // Create a functor object
    if (is_even(6)) // Call its function call operator with argument 6
        cout << "6 is an even number\n";

    cout << "--------------------------------" << endl;

    vector<int> numbers{1, 4, 7, 11, 12, 23, 36}; // Vector of numbers

    cout << "Vector: ";
    for (auto number : numbers)
        cout << number << ", ";
    cout << endl;

    do_it(numbers, is_even); // Pass functor as argument to a function call

    cout << "--------------------------------" << endl;

    cout << "Vector: ";
    for (auto number : numbers)
        cout << number << ", ";
    cout << endl;

    // Create a divisible object with member variable equal to 3
    cout << "Finding elements which are divisible by 3\n";

    divisible divisible_by_three{3}; // Will return true if divisible by 3
    // Pass this as argument to the function call
    do_it2(numbers, divisible_by_three);
}
