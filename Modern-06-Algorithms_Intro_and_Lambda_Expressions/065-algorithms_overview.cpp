#include <algorithm> // find
#include <iostream>  // cout
#include <string>    // string

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 065-algorithms_overview.cpp && ./a.out
int main() {
    string str{"Hello world"};
    cout << "String: ";

    for (auto c : str)
        cout << c << ",";
    cout << "\n";

    /**
     * Search string for first occurrence of 'l'
     *
     * string::find() returns an index.
     *
     * std::find() returns an iterator. Why?
     * Because some algorithms do not have the concept of index.
     */
    string::const_iterator res_iter = find(cbegin(str), cend(str), 'l');
    size_t res_idx = str.find('l');

    // Check if we found it
    if (res_iter != cend(str)) {
        cout << "Found a matching element at index: " << res_iter - str.cbegin() << endl;
    }
    if (res_idx != string::npos) {
        cout << "Found a matching element at index: " << res_idx << endl;
    }

    cout << "At this point in the string: " << endl;
    for (auto it = res_iter; it != str.cend(); ++it)
        cout << *it;
    cout << endl;
    for (size_t i = res_idx; i < str.size(); ++i)
        cout << str[i];
    cout << endl;
}
