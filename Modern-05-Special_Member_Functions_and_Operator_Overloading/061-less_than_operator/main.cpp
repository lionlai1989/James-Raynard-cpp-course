/**
 * Less-than operator
 *
 * The Standard Library uses the less-than operator for sorting and ordering.
 *
 * The < operator is sufficient to perform all comparisons operations.
 *  - a == b: "!(a < b) && !(b < a)"
 *  - a >= b: "!(a < b)"
 *  - a > b: "b < a"
 *  - a <= b: "!(b < a)"
 *  - a != b: "(a < b) || (b < a)"
 *
 */

#include <algorithm> // sort, begin, end
#include <iostream>  // cout, endl, boolalpha
#include <vector>    // vector

#include "student.h"

using namespace std;

// Choose to sort by name or by ID
// g++ -std=c++20 -Wall -Wextra -pedantic student_by_name.cpp main.cpp && ./a.out
// g++ -std=c++20 -Wall -Wextra -pedantic student_by_id.cpp main.cpp && ./a.out
int main() {
    student stu1("John Smith", 561234);
    student stu2("John Smith", 453811);
    student stu3("Jack Jones", 692837);

    cout << "stu1: ";
    stu1.print();
    cout << "stu2: ";
    stu2.print();
    cout << "stu3: ";
    stu3.print();
    cout << boolalpha << endl; // Set output stream format
    cout << "stu1 < stu2: " << (stu1 < stu2) << endl;
    cout << "stu1 < stu3: " << (stu1 < stu3) << endl << endl;
    cout << "stu2 < stu1: " << (stu2 < stu1) << endl;
    cout << "stu2 < stu3: " << (stu2 < stu3) << endl << endl;
    cout << "stu3 < stu1: " << (stu3 < stu1) << endl;
    cout << "stu3 < stu2: " << (stu3 < stu2) << endl;

    cout << "--------------------------------" << endl;

    vector<student> students = {stu1, stu2, stu3};
    cout << "Vector before sorting:" << endl;
    for (auto student : students)
        student.print();

    sort(begin(students), end(students)); // Sort all the elements in the vector

    cout << "Vector after sorting:" << endl;
    for (auto student : students)
        student.print();
}