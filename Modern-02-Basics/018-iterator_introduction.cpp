#include <iostream> // cout
#include <vector>   // vector

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 018-iterator_introduction.cpp && ./a.out
int main() {
    const char cstr[] = {'H', 'e', 'l', 'l', 'o'};
    const char *pEnd = cstr + 5; // Pointer to element after last element
    const char *p = cstr;        // Start of array
    while (p != pEnd) {          // Gone past last element?
        cout << *p << ", ";
        ++p; // Increment to move to next element
    }
    // Dangerous! The final value of the pointer p is not the address of any element in the array.

    cout << endl << "--------------------------------" << endl;

    /**
     * iterator is a type that points to an element of a container.
     * begin() returns an iterator to the first element of the container.
     * end() returns an iterator to the element after the last element of the container.
     * end() is an invalid iterator and must not be dereferenced.
     */
    string str{"Hello"};
    for (string::iterator sit = str.begin(); sit != str.end(); ++sit) {
        cout << *sit << ", ";
    }

    cout << endl << "--------------------------------" << endl;

    vector<int> vec{3, 1, 4, 1, 5, 9};
    vector<int>::iterator vit = vec.begin(); // Start of string
    while (vit != vec.end()) {
        cout << *vit << ", ";
        ++vit;
    }
}
