#include <iostream>

using namespace std;

class Complex {
    double real;
    double imag;

  public:
    Complex(double real, double imag) : real(real), imag(imag) {}

    Complex &operator++();   // Prefix ++ operator
    Complex operator++(int); // Postfix ++ operator

    Complex &operator--();   // Prefix -- operator
    Complex operator--(int); // Postfix -- operator

    void print() { cout << "(" << real << ", " << imag << ")" << endl; }
};

// Prefix ++ operator
// Returns a reference to the current object
Complex &Complex::operator++() {
    ++real;
    return *this;
}

// Postfix ++ operator takes a dummy parameter
// Returns a copy of the current object before incrementing
Complex Complex::operator++(int) {
    Complex temp(*this);
    ++real;
    return temp;
}

// Prefix -- operator
Complex &Complex::operator--() {
    --real;
    return *this;
}

// Postfix -- operator
Complex Complex::operator--(int) {
    Complex temp(*this);
    --real;
    return temp;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 062-prefix_and_postfix_operators.cpp && ./a.out
int main() {
    Complex c(5, 6);
    cout << "Initial value of c: ";
    c.print();

    ++c;
    cout << "After calling ++c: ";
    c.print();

    Complex d = c++;
    cout << "After calling c++: ";
    c.print();
    cout << "Value of d: ";
    d.print();

    --c;
    cout << "After calling --c: ";
    c.print();

    d = c--;
    cout << "After calling c--: ";
    c.print();
    cout << "Value of d: ";
    d.print();
}