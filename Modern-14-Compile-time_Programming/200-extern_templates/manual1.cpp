#include "manual.h"

// Define the non-template function in "manual.h"
void func(const std::string &str) {
    std::cout << "func() printing " << str << ": ";

    // Call the template function
    // The compiler will NOT instantiate it here (it cannot see the definition because the manual.h
    // only has the template declaration)
    print(std::cout, str);
}