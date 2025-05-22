#include <iostream>
#include <string>

using namespace std;

class String {
    string s;

  public:
    String() : s("") { cout << "Default constructor" << endl; }
    String(const string &s) : s(s) { cout << "Parameterized constructor" << endl; }

    String(const String &other) : s(other.s) { cout << "Copy constructor" << endl; }

    String &operator=(const String &other) {
        cout << "Assignment operator" << endl;
        s = other.s;
        return *this;
    }

    void print() { cout << s << endl; }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 049-assignment_operator.cpp && ./a.out
int main() {
    String a{"hello"};
    String b{"world"};
    String c;
    a = b = c;

    cout << "a = ";
    a.print();
    cout << "b = ";
    b.print();
    cout << "c = ";
    c.print();
}
