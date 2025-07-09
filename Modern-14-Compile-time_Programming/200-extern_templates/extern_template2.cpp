#include "extern_template.h"

// g++ -std=c++20 extern_template1.cpp extern_template2.cpp extern_template_impls.cpp && ./a.out
int main() {
    std::string str{"Hello"};
    std::cout << "main() printing " << str << ": ";
    print(std::cout, str);
    std::cout << std::endl;
    func(str);
    std::cout << std::endl;
}