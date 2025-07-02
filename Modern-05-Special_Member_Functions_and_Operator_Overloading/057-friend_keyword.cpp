#include <iostream>
#include <string>

using namespace std;

class Test {
  private:
    int i{42};
    string s{"Hello"};

  public:
    friend void print(const Test &);
};

// A non-member function can access all the private and public members of Test.
void print(const Test &test) { cout << "i = " << test.i << ", s = " << test.s << endl; }

class Test2 {
  private:
    int i{42};
    string s{"Hello"};

  public:
    /**
     * Declare a class Example to be a friend, which allows the Example class to access all the
     * Test2's members.
     */
    friend class Example;
};

class Example {
  public:
    // A member function of Example can access all the private and public members of Test2.
    void print(const Test2 &test) { cout << "i = " << test.i << ", s = " << test.s << endl; }
};

class Test3 {
    int i{42};
    string s{"Hello"};

  public:
    void print() const { cout << "i = " << i << ", s = " << s << endl; }
};

void print2(const Test3 &test) { test.print(); }

// g++ -std=c++20 -Wall -Wextra -pedantic 057-friend_keyword.cpp && ./a.out
int main() {
    /**
     * "friend" functions:
     * Normally a non-member function can only access a class's public members. The class can
     * declare a non-member function to be a "friend", which allows the function to access all the
     * class's members.
     */

    Test test;
    print(test);

    cout << "--------------------------------" << endl;

    Test2 test2;
    Example ex;
    ex.print(test2);

    cout << "--------------------------------" << endl;

    /**
     * Some programmers dislike "friend" because it reduces encapsulation.
     *
     * To avoid using friend, we can create a member function which implements the functionality of
     * the operator. The member function has direct access to all the class's members. And a
     * non-member function then calls this member function.
     */
    Test3 test3;
    print2(test3);

    return 0;
}
