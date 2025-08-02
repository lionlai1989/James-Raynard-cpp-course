/**
 *
 */

#include <iostream>

using namespace std;

class Vehicle {
  private:
    int max_speed;

  public:
    Vehicle(int max_speed) : max_speed(max_speed) { // Initialize max_speed
        cout << "Vehicle constructor\n";
    }
    // ...  Member Functions
};

class Aeroplane : public Vehicle {
  private:
    int max_height;

  public:
    // Initialize the Vehicle part of the instance, then initialize max_height
    Aeroplane(int max_speed, int max_height) : Vehicle(max_speed), max_height(max_height) {
        cout << "Aeroplane constructor\n";
    }
    // ...  Member Functions
};

class FighterPlane : public Aeroplane { // More specialized Aeroplane
  private:
    int max_num_missles;

  public:
    // Initialize the Aeroplane part of the instance, then initialize max_num_missles
    FighterPlane(int max_speed, int max_height, int max_num_missles)
        : Aeroplane(max_speed, max_height), max_num_missles(max_num_missles) {
        cout << "FighterPlane constructor\n";
    }
    // ...  Member Functions};
};

// g++ -std=c++20 -Wall -Wextra -pedantic 126-base_and_derived_classes.cpp && ./a.out
int main() {
    cout << "Creating Vehicle object\n";
    Vehicle vehicle(10);

    cout << endl;

    cout << "Creating Aeroplane object\n";
    Aeroplane aeroplane(40000, 500);

    cout << endl;

    cout << "Creating FighterPlane object\n";
    FighterPlane fighterplane(40000, 500, 10);
}
