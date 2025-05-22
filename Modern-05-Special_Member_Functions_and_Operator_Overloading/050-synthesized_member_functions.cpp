#include <iostream> // cout, endl
#include <string>   // string

using namespace std;

class Test2 {
  private:
    int i;
    string str;

  public:
    Test2(int i, const string &s) : i(i), str(s) {}
    void print() { cout << "i = " << i << ", str = " << str << endl; }
};

class Test {
  private:
    int i;
    string str;

  public:
    /**
     * If we don't define special member functions, the compiler will often "synthesize" them for us.
     *
     * 1. Default constructor
     * 2. Copy constructor
     * 3. Assignment operator
     * 4. Destructor
     *
     * Drawbacks of synthesized member functions:
     * - Built-in types members are default initialized.
     * - Pointer members are "shallow copied".
     * In these cases, we should define our own special member functions:
     * - Implement a default contructor which initializes the built-in types members correctly.
     * - Implement copy constructor and copy assignment operator which deep copy the pointer members.
     */
    // Test(int i, const string& s) : i(i), str(s) {}
    // Test() {}
    // Test(const Test& other) : i(other.i), str(other.str) {}
    // Test& operator =(const Test& other) { i = other.i; str = other.str; }
    // ~Test() {}
    void print() { cout << "i = " << i << ", str = " << str << endl; }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 050-synthesized_member_functions.cpp && ./a.out
int main() {
    Test test;
    cout << "test after default constructor: ";
    test.print();

    Test2 test2(7, "Goodbye"s);
    cout << "test2 after default constructor: ";
    test2.print();
}
