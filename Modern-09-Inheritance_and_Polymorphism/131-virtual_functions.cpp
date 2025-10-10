/**
 * Virtual Functions
 *
 * Static Binding vs Dynamic Binding
 * Normally when we call a member function of an object, the compiler will decide which function to
 * call. This is done using the static type of the object (the type known at compile time).
 * ```
 *     Circle circle; // static type is Circle
 *     Shape &rshape = circle; // rshape is a reference to Shape, but bound to a Circle object
 *     rshape.draw(); // Calls Shape::draw() because static type of rshape is Shape
 * ```
 * This is known as static binding.
 * However, there are some cases where the compiler cannot determine the type of the object at
 * compile time. Instead, it generates code that will determine the type of the object at runtime.
 * It will use the dynamic type of the object (the type of the actual object in memory at runtime).
 * This is known as dynamic binding.
 *
 * Two conditions must be met for dynamic binding to occur:
 * 1. A member function is called through a reference or pointer to a base class.
 * 2. The member function is declared as virtual in the base class.
 */

#include <iostream>

using namespace std;

class Shape {
  public:
    virtual void draw() const { cout << "Drawing a generic shape...\n"; }
};

class Circle : public Shape {
  public:
    // Override base class virtual draw member function
    void draw() const override { cout << "Drawing a circle...\n"; }
};

class Triangle : public Shape {
  public:
    // To be extra safe and clear, we tell the compiler we intend to override a base class virtual
    // member function
    void draw() const override { cout << "Drawing a triangle...\n"; }
};

void draw_shape(const Shape &s) { // Argument is a reference to a Shape
    s.draw();                     // Use dynamic binding to call the appropriate draw()
}

// g++ -std=c++20 -Wall -Wextra -pedantic 131-virtual_functions.cpp && ./a.out
int main() {
    Circle circle;     // Derived class object
    Triangle triangle; // Derived class object

    draw_shape(circle);   // draw_shape will call Circle's version of draw()
    draw_shape(triangle); // draw_shape will call Triangle's version of draw()

    Shape &rcircle = circle;      // Reference to Shape, bound to a Circle object
    Shape *ptriangle = &triangle; // Pointer to Shape, bound to a Triangle object

    draw_shape(rcircle);    // draw_shape will call Circle's version of draw()
    draw_shape(*ptriangle); // draw_shape will call Triangle's version of draw()
}
