#include <iostream> // cout
#include <string>   // string

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 016-string_literals.cpp && ./a.out
int main() {
    // The traditional C-style string literal is an array of const char, terminated by a null character
    const char *cca = "Hello, world!";
    cout << "cca: " << cca << endl;

    string str = "Hello, world!"s;
    cout << "str: " << cca << endl;

    // Pay attention to the suffix s, which makes the string literal a std::string.
    cout << "std::string literal: " << "Hello"s + ", world!"s << endl;

    cout << endl;

    // String literal with escaped characters
    string url = "<a href=\"file\">C:\\\"Program Files\"\\</a>\\n";
    cout << "URL is           " << url << endl << endl;

    // Raw string literal with unescaped characters
    string raw_url = R"(<a href="file">C:\"Program Files"\</a>\n)";
    cout << "Raw URL is       " << raw_url << endl << endl;

    // Raw string literal with delimiter x
    string delimited_url = R"x(<a href="file">C:\"Program Files (x86)"\</a>\n)x";
    cout << "Delimited URL is " << delimited_url << endl << endl;
}
