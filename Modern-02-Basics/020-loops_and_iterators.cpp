#include <iostream> // cout
#include <string>   // string
#include <vector>   // vector

using namespace std;

// g++ -std=c++20 -Wall -Wextra -pedantic 020-loops_and_iterators.cpp && ./a.out
int main() {
    string str{"Hello"};
    const string str2{"World"};

    // If we want to prevent the loop from modifying the string, we can use a const_iterator.
    cout << "Const iterator on non-const container: ";
    for (string::const_iterator it = str.begin(); it != str.end(); ++it) {
        cout << *it << ", ";
        // *it = 'X'; // Error!
    }
    cout << endl;

    // const containers must use a const_iterator.
    cout << "Const iterator on const container: ";
    for (string::const_iterator it = str2.begin(); it != str2.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;

    // We can use a reverse iterator to iterate backwards from the last element.
    // rbegin() returns a reverse iterator to the last element.
    // rend() returns a reverse iterator to the element before the first element.
    cout << "Reverse iterator: ";
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;

    // C++ has const forms of begin() and end().
    cout << "Non-const iterator: ";
    for (auto it = str.begin(); it != str.end(); ++it)
        cout << *it << ", ";

    cout << endl << "Const iterator: ";
    for (auto it = str.cbegin(); it != str.cend(); ++it)
        cout << *it << ", ";

    cout << endl << "Non-const reverse iterator: ";
    for (auto it = str.rbegin(); it != str.rend(); ++it)
        cout << *it << ", ";

    cout << endl << "Const reverse iterator: ";
    for (auto it = str.crbegin(); it != str.crend(); ++it)
        cout << *it << ", ";

    cout << endl;

    // C++ has non-member functions begin() and end(), which also works for built-in arrays.
    int arr[] = {1, 2, 3, 4, 5};

    cout << "Non-const iterator: ";
    for (auto it = begin(arr); it != end(arr); ++it)
        cout << *it << ", ";

    cout << endl << "Const iterator: ";
    for (auto it = cbegin(arr); it != cend(arr); ++it)
        cout << *it << ", ";

    cout << endl << "Non-const reverse iterator: ";
    for (auto it = rbegin(arr); it != rend(arr); ++it)
        cout << *it << ", ";

    cout << endl << "Const reverse iterator: ";
    for (auto it = crbegin(arr); it != crend(arr); ++it)
        cout << *it << ", ";
    cout << endl;

    // Range-based for loop.
    vector<int> vec{1, 2, 3, 4};

    cout << "Vector elements: " << endl;
    for (auto el : vec) {
        // el is a copy of the element. Any changes to el will not affect vec.
        cout << el << ", ";
        el = 0;
    }

    cout << endl << "Adding 2 to each element" << endl;
    for (auto &el : vec) {
        // el is a reference to the element. Any changes to el will affect vec.
        el += 2;
    }

    cout << endl << "Modified vector elements: " << endl;
    for (auto el : vec) {
        cout << el << ", ";
    }

    return 0;
}
