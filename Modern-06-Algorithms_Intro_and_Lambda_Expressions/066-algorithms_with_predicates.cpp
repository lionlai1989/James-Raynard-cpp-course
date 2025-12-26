#include <algorithm> // sort
#include <iostream>  // cout
#include <string>    // string
#include <vector>    // vector

using namespace std;

// Define a predicate function
bool is_shorter(const string &lhs, const string &rhs) { return lhs.size() < rhs.size(); }

// Define a predicate as a functor
class is_shorter2 {
  public:
    // Overloaded () operator
    // Takes two strings as arguments
    // Returns true/false depending on relative string length
    bool operator()(const string &lhs, const string &rhs) { return lhs.size() < rhs.size(); }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 066-algorithms_with_predicates.cpp && ./a.out
int main() {
    vector<string> names = {"Dilbert", "PHB", "Dogbert", "Asok", "Ted", "Alice", "Wally"};

    cout << "Vector before sort()\n";
    for (auto name : names)
        cout << name << ", ";
    cout << endl << endl;

    cout << "Sorted alphabetically:" << endl;
    sort(begin(names), end(names));
    for (auto name : names)
        cout << name << ", ";
    cout << endl;

    cout << endl << "Sorted by length with function pointer:" << endl;
    sort(begin(names), end(names), is_shorter);
    for (auto name : names)
        cout << name << ", ";
    cout << endl;

    cout << endl << "Sorted by length with functor:" << endl;
    sort(begin(names), end(names), is_shorter2());
    for (auto name : names)
        cout << name << ", ";
    cout << endl;
}