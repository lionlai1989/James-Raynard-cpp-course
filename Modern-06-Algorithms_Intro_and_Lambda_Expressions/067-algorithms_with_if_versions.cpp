/**
 * Many algorithms have two versions:
 * - The base version which takes a value argument
 * - An `_if()` version which takes a predicate argument
 */

#include <algorithm> // find_if
#include <iostream>  // cout
#include <string>    // string
#include <vector>    // vector

using namespace std;

// Functor
class ge_5 {
  public:
    // Overloaded () operator
    // Takes an std::string, returns true if more than 5 characters
    bool operator()(const string &s) const { return (s.size() > 5); }
};

// Functor
class ge_n {
  private:
    const size_t n;

  public:
    ge_n(const size_t n) : n(n) {}
    bool operator()(const string &str) const { return str.size() > n; }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 067-algorithms_with_if_versions.cpp && ./a.out
int main() {
    vector<string> names{"Dilbert", "PHB", "Dogbert", "Asok", "Ted", "Alice", "Wally"};

    ge_5 long_enough;
    for (auto name : names) {
        if (long_enough(name)) {
            cout << "Loop: the first name with > 5 characters is \"" << name << "\"\n";
            break;
        }
    }

    vector<string>::const_iterator res;

    // Find the first element with more than 5 characters
    res = find_if(cbegin(names), cend(names), ge_5()); // Pass a functor object as predicate
    if (res != cend(names))
        cout << "find_if with ge_5(): the first name with > 5 characters is \"" << *res << "\"\n";

    // Find the first element with more than 5 characters
    res = find_if(cbegin(names), cend(names), ge_n(5)); // Pass a functor object as predicate
    if (res != cend(names))
        cout << "find_if with ge_n(5): the first name with > 5 characters is \"" << *res << "\"\n";

    // Find the first element with not more than 5 characters
    res = find_if_not(cbegin(names), cend(names), ge_5()); // Pass a functor object as predicate
    if (res != cend(names))
        cout << "find_if_not with ge_5(): the first word with <= 5 characters is \"" << *res
             << "\"\n";
}
