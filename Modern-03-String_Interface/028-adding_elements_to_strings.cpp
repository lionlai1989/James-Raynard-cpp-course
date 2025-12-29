#include <iostream>
#include <string>

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 028-adding_elements_to_strings.cpp && ./a.out
int main() {
    string s1{"Hello"};
    s1.append(" world"s);
    cout << "s1 = " << s1 << endl;

    string s2{"Hello"};
    s2.append("wow!!!!"s, 3, 2);
    cout << "s2 = " << s2 << endl;

    string s3{"for"};
    s3.insert(2, "lde"s);
    cout << "s3 = " << s3 << endl;

    string s4{"care"};
    s4.insert(1, "omp"s);
    cout << "s4 = " << s4 << endl;

    string s5(2, 'x');
    s5.insert(1, "trombone"s, 4, 2);
    cout << "s5 = " << s5 << endl;

    string s6("cash");
    s6.insert(1, 3, 'r');
    cout << "s6 = " << s6 << endl;

    string s7{"Hello"};
    auto opos = s7.find('o');
    if (opos != string::npos)
        s7.insert(opos, 2, 'o');
    cout << "s7 = " << s7 << endl;

    string s8{"word"};
    auto last = end(s8) - 1; // Get iterator to last character
    s8.insert(last, 'l');
    cout << "s8 = " << s8 << endl;

    string s9{"ski"};
    auto last2 = end(s9); // Get iterator to last character plus one
    s9.insert(last2, 2, 'l');
    cout << "s9 = " << s9 << endl;

    /**
     * Iterator Invalidation
     * When we insert into a string, the string may need to reallocate its storage
     * If it does, then all iterators, references, and pointers into the string become invalid. To
     * solve this issue, we need to update the iterator to point to the new location of the element
     * in the string. For example, the following code has runtime error:
     * ```
     * double free or corruption (!prev)
     * Aborted (core dumped)
     * ```
     */
    string str{"orld"};
    cout << "str = " << str << endl;

    auto first = begin(str);

    str.insert(end(str), 16, 'd'); // Add enough elements to force a reallocation of the string

    // first = begin(str); // Get the new value of the iterator. Uncomment to see the effect

    str.insert(first, 'w');
    cout << "str = " << str << endl;
}
