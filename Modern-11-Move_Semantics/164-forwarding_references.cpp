/**
 * Why are Forwarding References Useful?
 * In "163-function_arguments_and_move_semantics.cpp", we saw that the best way to implement a
 * constructor is to write two separate constructors:
 * ```
 *     class Test {
 *         string m_str;
 *       public:
 *          // Called when an lvalue is passed
 *          Test(const string &str) : m_str((str)) {}
 *
 *          // Called when an rvalue is passed
 *          Test(string &&str) : m_str(std::move(str)) {}
 *     };
 * ```
 * Now if we have many parameters or even a variable number of parameters, we would have to write a
 * lot of overloads. This is where forwarding references come in handy. We can write a single
 * function template that can handle both lvalues and rvalues.
 */

#include <iostream>

using namespace std;

void func(int &x) { cout << "func called with argument int&: " << x << endl; }

class Test {};
template <class T> void func(T &&x) { cout << "func called" << endl; }

// g++ -std=c++20 -Wall -Wextra -pedantic 164-forwarding_references.cpp && ./a.out
int main() {
    /**
     * Nested References
     * Programmers cannot directly create a nested reference. However, the compiler can do this
     * internally for a type alias or a template type parameter.
     * The type of the result is determined by "reference collapsing". E.g., the reference to
     * "reference to int" collapses into reference to int.
     *
     * Reference Collapsing Rules:
     * rvalue references can also appear in nested references. The following rules determine the
     * type of the resulting reference:
     * ```
     * using lval_ref = int&;
     * using rval_ref = int&&;
     * ```
     * 1. lval_ref &  => int&
     * 2. lval_ref && => int&
     * 3. rval_ref &  => int&
     * 4. rval_ref && => int&&
     *
     */
    int i{42};
    // int& & ri = i;                       // Error

    using int_ref = int &; // or typedef int& int_ref;

    int_ref j{i};   // j is a reference to int
    int_ref &rj{j}; // rj is a reference to (reference to int)

    func(rj);

    cout << "\n--------------------------------\n" << endl;

    /**
     * && Argument Parameters:
     * Given a function:
     * ```
     *     func(Test &&x);
     * ```
     * The type of the parameter x is rvalue reference to Test. It can only be bound to an rvalue
     * (xvalue or prvalue).
     *
     * && Template Argument Parameters:
     * && has completely DIFFERENT meaning if the argument is a template type parameter:
     * ```
     *     template <class T> void func(T &&x);
     * ```
     * `x` is now a forwarding reference (or universal reference). It can be bound to an rvalue or
     * an lvalue.
     * However, how does the compiler deduce the type T when the compiler instantiates the function?
     * When deducing the argument type for a forwarding reference, the compiler first examines the
     * value category of the argument:
     * 1. If an lvalue is passed to the function, T is deduced as lvalue reference to the type of
     *    the argument. Therefore, `x` becomes an lvalue reference.
     * 2. If an rvalue is passed to the function, T is deduced as the original type of the argument.
     * `x` is then an rvalue reference.
     */
    Test t;      // t is an lvalue of type Test
    Test &rt{t}; // rt is an lvalue reference to t

    // T is Test& and x is T&& => Test&
    func(t); // Compiler instantiates func(Test& x)

    // T is Test& and x is T&& => Test&
    func(rt); // Compiler instantiates func(Test& x)

    // T is Test and x is T&& => Test&&
    func(std::move(t)); // Compiler instantiates func(Test&& x)
}