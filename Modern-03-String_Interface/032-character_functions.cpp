/**
 * Character functions
 * The C++ standard library has a number of character functions inherited from the C standard
 * library. These functions are defined in the header <cctype>.
 */

#include <cctype>   // isupper, islower, ispunct, isspace, toupper
#include <iostream> // cin, cout
#include <string>   // string

using namespace std;

// Return true if input starts with 'Y' or 'y'
bool yes_or_no(const string &input) {
    char c = input[0];

    if (toupper(c) == 'Y') // Is c equal to 'Y' or 'y'?
        return true;
    return false;
}

// Case-insensitive string equality. Returns true if lhs and rhs are equal, otherwise false
bool equal_strings(const string &lhs, const string &rhs) {
    // FIrst we compare the lengths of the two strings.
    // If the two strings have different lengths, they cannot be equal.
    if (lhs.size() != rhs.size())
        return false;

    // We now know that the strings have the same lengths.

    // Get constant iterators to the first element in each string
    auto lit = cbegin(lhs);
    auto rit = cbegin(rhs);

    // We iterate over the two strings, comparing the current character from each string.
    // If either iterator is equal to cend(), we know that we have seen all the characters
    // and the loop terminates.
    // On each iteration, we look for a mismatch. If the character has a different value in the two
    // strings, then we know the strings are different and we can terminate the loop.
    while (lit != cend(lhs) && rit != cend(rhs)) {
        // We use toupper to compare the upper-case version of the two characters
        if (toupper(*lit) != toupper(*rit))
            return false; // Mismatch - return false
                          // No mismatch found - we move to the next character in each string
        ++lit;
        ++rit;
    }

    // If we got here, we looked at all the characters in the string and not found
    // any mismatches. The strings must be equal.
    return true;
}

// g++ -std=c++17 -Wall -Wextra -pedantic 032-character_functions.cpp && ./a.out
int main() {
    string hello{"Hello, World!"};

    for (auto c : hello) {
        if (isupper(c))
            cout << c << " is an upper case letter\n";
        if (islower(c))
            cout << c << " is a lower case letter\n";
        if (ispunct(c))
            cout << c << " is a punctuation character\n";
        if (isspace(c))
            cout << "\'" << c << "\'" << " is a whitespace character\n";
    }

    cout << "--------------------------------" << endl;

    string input;
    cout << "Do you want to enter a string which starts with Y or y?" << endl;
    cin >> input;
    if (yes_or_no(input))
        cout << "Evidently you do!\n";
    else
        cout << R"(I will take that as a "no"!)" << endl; // Raw string literal

    cout << "--------------------------------" << endl;

    string a{"one"}, b{"two"}, c{"ONe"};
    cout << a << " and " << b << " are " << (equal_strings(a, b) ? "" : "not ") << "equal\n";
    cout << b << " and " << c << " are " << (equal_strings(b, c) ? "" : "not ") << "equal\n";
    cout << a << " and " << c << " are " << (equal_strings(a, c) ? "" : "not ") << "equal\n";
}
