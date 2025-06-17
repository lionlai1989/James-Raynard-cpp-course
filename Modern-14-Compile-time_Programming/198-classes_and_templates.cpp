#include <iostream>

using namespace std;

// C++14 generic lambda. The compiler deduces the type of the signature of the lambda function.
auto lambda = [](auto x, auto y) { return x + y; };

// Equivalent functor class of "lambda" function with member template.
// A functor is a class that overloads the function call operator () so that it can be called like
// a function. The benefit of using a functor is that it can have internal state.
class functor {
  public:
    template <typename T> T operator()(T x, T y) { return x + y; }
};

// Templated class with parameter T
template <typename T> class comparer {
    T t1, t2;

  public:
    comparer(const T &t1, const T &t2) : t1(t1), t2(t2) {}

    // Member template with parameter Func
    template <typename Func> bool compare(Func f) { return f(t1, t2); }
};

// g++ -std=c++20 -Wall -Wextra -pedantic 198-classes_and_templates.cpp && ./a.out
int main() {
    // Create functor object, instantiate its function call operator and call it. The compiler
    // deduces the type of the signature of the function call operator.
    cout << "functor()(2, 5): ";
    cout << functor()(2, 5) << endl;
    cout << "lambda()(2, 5): ";
    cout << lambda(2, 5) << endl;

    cout << "--------------------------------" << endl;

    int x{1}, y{2};

    // Instantiate a comparer object where T is an int
    comparer<int> c(x, y);
    cout << "comparer class: t1 = " << x << ", t2 = " << y << endl;

    // Instantiate comparer::compare() where Func is a lambda expression. The compiler deduces the
    // type of the "Func" parameter.
    auto b = c.compare([](int i1, int i2) { return i1 < i2; });
    cout << "Result of calling compare: " << boolalpha << b << endl;
}
