/**
 * Inheritance vs Composition
 *
 * Composition is often preferred over inheritance because it results in looser coupling
 * and better encapsulation.
 *
 * "Is-A" vs "Has-A":
 * - Inheritance models an "Is-A" relationship (e.g., a Dog is an Animal).
 * - Composition models a "Has-A" relationship (e.g., a Car has an Engine).
 *
 * Problem with inappropriate inheritance:
 * If we inherit for code reuse where no "Is-A" relationship exists, we expose unnecessary interfaces
 * and create fragile hierarchies.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==========================================
// Example 1: The "Has-A" relationship (Car and Engine)
// ==========================================

class Engine {
  public:
    void start() { cout << "Engine started.\n"; }
    void stop() { cout << "Engine stopped.\n"; }
};

// BAD: Inheritance used for code reuse (A Car is not an Engine)
class CarInheritance : public Engine {
  public:
    void drive() {
        start(); // Inherited from Engine
        cout << "Car is moving...\n";
    }
    // Problem: CarInheritance exposes stop() and start() directly as its own interface.
    // Users might call car.stop() thinking it stops the car, but it just stops the engine.
};

// GOOD: Composition (A Car has an Engine)
class CarComposition {
  private:
    Engine engine; // The Car "owns" the Engine

  public:
    void drive() {
        engine.start(); // Delegating to the component
        cout << "Car is moving...\n";
    }
    // We can choose what to expose. We might implement a stop_car() method
    // that gracefully stops the car and then the engine.
    void stop_car() {
        cout << "Braking...\n";
        engine.stop();
    }
};

// ==========================================
// Example 2: Implementation Reuse (Stack)
// ==========================================

// BAD: Inheriting from std::vector to implement a Stack
// std::vector has methods like insert(), erase(), clear(), operator[]
// A Stack should ONLY allow push() and pop() (LIFO).
class StackInheritance : public std::vector<int> {
  public:
    void push(int value) { push_back(value); }
    void pop() { pop_back(); }
    int top() { return back(); }
};
// Problem:
// StackInheritance s;
// s.insert(s.begin(), 5); // OOPS! We can insert at the bottom. This breaks the Stack abstraction.

// GOOD: Composition
class StackComposition {
  private:
    std::vector<int> data; // Implementation detail hidden

  public:
    void push(int value) { data.push_back(value); }
    void pop() { 
        if (!data.empty()) data.pop_back(); 
    }
    int top() { 
        return data.empty() ? -1 : data.back(); 
    }
    bool is_empty() const { return data.empty(); }
};

// g++ -std=c++20 -Wall -Wextra -pedantic inheritance_vs_composition.cpp && ./a.out
int main() {
    cout << "--- Inheritance (Bad) ---\n";
    CarInheritance badCar;
    badCar.start(); // Exposed!
    badCar.drive();

    cout << "\n--- Composition (Good) ---\n";
    CarComposition goodCar;
    // goodCar.start(); // Error: Engine::start is private/not exposed
    goodCar.drive();
    goodCar.stop_car();

    cout << "\n--- Stack Example ---\n";
    StackInheritance badStack;
    badStack.push(10);
    badStack[0] = 5; // Direct access allowed - Breaks encapsulation!
    cout << "Bad Stack top (modified via index): " << badStack.top() << "\n";

    StackComposition goodStack;
    goodStack.push(10);
    // goodStack[0] = 5; // Compile Error: operator[] not defined
    cout << "Good Stack top: " << goodStack.top() << "\n";

    return 0;
}
