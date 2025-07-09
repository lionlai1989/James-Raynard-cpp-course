#include "extern_int.h"
#include <iostream>

using namespace std;

// g++ -std=c++20 -Wall extern_int1.cc extern_int2.cc extern_int_impls.cc && ./a.out
int main() {
    func();
    cout << "The meaning of life is: " << meaning_of_life << endl;
}
