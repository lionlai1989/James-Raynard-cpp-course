/**
 * Stream State Member Functions
 * C++ streams have member functions to check the state of the stream.
 * good() - returns true if the stream is in a good state
 * fail() - returns true if there was a recoverable error
 * bad() - returns true if there was an unrecoverable error
 */

#include <iostream> // cin, cout, endl

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic checking.cpp && ./a.out
int main() {
    int x{0};

    cout << "Please enter a number: ";
    cin >> x;

    if (cin.good()) // Successfully read an int
        cout << "You entered the number " << x << "\n";
    else if (cin.fail()) // Not an int. Probably a user error - try again
        cout << "Please try again and enter a number\n";
    else if (cin.bad()) // A serious error occurred
        cout << "Something has gone seriously wrong\n";
}
