#include "manual.h"

// Define the template in one and only one source file
template <typename T> std::ostream &print(std::ostream &os, const T &t) { return os << t; }

// Manual instantiation of the template. template keyword is placed at the front of this line so the
// compiler knows that this is a template instantiation.
template std::ostream &print(std::ostream &os, const std::string &str);

// g++ -std=c++20 -Wall -Wextra -pedantic manual2.cpp manual1.cpp && ./a.out
int main() {
    std::string str{"Hello"};
    std::cout << "main() printing " << str << ": ";

    /**
     * When `print(std::cout, str);` is called below, it uses the template instantiation at line 8.
     */
    print(std::cout, str);
    std::cout << std::endl;

    /**
     * When `func(str);` is called below, it uses the non-template function defined in "manual.cpp",
     * which calls `print(std::cout, str);`. And the print function is the template instantiation at
     * line 8.
     *
     * The result is that we only have one copy of the template instantiation in the entire program.
     *
     * The ISSUE is that programmers need to keep track of which templates they need to instantiate
     * and where to instantiate them, which is error-prone.
     *
     * This is not really useful.
     *
     * The solution is to use the extern template declaration.
     */
    func(str);
    std::cout << std::endl;

    return 0;
}
