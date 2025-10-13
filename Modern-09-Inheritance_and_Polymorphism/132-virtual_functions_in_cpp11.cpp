/**
 * Override and Overload of Virtual Functions in C++11
 * A child class can define a member function with the same name as a virtual member function in the
 * parent class.
 * - Overriding: the child class function has the same signature (name, parameters, and const-ness)
 *   as the parent class function.
 * - Overloading: the child class function has a different signature from the parent class function.
 *   Dynamic binding does not work here.
 *
 * The override specifier (introduced in C++11) can be used in the child class to indicate that a
 * member function is intended to override a virtual function in the parent class. The compiler will
 * given an error if the function does not actually override a base class function.
 *
 * C++11 introduced the "final" specifier, which can be used to prevent further overriding of a
 * virtual function in derived classes, or to prevent a class from being inherited from.
 */

#include <iostream>

using namespace std;

class Shape {
  public:
    virtual void draw() const { cout << "Drawing a generic shape...\n"; }
};

class Circle : public Shape {
  public:
    void draw() const override { cout << "Drawing a circle...\n"; } // OK - overrides Shape::draw()
    // void draw(int radius) const override; Error! Does not override
};

//////////////////////////////////////////////////////////////////////

class Circle2 final : public Shape { // Circle2 is declared as final
  public:
    void draw() const override final; // draw() is declared as final
};
/**
 * Circle2 is declared as final, so it cannot be inherited from. The compiler will give an error if
 * any class tries to inherit from Circle2.
 */
// error: cannot derive from ‘final’ base ‘Circle2’ in derived type ‘DeluxeCircle’
// error: virtual function ‘virtual void DeluxeCircle::draw() const’ overriding final function
// class DeluxeCircle : public Circle2 {
//   public:
//     void draw() const override;
// };

// g++ -std=c++20 -Wall -Wextra -pedantic 132-virtual_functions_in_cpp11.cpp && ./a.out
int main() {
    Circle circle;
    circle.draw();
}
