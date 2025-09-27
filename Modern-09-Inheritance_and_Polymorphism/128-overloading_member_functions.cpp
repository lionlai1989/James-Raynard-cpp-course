#include <iostream>

using namespace std;

class Vehicle {
  public:
    void accelerate() { cout << "Increasing speed: "; }
};

class Aeroplane : public Vehicle {
  public:
    // Overloaded member function
    void accelerate(int height) { cout << "Accelerating at a height of: " << height; }
};

class Aeroplane2 : public Vehicle {
  public:
    void accelerate() { Vehicle::accelerate(); } // Call parent version of accelerate()
    void accelerate(int height) { cout << "Accelerating at a height of: " << height; }
};

class Aeroplane3 : public Vehicle {
  public:
    using Vehicle::accelerate;
    void accelerate(int height) { cout << "Accelerating at a height of: " << height; }
};

// g++ -std=c++20 -Wall -Wextra -pedantic 128-overloading_member_functions.cpp && ./a.out
int main() {
    Aeroplane plane;
    plane.accelerate(1000);
    cout << endl;

    /**
     * error: no matching function for call to ‘Aeroplane::accelerate()’
     * plane.accelerate();
     */

    cout << "--------------------------------" << endl;

    // One way to solve the issue above is to define a new member function in the derived class that
    // calls the parent version of accelerate()
    Aeroplane2 plane2;
    plane2.accelerate(1000);
    cout << endl;
    plane2.accelerate();
    cout << endl;

    cout << "--------------------------------" << endl;

    // The modern solution to this problem is to use the 'using' keyword in the derived class
    Aeroplane3 plane3;
    plane3.accelerate(1000);
    cout << endl;
    plane3.accelerate();
    cout << endl;
}
