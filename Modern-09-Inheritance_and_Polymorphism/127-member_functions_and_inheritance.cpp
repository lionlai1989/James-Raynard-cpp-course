/**
 * When a child class inherits from a parent class, it inherits all the non-private member functions
 * of its parent class.
 *
 * A child class can reimplement or extend a member function of its parent class to make it more
 * specific.
 *
 * A public member of a class is accessible from any part of the code. Thus, a child class will have
 * access to all its parent's PUBLIC members.
 * A child class does not have access to its parent's PRIVATE members.
 * Sometimes, we want to make a member not part of the public interface of a parent class, but still
 * accessible to a child class. We can do this by making the member PROTECTED.
 *
 */
#include <iostream>

using namespace std;

class Vehicle {
  public:
    void start() { cout << "Engine started "; }
};

// Inherit the start() function from the Vehicle class
class Aeroplane : public Vehicle {
  public:
    /// void start(); Inherited from Vehicle ///
};

// Reimplement the start() function
class Aeroplane2 : public Vehicle {
  public:
    void start() {
        cout << "Carrying out checks... ";
        cout << "Ready for take-off!";
    }
};

// Extend the start() function
class Aeroplane3 : public Vehicle {
  public:
    void start() {
        cout << "Carrying out checks... ";
        Vehicle::start(); // Call base class member function
        cout << "Ready for take-off!";
    }
};

////////////////////////////////////////////////////////////

// Protected member functions
class Vehicle2 {
  protected:
    void kids_only() {
        cout << "Kids only" << endl;
    } // Can only be called by this class and its children
  public:
    void call_kids() { kids_only(); }
};

// Inherit the kids_only() function from the Vehicle class
class Aeroplane4 : public Vehicle2 {
  public:
    void do_something() { kids_only(); } // Child can call protected member function
};

// g++ -std=c++20 -Wall -Wextra -pedantic 127-member_functions_and_inheritance.cpp && ./a.out
int main() {
    Aeroplane plane;
    plane.start(); // Calls start() on an Aeroplane object. Prints out "Engine started: "

    cout << "\n--------------------------------\n" << endl;

    Aeroplane2 plane2;
    plane2.start(); // Calls start() on an Aeroplane2 object.

    cout << "\n--------------------------------\n" << endl;

    Aeroplane3 plane3;
    plane3.start(); // Calls start() on an Aeroplane3 object.

    cout << "\n--------------------------------\n" << endl;

    Vehicle2 vehicle2;
    // vehicle2.kids_only(); // Cannot be called by "outsider" code. kids_only is non-public.
    vehicle2.call_kids();

    Aeroplane4 plane4;
    // plane4.kids_only(); // Cannot be called by "outsider" code. kids_only is non-public.
    plane4.do_something(); // Calls do_something() on an Aeroplane4 object.

    return 0;
}
