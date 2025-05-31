/**
 * Polymorphism is when we use a base class object to represent a derived class object.
 * In c++, polymorphism requires either a pointer or a reference to the base class.
 *
 */

#include <iostream> // cout
#include <memory>   // unique_ptr, make_unique
#include <vector>   // vector

using namespace std;

class Shape {
  public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
  public:
    void draw() const { cout << "Drawing a Circle...\n"; }
};

class Triangle : public Shape {
  public:
    void draw() const { cout << "Drawing a Triangle...\n"; }
};

class Square : public Shape {
  public:
    void draw() const { cout << "Drawing a Square...\n"; }
};

// Factory function
Shape *create_shape(int sides) {
    /**
     * Advantages of using Factory Pattern:
     * - We can use arguments to decide the type of the object to create.
     * - It's easy to extend the factory if new child classes are added.
     */

    // The returned pointer will be copied into the function's return space
    if (sides == 1)
        return new Circle; // Create 1-sided shape
    else if (sides == 3)
        return new Triangle; // Create 3-sided shape
    else if (sides == 4)
        return new Square; // Create 4-sided shape
    else {
        cout << "Cannot create a shape with " << sides << " sides\n";
        return nullptr;
    }
}

// Factory function
unique_ptr<Shape> create_shape2(int sides) {
    /**
     * Create a unique_ptr as a local variable. This will allocate the memory and store a pointer to it.
     * Return the unique_ptr from the function.
     * The unique_ptr will be moved into the function's return space.
     * Then it will be moved into a variable in the caller.
     */

    // The returned unique_ptr will be moved into the function's return space
    if (sides == 1)
        return make_unique<Circle>(); // Create 1-sided shape
    else if (sides == 3)
        return make_unique<Triangle>(); // Create 3-sided shape
    else if (sides == 4)
        return make_unique<Square>(); // Create 4-sided shape
    else {
        cout << "Cannot create a shape with " << sides << " sides\n";
        return nullptr;
    }
}

// g++ -std=c++20 -Wall -Wextra -pedantic 169-unique_pointer_and_polymorphism.cpp && ./a.out
int main() {
    /**
     * A naive example.
     */
    vector<Shape *> shapes;
    shapes.push_back(new Circle);
    shapes.push_back(new Triangle);
    shapes.push_back(new Square);
    for (auto &it : shapes)
        it->draw();
    for (auto &it : shapes) // Must delete the pointers manually
        delete it;

    /**
     * A better example. We can use unique_ptr instead of calling `new` and `delete`.
     * unique_ptr<Base> pbase{make_unique<Derived>()};
     *
     * The allocated memory will be managed by unique_ptr.
     * - pbase cannot be aliased.
     * - pbase cannot be accidentally reseated, overwritten, or invalidated.
     * - Pointer arithmetic on pbase is not allowed.
     * - pbase cannot be copied.
     * - pbase cannot be assigned to another unique_ptr.
     * - pbase will be deleted automatically when it goes out of scope or exception is thrown.
     */
    vector<unique_ptr<Shape>> shapes2;
    shapes2.push_back(make_unique<Circle>());
    shapes2.push_back(make_unique<Triangle>());
    shapes2.push_back(make_unique<Square>());
    for (auto &it : shapes2)
        it->draw();

    /**
     * The Factory Pattern.
     * Programmers often call a function to create a new object. The function decides the type of the new object and
     * returns a pointer to it. It usually creates a child class object and returns it through a point to base class.
     */
    // The returned pointer will be copied into a variable in the caller
    Shape *pshape = create_shape(1);
    if (pshape)
        pshape->draw();
    delete pshape; // Memory leak if the pointer is not deleted

    // The returned unique_ptr will be moved into a variable in the caller
    auto pshape2{create_shape2(3)};
    if (pshape2)
        pshape2->draw();
    // Memory allocation is automatically released at end of scope
}
