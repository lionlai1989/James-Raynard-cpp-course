#include <iostream>

// It brings everything from the std namespace into the global namespace.
// This is not recommended because it can cause name conflicts.
// Using "using namespace std;" defeats the purpose of namespaces.
using namespace std;

int x{23}; // x defined in the global namespace

namespace abc {

int x{47}; // x defined in the namespace abc - hides global x

void func() {
    cout << "x = " << x << endl;     // Will use abc's x -> 47
    cout << "::x = " << ::x << endl; // Will use global x -> 23
}

} // namespace abc

// g++ -std=c++20 -Wall -Wextra -pedantic 024-namespaces.cpp && ./a.out
int main() {

    // func(); identifier "func" is undefined

    abc::func();

    cout << "x = " << x << endl; // Will use global x -> 23

    cout << "abc::x = " << abc::x << endl; // Will use abc's x -> 47

    cout << "::x = " << ::x << endl; // Will use global x -> 23

    return 0;
}
