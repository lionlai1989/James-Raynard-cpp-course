#include <iostream> // cout, endl
#include <string>   // string

using namespace std;

class String {
  private:
    string s;

  public:
    // Constructors
    String(const string &s) : s(s) { cout << "Constructor" << endl; }

    // Copy constructor
    String(const String &arg) : s(arg.s) { cout << "Copy constructor" << endl; }

    void print() { cout << s << endl; }
};

String make_string(const String s) { return String(s); }

// g++ -std=c++17 -Wall -Wextra -pedantic 048-copy_constructor.cpp && ./a.out
int main() {
    String w{"world"s}; // Call constructor
    String bang{w};     // Call copy constructor
    String bang2 = w;   // Call copy constructor

    cout << "w = ";
    w.print();
    cout << "bang = ";
    bang.print();
    cout << "bang2 = ";
    bang2.print();

    String s = make_string(w);
}
