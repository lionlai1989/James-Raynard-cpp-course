/**
 * The memory layout of Base class and Derived class objects
 *
 *               ---------------------------
 *   base_ptr--> |   Base   |              |
 *               ---------------------------
 *               <---      Derived      --->
 */

#include <iostream>
#include <vector>

using namespace std;

class Shape {
  public:
    void draw() const { cout << "Drawing a generic shape...\n"; }
};

class Circle : public Shape {
  public:
    void draw() const { cout << "Drawing a circle...\n"; }
    void area() const { cout << "Calculating area of circle...\n"; }
};

void draw_shape(const Shape &s) {
    s.draw(); // Calls draw member function of Shape
}

void draw_shape(const Circle &c) {
    c.draw(); // Calls draw member function of Circle
}

// g++ -std=c++20 -Wall -Wextra -pedantic 063-pointers_references_and_inheritance.cpp && ./a.out
int main() {
    Circle circle; // Derived class object
    Shape shape;   // Base class object

    Shape *shape_ptr = &circle; // Pointer to base class, points to a Circle object
    // Circle *circle_ptr = &shape; // Error!

    Shape &shape_ref = circle; // Binds reference to base class, to a Circle object
    // Circle &circle_ref = shape; // Error!

    shape_ptr->draw(); // Calls Shape's version of draw()
                       // shape_ptr->area(); // Error!

    draw_shape(circle);    // Calls Circle's version of draw()
    draw_shape(shape_ref); // Calls Shape's version of draw()
    draw_shape(shape);     // Calls Shape's version of draw()

    cout << "--------------------------------" << endl;

    vector<Shape *> shapes; // Vector of pointers to Shape instances

    // Create a pointer to a child class of Shape and append it to the vector
    shapes.push_back(new Circle);

    for (auto s : shapes) {
        s->draw(); // Calls Shape::draw()

        /**
         * Here, in order to use the derived class's member function, we cast the base class pointer
         * to a derived class pointer. The drawback of this approach is that we need to know the
         * actual type of the object being pointed to at compile time. Fortunately, C++ provides a
         * mechanism to determine the actual type of the object at runtime. Check
         * "064-static_and_dynamic_type.cpp" for more details.
         */
        static_cast<Circle *>(s)->draw(); // Calls Circle::draw()
    }

    for (auto s : shapes) // Release allocated memory
        delete s;

    return 0;
}
