/**
 * List operations
 * std::list is a sequence container that allows constant time insertions and deletions anywhere
 * in the sequence (given an iterator to the position).
 *
 * However, random access is not supported. E.g., we cannot access the element at a given position
 * in constant time. This means that the generic std::sort() will not work because it requires
 * random access to container elements. Instead, we have to use list's sort() member function.
 *
 * In some cases, the list's member function versions of algorithms are more efficient than the
 * generic versions. Thus, we should use the member function versions when possible.
 */

#include <algorithm>    // sort
#include <forward_list> // forward_list
#include <iostream>     // cout, endl
#include <iterator>     // advance
#include <list>         // list

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 106-list_operations.cpp && ./a.out
int main() {
    list<int> l{4, 3, 1}; // Create a list object

    cout << "Initial elements in list" << endl;
    for (auto el : l) // Use a range-for loop to display all the elements
        cout << el << ", ";
    cout << endl;

    // sort(begin(l), end(l)); // Does not compile
    l.sort(); // Sort the list

    cout << "Elements in list after sorting" << endl;
    for (auto el : l)
        cout << el << ", ";
    cout << endl;

    l.remove(3); // Remove element with value 3

    cout << "Elements in list after removing 3" << endl;
    for (auto el : l)
        cout << el << ", ";
    cout << endl;

    cout << "--------------------------------" << endl;

    list<int> list1{1, 12, 6, 24};
    list<int> list2{9, 3, 14};

    cout << "Elements in list1" << endl;
    for (auto el : list1)
        cout << el << ", ";
    cout << endl;

    cout << "Elements in list2" << endl;
    for (auto el : list2)
        cout << el << ", ";
    cout << endl;

    list1.sort();
    list2.sort();
    // list.merge() removes elements from the argument list and merges them into the "this" list
    list1.merge(list2); // list1 now contains 1, 3, 6, 9, 12, 14, 24 and list2 is empty

    cout << "Elements in list1 after merge" << endl;
    for (auto el : list1)
        cout << el << ", ";
    cout << endl;

    cout << "Elements in list2 after merge" << endl;
    for (auto el : list2)
        cout << el << ", ";
    cout << endl;

    cout << "--------------------------------" << endl;

    list<int> list3{1, 12, 6, 24};
    list<int> list4{9, 3, 14};

    cout << "Elements in list3" << endl;
    for (auto el : list3)
        cout << el << ", ";
    cout << endl;

    cout << "Elements in list4" << endl;
    for (auto el : list4)
        cout << el << ", ";
    cout << endl;

    auto p = begin(list3);
    advance(p, 1);          // p is an iterator to the second element of list3 (with value 12)
    list3.splice(p, list4); // Insert elements of list4 before p

    cout << "Elements in list3 after splice" << endl;
    for (auto el : list3)
        cout << el << ", ";
    cout << endl;

    cout << "Elements in list4 after splice" << endl;
    for (auto el : list4)
        cout << el << ", ";
    cout << endl;

    cout << "--------------------------------" << endl;

    forward_list<int> fl1{1, 12, 6, 24};
    forward_list<int> fl2{9, 3, 14};

    cout << "Elements in fl1" << endl;
    for (auto el : fl1)
        cout << el << ", ";
    cout << endl;

    cout << "Elements in fl2" << endl;
    for (auto el : fl2)
        cout << el << ", ";
    cout << endl;

    auto tmp = begin(fl1); // tmp is an iterator to the first element of fl1 (with value 1)

    // Why forward_list does not have a splice() member function?
    // Because forward_list is a singly linked list, it does not point to the previous element.
    fl1.splice_after(tmp, fl2); // Insert elements of fl2 after tmp

    cout << "Elements in fl1 after splice" << endl;
    for (auto el : fl1)
        cout << el << ", ";
    cout << endl;

    cout << "Elements in fl2 after splice" << endl;
    for (auto el : fl2)
        cout << el << ", ";
    cout << endl;
}
