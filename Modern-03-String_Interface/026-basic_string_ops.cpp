#include <iostream> // cout
#include <string>   // string

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 026-basic_string_ops.cpp && ./a.out
int main() {
    string str{"Hello world"};
    str[1] = 'a'; // Change 2nd character to 'a'

    string s1 = str.substr(6);       // Returns "world"
    string s2 = str.substr(6, 2);    // Returns "wo"
    const char *pchar = str.c_str(); // null-terminated C-style string

    cout << str << endl;
    cout << s1 << endl;
    cout << s2 << endl;
    cout << pchar << endl; // cout overload operator<< for C-style strings
    cout << static_cast<const void *>(pchar) << endl; // print numerical value of the pointer

    cout << "--------------------------------" << endl;

    // Default constructor
    string empty;
    cout << "empty has " << empty.size() << " characters: " << empty << endl;

    // C-style string
    string hi{"Hello"};
    cout << "hi has " << hi.size() << " characters: " << hi << endl;

    // Repeated value
    string triple_x(3, 'x');
    cout << "triple_x has " << triple_x.size() << " characters: " << triple_x << endl;

    // Initializer list
    string howdy{'h', 'o', 'w', 'd', 'y'};
    cout << "howdy has " << howdy.size() << " characters: " << howdy << endl;

    // substring
    string hello(hi, 1); // "ello"
    cout << "hello has " << hello.size() << " characters: " << hello << endl;

    string hello2(hi, 1, 3); // "ell"
    cout << "hello2 has " << hello2.size() << " characters: " << hello2 << endl;
}
