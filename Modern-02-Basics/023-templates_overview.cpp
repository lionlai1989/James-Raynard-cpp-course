/**
 * We often need to write a function that can work with different types of data. C++ templates allow
 * us to write a function once that can work with different types of data.
 *
 * When we use the template for the data of a particular type, the compiler will generate the code
 * needed for that type. E.g. vector<int> will cause the compiler to define a class that is a vector
 * of ints. This is called an instantiation of the template.
 *
 * For this to be possible, the compiler needs to see the full definition of the vector template
 * class in the translation unit.
 *
 * With a regular function, the compiler only needs to see its declaration when it is called.
 * For a template function, the compiler must be able to see the full definition when it is called.
 * That is, the compiler has to generate the instantiated code for that code.
 *
 * Most programmers write the template definition in the header file, so it is included
 * automatically.
 *
 * Some programmers put all their templates in a separate ".inc" file and include it separately.
 *
 */

#include <iostream> // cout, endl
#include <vector>   // vector

using namespace std;

// Function template for finding maximum of two values.
// template <class T> also works.
template <typename T>             // The template parameter T is the parameter type
T Max(const T &t1, const T &t2) { // The arguments and return value have this type
    cout << "Max<" << typeid(T).name() << ">" << endl;
    if (t1 > t2)
        return t1;
    return t2;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 023-templates_overview.cpp && ./a.out
int main() {
    // When we call Max, the compiler will instantiate the function from the template code, with T
    // replaced by the type of the arguments. The compiler deduces the type of T  to be double.
    cout << Max(7.0, 2.6) << endl; // Expands template to:
    /**
     * double Max(const double& t1, const double& t2) {
     *     if (t1 > t2)
     *         return t1;
     *     return t2;
     * }
     */

    cout << Max<float>(7.0, 2.6) << endl; // Force the template to be instantiated with float
    cout << Max(7.0f, 2.6f) << endl;      // Force the template to be instantiated with float

    cout << "--------------------------------" << endl;

    // When we create an object of a template class, the compiler can deduce the parameter type.
    // This is known as CTAD (Class Template Argument Deduction).
    vector<int> vec{1, 2, 3}; // C++11 - declared as vector<int>
    vector vec2{1, 2, 3};     // C++17 - deduced as vector<int>

    cout << "vec = ";
    for (auto it : vec)
        cout << it << ", ";

    cout << endl;

    cout << "vec2 = ";
    for (auto it : vec2)
        cout << it << ", ";

    cout << endl;
}
