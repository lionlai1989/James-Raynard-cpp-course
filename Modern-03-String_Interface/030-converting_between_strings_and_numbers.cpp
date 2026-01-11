#include <iostream> // cout, endl
#include <string>   // string, to_string, stoi, stod

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 030-converting_between_strings_and_numbers.cpp && ./a.out
int main() {
    /**
     * std::to_string()
     * - Returns its argument as a std::string
     * - Overloads all integer and floating-point types
     */
    cout << to_string(3.14159) << endl;

    cout << "--------------------------------" << endl;

    /**
     * std::stoi()
     * The first argument is a string to convert to an integer.
     */
    cout << stoi("42"s) << endl; // Displays 42

    cout << "--------------------------------" << endl;

    /**
     * std::stoi()
     * The second argument is a pointer to a size_t that will be set to the
     * number of characters processed.
     */
    string str{"  314 159"}; // Leading whitespace is ignored
    size_t n_processed;
    auto i = stoi(str, &n_processed);
    if (n_processed < str.size()) {
        cout << "Non-numeric character at index " << n_processed << endl;
    }
    cout << "Result of conversion: " << i << endl; // Displays 314

    // stoi("abcdef"s); // Cannot be converted - throws exception

    cout << "--------------------------------" << endl;

    /**
     * std::stoi()
     * The string is assumed to be a base-10 integer. The third argument
     * specifies the base of the number in the string.
     */
    auto x = stoi("2a", nullptr, 16);
    cout << "Result of conversion: " << x << endl; // Displays 42

    cout << "--------------------------------" << endl;

    /**
     * std::stod()
     * returns double and does not support different bases
     */
    string pi{"3.14159"};
    cout << "stoi:\n";
    cout << stoi(pi, &n_processed) << endl; // Displays 3
    cout << n_processed << " characters processed\n\n";
    cout << "stod:\n";
    cout << stod(pi, &n_processed) << endl; // Displays 3.14159
    cout << n_processed << " characters processed\n\n";
}
