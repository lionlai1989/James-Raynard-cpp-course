/**
 * Traditional Pointers: A traditional pointer is a variable that stores the address of an object in memory.
 *
 * Smart Pointers: Smart pointers are classes which encapsulate allocated memory.
 * - The class has a private data memeber which is a pointer to the allocated memory.
 * - The smart pointer object has ownership of the allocated memory.
 * - The allocated memory can only be accessed through public member functions.
 * - Pointer arithmetic is not allowed.
 * - Smart pointers are implemented using RAII idiom.
 *
 */

/**
 * std::unique_ptr
 * In most situations, unique_ptr is the best replacement for raw pointers which manages heap memory. It allocates heap
 * memory in its constructor and has sole ownership of it. unique_ptr automatically releases the memory when it goes out
 * of scope, which allows heap-allocated memory to be used like a stack object.
 * unique_ptr is a move-only class. Moving a unique_ptr transfers the allocated memory from one object to another.
 */

#include <iostream> // cout
#include <memory>   // unique_ptr

using namespace std;

// Data structure representing a point on the screen
struct Point {
    int x;
    int y;
};

void func(unique_ptr<Point> upp) {
    cout << "In func: ";
    cout << upp->x << ", " << upp->y << endl;
}

unique_ptr<Point> point_ptr(int x, int y) {
    /**
     * We can return a unique_ptr object from a function.
     * The object is moved into the function's return space.
     * This transfers ownership of the allocated memory to the caller.
     *
     * Note that we do not use `std::move(ptr)` in the return statement to cast ptr to an rvalue because the compiler
     * will always more a return value to an rvalue.
     */
    Point p = {x, y};                // Create Point object
    auto ptr{make_unique<Point>(p)}; // Create local unique_ptr object
    return ptr;                      // The allocated memory is transferred
                                     // from p to the returned object
}

unique_ptr<Point> point_ptr2(int x, int y) {
    Point p = {x, y};             // Create Point object
    return make_unique<Point>(p); // Create and return unique_ptr object
}

// g++ -std=c++20 -Wall -Wextra -pedantic 168-unique_pointer.cpp && ./a.out
int main() {
    // In C++11, we have to provide the pointer by calling new() explicitly

    // Allocate a single int with value 42
    unique_ptr<int> p1{new int(42)}; // p1's member points to the int on the heap

    // Allocate array of 6 ints
    unique_ptr<int[]> p2{new int[6]}; // p2's member points to the first element of the array
    /**
     * It's usually better to use std::array or std::vector.
     * std::array<int, 6> arr; // stack-allocated array
     * std::vector<int> vec(6); // heap-allocated array
     *
     * The only reason to use built-in array is that a fixed-size array on the heap is needed, because std::array
     * can only allocate memory on the stack and std::vector cannot allocate fixed-size arrays on the heap. Thus, using
     * built-in type array has the two advantages of both worlds:
     * - Fixed size
     * - Allocated on the heap
     */

    // C++14 has make_unique, which calls new() internally
    // make_unique uses perfect forwarding to intialize the int object with the value 42
    auto p3{make_unique<int>(42)};

    // Allocate array of 6 ints
    auto p4{make_unique<int[]>(6)};

    cout << *p1 << endl; // Single object can be dereferenced
    // cout << p1[0];                            // Error - single object cannot be indexed
    cout << p2[0] << " " << p2[1] << endl; // Array can be indexed
    // cout << *p2 << endl;                      // Error - array cannot be dereferenced
    //  ++p1;                                    // Error - pointer arithmetic not supported
    //  ++p2;                                    // Error - pointer arithmetic not supported
    //  p1 = p2;                                 // Error - unique_ptr can only be moved
    //  unique_ptr<int> p5(p4);                  // Error - unique_ptr can only be moved
    unique_ptr<int> p5(std::move(p3)); // OK
    // unique_ptr<int> p6(std::move(p4));        // Error - incompatible types

    p1 = nullptr; // Calls delete on the pointer member
                  // and sets the pointer to nullptr

    // Create a unique_ptr to an point which has initial value {3,6}
    auto point{make_unique<Point>(Point{3, 6})};
    // unique_ptr<Point> p{ new Point{3, 6} };           // C++11
    cout << "Point: " << point->x << ", " << point->y << endl;
    // func(point); Error! it will call the copy constructor of unique_ptr which is deleted.
    func(std::move(point));
    /**
     * After moving the unique_ptr, the original unique_ptr is set to nullptr. Thus the following code will cause
     * a runtime error.
     * cout << "Point: " << point->x << ", " << point->y << endl;
     */

    auto upp{point_ptr(1, 2)};
    cout << "Point: " << upp->x << ", " << upp->y << endl;

    auto upp2{point_ptr2(3, 4)};
    cout << "Point: " << upp2->x << ", " << upp2->y << endl;

    return 0;
}
