#include <fstream>  // ofstream
#include <iostream> // cout, endl, ostream
#include <string>   // string, operator""s

using namespace std;

class Test {
  private:
    int i{42};
    string str{"Hello"s};

  public:
    // A member function which prints out the data members of the Test class
    void print() const { cout << "Test: i = " << i << ",  str = " << str << endl; }
};

class Test2 {
  private:
    int i{42};
    string str{"Hello"s};

  public:
    /**
     * A member function which prints out the data members of the Test class.
     * This version will work with any output stream such as cout, ofstream, ostringstream, etc.
     *
     * We pass the output stream by reference for two reasons:
     * 1. "ostream" cannot be copied so we cannot pass it by value
     * 2. "ostream" will be modified inside the function
     */
    void print(ostream &os) const { os << "Test2: i = " << i << ", str = " << str << endl; }
};

class Test3 {
  private:
    int i{42};
    string str{"Hello"s};

  public:
    void print(ostream &os) const { os << "Test3: i = " << i << ", str = " << str; }

    /**
     * The non-member operator<< defined below does NOT need to be a friend of Test3 because it
     * doesn't access Test3's private members directly. Instead it calls this public print(ostream&)
     * member which provides controlled access to the object's data. This preserves encapsulation
     * and is the preferred pattern: implement operator<< as a non-friend non-member that uses
     * public accessors (or a public print helper).
     *
     * Declare operator<< as friend only if the operator must access private members directly and
     * you intentionally want to allow that.
     * friend ostream &operator<<(ostream &os, const Test3 &test);
     */
};
/**
 * Overloaded output operator <<  which prints out the data members of the Test class.
 * This calls the Test class's print() method and returns the ostream.
 * ostream must be returned by reference for two reasons:
 * 1. "ostream" cannot be copied so we cannot return it by value
 * 2. We want to allow chaining of the << operator, e.g., cout << test1 << test2;
 */
ostream &operator<<(ostream &os, const Test3 &test) {
    test.print(os);
    return os;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 064-output_operator.cpp && ./a.out
int main() {
    Test test;
    // cout << test << endl; // Error: no match for operator <<
    test.print();

    cout << "\n--------------------------------\n" << endl;

    Test2 test2;

    test2.print(cout); // Pass cout to print on the console

    ofstream ofile("test.txt");
    if (!ofile.is_open()) {
        cout << "could not open test.txt" << endl;
        return -1;
    }
    test2.print(ofile); // Pass ofile to print in a file

    cout << "\n--------------------------------\n" << endl;

    Test3 test3;

    cout << test3 << endl;

    ofile << test3 << endl;

    ofile.close();
}