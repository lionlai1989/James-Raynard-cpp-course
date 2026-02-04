#include <algorithm> // equal
#include <cctype>    // toupper
#include <iostream>  // cout, endl
#include <string>    // string, cbegin, cend

using namespace std;

// Case-insensitive string equality. Returns true if lhs and rhs are equal, otherwise false
bool equal_strings(const string &lhs, const string &rhs) {
    // If the two strings have different lengths
    if (lhs.size() != rhs.size())
        return false;

    // If the two strings have the same lengths...
    auto lit = cbegin(lhs);
    auto rit = cbegin(rhs);

    while (lit != cend(lhs) && rit != cend(rhs)) { // Iterate over both strings
        if (toupper(*lit) != toupper(*rit))        // Convert to upper case and compare
            return false;                          // Characters are different
        ++lit;
        ++rit;
    }
    return true; // No differences found
}

void test(const string &str1, const string &str2) {
    cout << str1 << " and " << str2 << " are" << (equal_strings(str1, str2) ? "" : " not")
         << " equal" << endl;
}

bool equal_strings2(const string &lhs, const string &rhs) {
    /**
     * The equal() algorithm compares the elements in two containers, ct1 and ct2.
     * It returns false as soon as it encounters a pair of elements that are not equal.
     *   If ct1 has more elements than ct2, it returns false.
     *   If ct2 has more elements than ct1, the extra elements in ct2 are ignored.
     * By default, it uses the == operator to compare the elements.
     * However, we can provide a custom comparison function to compare the elements.
     * In this case, we provide a lambda expression to compare the elements.
     */
    return equal(cbegin(lhs), cend(lhs), cbegin(rhs), cend(rhs),
                 [](char lc, char rc) { return toupper(lc) == toupper(rc); });
}

void test2(const string &str1, const string &str2) {
    cout << str1 << " and " << str2 << " are" << (equal_strings(str1, str2) ? "" : " not")
         << " equal" << endl;
}

// g++ -std=c++17 -Wall -Wextra -pedantic 069-lambda_expressions_practical.cpp && ./a.out
int main() {
    test("lambda", "Lambda");
    test("lambda", "lambada");

    test2("lambda", "Lambda");
    test2("lambda", "lambada");
}
