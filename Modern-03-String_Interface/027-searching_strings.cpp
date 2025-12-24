#include <iostream> // cout, endl
#include <string>   // string

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 027-searching_strings.cpp && ./a.out
int main() {
    string str{"Hello world"};
    cout << "Initial contents of str: " << str << endl;
    size_t pos;

    pos = str.find('o');
    if (pos != string::npos) { // npos: no position
        cout << R"(First occurrence of 'o' is at index )" << pos << endl;
    } else {
        cout << R"(Could not find 'o' in the string)" << endl;
    }
    pos = str.find("or");
    if (pos != string::npos) {
        cout << R"(First occurrence of "or" is at index )" << pos << endl;
    } else {
        cout << R"(Could not find "or" in the string)" << endl;
    }
    pos = str.find(string{'O'});
    if (pos != string::npos) {
        cout << R"(First occurrence of 'O' is at index )" << pos << endl;
    } else {
        cout << R"(Could not find 'O' in the string)" << endl;
    }

    cout << "--------------------------------" << endl;

    cout << "Initial contents of str: " << str << endl;
    pos = str.find('o');
    if (pos != string::npos) {
        str[pos] = 'p';
    } else {
        cout << "Could not find the search string\n";
    }
    cout << "Final contents of str:   " << str << endl;

    cout << "--------------------------------" << endl;

    cout << "Initial contents of str: " << str << endl;
    pos = str.rfind('o');
    if (pos != string::npos) {
        str[pos] = 'p';
    } else {
        cout << "Could not find the search string\n";
    }
    cout << "Final contents of str:   " << str << endl;

    cout << "--------------------------------" << endl;

    cout << "Initial contents of str: " << str << endl;
    string vowels{"aeiou"};
    cout << "First vowel is at index " << str.find_first_of(vowels) << endl;
    cout << "Last vowel is at index " << str.find_last_of(vowels) << endl;
    cout << "First non-vowel is at index " << str.find_first_not_of(vowels) << endl;
    cout << "Last non-vowel is at index " << str.find_last_not_of(vowels) << endl;
}
