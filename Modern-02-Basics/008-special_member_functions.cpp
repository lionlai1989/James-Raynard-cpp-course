#include <iostream> // cin, cout
#include <string>   // string

using namespace std;

class Test {
  private:
    int i;
    string str;

  public:
    // constructor
    Test(int i, string str) : i(i), str(str) { cout << "constructor" << endl; }

    // copy constructor
    Test(const Test &other) : i(other.i), str(other.str) { cout << "copy constructor" << endl; }

    // copy assignment operator. Explain why it needs to use a reference to other.
    Test &operator=(const Test &other) {
        cout << "copy assignment operator" << endl;
        i = other.i;
        str = other.str;
        return *this;
    }

    void print() const { cout << "i: " << i << " str: " << str << endl; }

    // destructor
    ~Test() { cout << "destructor" << endl; }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 008-special_member_functions.cpp && ./a.out
int main() {
    Test t1(1, "Hello");
    Test t2 = t1;
    Test t3(2, "World");
    t3 = t1;
    t1.print();
    t2.print();
    t3.print();
    return 0;
}
