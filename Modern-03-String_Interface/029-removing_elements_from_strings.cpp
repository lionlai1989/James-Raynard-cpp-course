/**
 * Memory Reallocation: The primary cost driver is often memory management. If a modification (like
 * an insertion) causes the string to exceed its current allocated capacity, the library must:
 *
 *    1. Allocate a larger block of memory.
 *    2. Copy all existing characters to the new memory location.
 *    3. Deallocate the old memory block.
 *
 * This is an expensive operation that typically results in amortized linear time complexity, but
 * can be much slower in specific instances.
 *
 * Data Shifting: Operations like inserting into or erasing from the middle of a string require
 * moving all the subsequent characters to their new positions in memory. This is a linear time
 * operation (O(N), where N is the number of characters after the insertion/deletion point).
 *
 * Appending vs. Middle Insertion: Appending to the end is generally more efficient than inserting
 * into the middle because it only involves data shifting when the capacity is exceeded.
 */

#include <iostream>
#include <string>

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 029-removing_elements_from_strings.cpp && ./a.out
int main() {
    string s1{"Hello"};
    cout << "s1 = " << s1 << endl;
    s1.erase(3, 1); // Erase fourth character
    cout << "s1 = " << s1 << endl;
    auto opos = s1.find('e'); // First occurrence of 'e'
    if (opos != string::npos)
        s1.erase(opos, 2); // Erase two elements starting with the first instance of 'e'
    cout << "s1 = " << s1 << '\n' << endl;

    string s2{"hello"};
    cout << "s2 = " << s2 << endl;
    auto first = begin(s2); // Get iterator to first character
    s2.erase(first);        // Erase it
    cout << "s2 = " << s2 << endl;
    s2.erase(begin(s2) + 1, end(s2) - 1); // Erase all characters except first and last
    cout << "s2 = " << s2 << '\n' << endl;

    string s3{"Say Hello!"};
    cout << "s3 = " << s3 << endl;
    auto gdx = s3.find('H');
    s3.replace(gdx, 5, "Goodbye");
    cout << "s3 = " << s3 << '\n' << endl;

    string s4{"Say Goodbye"};
    cout << "s4 = " << s4 << endl;
    s4.replace(begin(s4), begin(s4) + 3, "Wave");
    cout << "s4 = " << s4 << '\n' << endl;

    string s5{"Hello"};
    cout << "s5 = " << s5 << endl;
    s5.assign("Goodbye");
    cout << "s5 = " << s5 << endl;
}
