/**
 * Static Type and Dynamic Type
 *
 * Given the code below:
 * ```
 *     class Shape {};
 *     class Circle : public Shape {};
 *
 *     Circle circle;
 *     Shape *pshape = &circle;
 * ```
 * `pshape` is delcared as a pointer to `Shape`, but `pshape` points to the address of a `Circle`
 * object.
 *
 * What is the type of `pshape`?
 *
 * In C++, every variable has a static type and a dynamic type. The static type is the type used in
 * the variable's declaration. Eg,
 * ```
 * Circle circle; // static type Circle
 * Shape *pshape = &circle; // static type pointer to Shape
 * Shape &rshape = circle; // static type reference to Shape
 * ```
 * The dynamic type is the type of the object in memory that the variable refers to. For most
 * objects, this will be the same as the static type. However, it can be different for a pointer and
 * reference to a base class. Eg,
 * ```
 * Circle circle; // static type Circle
 * Shape *pshape = &circle; // dynamic type pointer to Circle
 * Shape &rshape = circle; // dynamic type reference to Circle
 * ```
 *
 * C++ almost always uses the static type of a variable to determine which function to call.
 * However, the dynamic type is used when calling a virtual function through a pointer or reference
 * to a base class.
 */

#include <iostream>
#include <vector>

using namespace std;

class Shape {
  public:
    // Make draw() a virtual function
    virtual void draw() { cout << "Drawing a generic shape...\n"; }
};

class Circle : public Shape {
  public:
    void draw() { cout << "Drawing a circle...\n"; }
};

// g++ -std=c++20 -Wall -Wextra -pedantic 064-static_and_dynamic_type.cpp && ./a.out
int main() {
    vector<Shape *> shapes; // Vector of pointers to Shape objects

    // Create a pointer to a child class of Shape and append it to the vector
    shapes.push_back(new Circle());

    for (auto shape : shapes)
        shape->draw(); // Calls Circle::draw()

    for (auto shape : shapes) // Release allocated memory
        delete shape;
}