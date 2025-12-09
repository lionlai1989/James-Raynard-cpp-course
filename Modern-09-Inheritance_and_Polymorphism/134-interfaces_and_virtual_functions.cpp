/**
 * Interfaces and Virtual Functions
 * Intuitively, base classes model abstract concepts such as "Shape" or "Vehicle". The derived
 * classes represent concrete implementations of these concepts, such as "Circle" or "Car".
 *
 * The base class is the interface to the class hierarchy. E.g., `Shape`'s public virtual member
 * functions provide all the functionality that is common to the hierarchy. Any Shape can be drawn,
 * rotated, etc.
 * The derived classes implement the interface defined by the base class concretely. E.g., `Circle`
 * implements the `draw` function to draw a circle.
 *
 * Usually, the base class's virtual member functions cannot do anything useful. We can use C++
 * syntax to express a base class as an interface.
 * We can make base class's virtual member functions "pure virtual" by doing this:
 * ```cpp
 * class Shape {
 *   public:
 *     virtual void draw() = 0; // Pure virtual function
 * };
 * ```
 * This means that Shape does not implement `draw()` at all.
 * A class with a pure virtual member function is called an "abstract class". This means that we
 * cannot instantiate objects of that class directly.
 * ```
 * Shape shape; // Error: cannot instantiate abstract class
 * ```
 * If we derive a class from an abstract class, the derived class must implement all pure virtual
 * functions to become a concrete class that can be instantiated. Otherwise, the derived class is
 * also an abstract class.
 *
 * Try to understand "Virtual Function Implementation". vtable, dynamic binding, etc.
 * Important thing is that calling a virtual member function takes longer than calling a non-virtual
 * one (takes 25-5-% more time). So use virtual functions only when necessary.
 *
 * Polymorphism:
 * - Subtype Polymorphism (Runtime Polymorphism):
 *   This is what we use with inheritance and virtual functions. It allows code written in terms of
 *   a base class (interface) to work with objects of any derived class. The specific function to call
 *   is determined at runtime (dynamic binding).
 *   Example: Taking a `Shape*` or `Shape&` and calling `draw()`, which executes `Circle::draw()` or `Triangle::draw()`.
 *
 * - Parametric Polymorphism (Compile-time Polymorphism):
 *   This is achieved using Templates (generics). We write code that works for any type `T`.
 *   The compiler generates the specific code for each type used.
 *   Example: `std::vector<int>`, `std::sort()`.
 *   It offers better performance (no runtime overhead) but requires the source code to be available in headers.
 *
 * Inheritance vs Composition (check `inheritance_vs_composition.cpp` for more details):
 * - Inheritance ("Is-A" relationship):
 *   Use when the derived class *is* a specialized version of the base class.
 *   The derived class inherits the interface and implementation of the base class.
 *   It creates a strong coupling between the base and derived classes. Changes in the base class affect all derived classes.
 *   Example: A `Circle` is a `Shape`.
 *
 * - Composition ("Has-A" relationship):
 *   Use when a class is composed of other objects, or uses them to implement its functionality.
 *   The class contains instances of other classes as member variables.
 *   It provides loose coupling. You can easily change the behavior by swapping the contained object.
 *   It allows for better encapsulation (you don't expose the interface of the component unless you want to).
 *   Example: A `Car` has an `Engine`. A `Car` is NOT an `Engine`.
 *
 * Guideline: Prefer Composition over Inheritance. Only use inheritance when the "Is-A" relationship is clear
 * and you need to leverage polymorphism (treating different objects as the same base type).
 * For code reuse alone, composition is usually better.
 *
 */

#include <iostream>

using namespace std;

class Shape {
  public:
    virtual void draw() const = 0; // Pure virtual function
}; // Abstract base class
class Circle : public Shape {}; // Still abstract - does not implement draw()
class Triangle : public Shape {
  public:
    void draw() const override { cout << "Drawing a Triangle...\n"; }
}; // Concrete class

//////////////////////////////////////////////////////////////////

/**
 * Object Slicing:
 * If we have a function that takes a base class object by value, and we pass a derived class object
 * to it, the derived part is "sliced off". Only the base part remains.
 */
class Shape2 {
  public:
    virtual void draw() const { cout << "Shape::draw()\n"; } // Empty virtual function
};
class Circle2 : public Shape2 {
  public:
    void draw() const override { cout << "Drawing a Circle...\n"; }
};
/**
 * Notice that when passing by value, the derived part is sliced off. Only the base part remains.
 * If we pass a Circle2 object to draw_shape(), the copy constructor of Shape2 is called to create
 * the parameter `s`.
 * - `s` will be a copy of the Shape2 object.
 * - In effect, the Circle2 part has been sliced off.
 */
void draw_shape(Shape2 s) {
    s.draw();     // Always calls Shape2's draw()
    (&s)->draw(); // Equivalent to above
}

//////////////////////////////////////////////////////////////////

class Shape3 {
  public:
    virtual void draw() const = 0; // Pure virtual function
}; // Abstract base class
class Circle3 : public Shape3 {
  public:
    void draw() const { cout << "Drawing a Circle...\n"; }
}; // Concrete class
/**
 * Shape3 is an abstract base class and it cannot be passed by value. It can only be passed by
 * pointer or by reference. In the function body, dynamic binding will be used.
 */
void draw_shape2(const Shape3 &s) {
    s.draw(); // Use dynamic binding to call the derived class's draw()
    (&s)->draw();
}

// g++ -std=c++20 -Wall -Wextra -pedantic 134-interfaces_and_virtual_functions.cpp && ./a.out
int main() {
    // Does not compile - cannot create variable of abstract type
    // Shape shape;
    // Circle circle;
    Triangle triangle;
    triangle.draw();

    cout << "---------------------------------\n";

    Circle2 circle2;
    draw_shape(circle2); // Pass derived class object by value as a Shape

    cout << "---------------------------------\n";

    Circle3 circle3;
    draw_shape2(circle3);
}
