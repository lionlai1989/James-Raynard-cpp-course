#include <iostream> // cout
#include <thread>   // thread

using namespace std;

// Class whose member function will be used as the thread's entry point
class Greeter {
  public:
    void hello() { cout << "Hello, Member Function Thread!\n"; }
};

// Function that takes an lvalue reference
void hello2(string &s) { s = "xyz"; }

// Function that takes an rvalue reference
void func(string &&str) { cout << "Ownership of \"" << str << "\" transferred to thread" << '\n'; }

// Callable object - thread entry point
void hello(string str) { cout << str << '\n'; }

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 015_thread_function_with_arguments.cpp && ./a.out
int main() {
    thread thr(hello, "Hello, Thread!");
    thr.join();

    /**
     * The std::thread object owns the arguments. Thus, there are two ways:
     * - lvalue arguments are passed by value
     * - rvalue arguments are passed by move semantic
     */
    string str = "moveable";
    cout << "Starting thread" << '\n';
    // Wrap str in a call to std::move()
    thread thr2(func, std::move(str)); // cast str to an rvalue
    thr2.join();
    // Verify that str has been modified
    cout << "Do I still have any data?" << ' ';
    // Note it's ok to call empty() of a string after a string has been moved from.
    cout << (str.empty() ? "No" : "Yes") << ".\n";

    /**
     * Now, let's pass a reference to the entry point function. Wait! As mentioned before, we can
     * only either pass an lvalue by value or an rvalue by move. How do we pass an lvalue by
     * reference? The answer is to use std::ref().
     * std::ref(obj) returns an object which is a reference to the "obj". So, we will have a value
     * object which is actually a reference to the "obj".
     */
    string str2 = "abc";
    // Wrap argument in a call to std::ref(). thr3 will see the return value of std::ref(str2) as a
    // value object.
    thread thr3(hello2, std::ref(str2));
    thr3.join();
    // Verify that it has been modified
    cout << "str is now " << str2 << '\n';

    // Create an object of the class
    Greeter greet;
    // Create an std::thread object
    // Pass a pointer to the member function
    // and a pointer to the object to call it on
    thread thr4(&Greeter::hello, &greet);

    thr4.join();

    int i = 3;
    // Use a lambda expression as the thread's entry point
    // Capture i by reference
    thread thr5([&i]() { i *= 2; });
    thr5.join();
    cout << "Value of i is now " << i << '\n';

    thread thr6(
        // The first argument is the lambda expression
        [&i](int i1, int i2) {
            cout << "Multiply the sum of " << i1 << " and " << i2 << " by " << i << " is "
                 << (i1 + i2) * i << '\n';
        },
        // The remaining arguments are passed to the lambda expression
        2, 3);

    thr6.join();
}
