/**
 * Template specialization:
 * When we write a class template, we will get the same behavior for all types that we instantiate
 * it with. Sometimes, we want to provide a different behavior for a specific type. This is called
 * template specialization. E.g., vector<bool> is a specialization of vector<T> for bool type.
 *
 * Usually, the template specialization follows immediately after the generic template:
 *
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

// Generic Vector class
template <typename T> class Vector {
  public:
    void identify() { cout << "Vector<T>\n"; }
};

// Partial specialization for pointers follows immediately after the generic template
template <typename T> class Vector<T *> {
  public:
    void identify() { cout << "Vector<T *>\n"; }
};

// Specialization of Vector class for bool type follows immediately after the generic template
template <> class Vector<bool> {
  public:
    void identify() { cout << "Vector<bool>\n"; }
};

// Generic Reverse function
template <typename T> void Reverse(T &container) {
    cout << "Calling generic Reverse\n";
    std::reverse(begin(container), end(container));
}

// Specialization of Reverse function for std::list
// list is itself a class template
// The element type is part of the list's type
// We need to provide a template parameter for std::list's element type
template <typename Elem> void Reverse(std::list<Elem> &container) {
    cout << "Calling specialization of Reverse for list<Elem>\n";
    container.reverse();
}

// g++ -std=c++20 -Wall -Wextra -pedantic 199-template_specialization.cpp && ./a.out
int main() {
    Vector<int> ivec;      // generic template
    Vector<int *> ptr_vec; // partial specialization
    Vector<bool> bvec;     // specialization

    cout << "Vector<int> identify: ";
    ivec.identify();
    cout << "Vector<int *> identify: ";
    ptr_vec.identify();
    cout << "Vector<bool> identify: ";
    bvec.identify();

    cout << "--------------------------------" << endl;

    vector<int> vec{3, 1, 4, 1, 5, 9};

    cout << "vec before calling Reverse()\n";
    for (auto v : vec)
        cout << v << ", ";
    cout << "\n";

    Reverse(vec); // Call generic Reverse

    cout << "vec after calling Reverse()\n";
    for (auto v : vec)
        cout << v << ", ";
    cout << "\n";

    list<int> lis{3, 1, 4, 1, 5, 9};

    cout << "\nlist before calling Reverse()\n";
    for (auto l : lis)
        cout << l << ", ";
    cout << "\n";

    Reverse(lis); // Call specialized Reverse

    cout << "lis after calling Reverse()\n";
    for (auto l : lis)
        cout << l << ", ";
    cout << "\n";
}
