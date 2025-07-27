/**
 * Plus operator:
 *   - Prototype: "T operator+(const T& lhs, const T& rhs);"
 *   - Invocation: "lhs + rhs;"
 *   - Called as: "operator+(lhs, rhs);"
 *   - Return: sum of lhs and rhs, returned by value
 *   - This is defined as a non-member function. WHY?
 *
 * += operator:
 *   - Prototype: "T& operator+=(const T& rhs);"
 *   - Invocation: "lhs += rhs;"
 *   - Called as: "lhs.operator += (rhs);"
 *   - Return: modified lhs, returned by reference
 *   - This is defined as a member function. WHY?
 */

#include <iostream>

using namespace std;

// Avoid potential confusion with std::complex
class Complex {
  private:
    double real{0.0};
    double imag{0.0};

  public:
    Complex(double r, double i) : real(r), imag(i) {}
    Complex(double r) : real(r) {}

    // We define the += operator as a member function
    // This adds the real and imaginary parts separately and returns the modified object
    Complex &operator+=(const Complex &rhs) {
        real += rhs.real; // Assign new value of real member
        imag += rhs.imag; // Assign new value of imag member
        return *this;     // Return modified object by reference
    }
    void print() { cout << "(" << real << ", " << imag << ")" << endl; }
};

/**
 * We define the + operator as a non-member function.
 * When we write "c1 + c2", the compiler looks not only in the global scope but also in the
 * namespaces of Complex to find matching operator+ overloads. By defining it as a free function in
 * the same namespace as your type, you let ADL find it automatically. A member version would only
 * be found if the left operand is already of your type.
 *
 */
Complex operator+(const Complex &lhs, const Complex &rhs) {
    // If we change the implementation detail of how Complex number addition works, we only need to
    // change the += operator. We don't need to change the + operator.

    Complex temp{lhs}; // Make a copy of the lhs argument
    temp += rhs;       // Add the rhs argument to it
    return temp;       // Return the modified copy of the lhs argument
}

// g++ -std=c++20 -Wall -Wextra -pedantic 059-addition_operators.cpp && ./a.out
int main() {
    Complex c1(1, 2);
    Complex c2(3, 4);
    cout << "c1: ";
    c1.print();
    cout << "c2: ";
    c2.print();

    Complex c3 = c1 + c2;
    cout << "c3: ";
    c3.print();

    c1 += c2;
    cout << "c1: ";
    c1.print();

    // The compiler will contruct Complex(1) and then call the operator+ function.
    Complex c4 = 1 + c2; // Type conversion (int -> double -> Complex)
    cout << "c4: ";
    c4.print();
}
