#include <iostream> // cout, endl
#include <string>   // string

// g++ -std=c++20 -Wall -Wextra -pedantic 021-iterator_arithmetic_and_ranges.cpp && ./a.out
int main() {
    std::string str{"12345"};

    std::cout << "str: " << str << '\n';
    std::cout << "Number of elements: " << str.end() - str.begin() << '\n';

    auto second = std::begin(str) + 1; // Iterator to second element
    std::cout << "Second element is " << *second << '\n';

    auto last = std::end(str) - 1; // Iterator to last element
    std::cout << "Last element is " << *last << '\n';

    // end() - begin() gives the number of elements
    auto mid =
        std::begin(str) + (std::end(str) - std::begin(str)) / 2; // Iterator to middle element
    std::cout << "Middle element is " << *mid << '\n';

    std::cout << "--------------------------------" << '\n';

    std::string str2{"12345"};

    std::cout << "str: " << str2 << '\n';
    // std::distance returns the number of steps needed to go from its first argument to its second.
    std::cout << "Number of elements: " << std::distance(std::begin(str2), std::end(str2)) << '\n';

    auto second2 = std::next(std::begin(str2)); // Returns iterator to second element
    if (second2 != std::end(str2))
        std::cout << "Second element is " << *second2 << '\n';

    auto last2 = std::prev(std::end(str2)); // Returns iterator to last element
    if (last2 != std::end(str2))
        std::cout << "Last element is " << *last2 << '\n';

    // end() - begin() gives the number of elements
    auto mid2 = std::begin(str2);
    // std::advance moves an iterator by a specified number.
    std::advance(mid2, std::distance(std::begin(str2), std::end(str2)) / 2);

    if (mid2 != std::end(str2)) {
        std::cout << "Middle element is " << *mid2;
        std::cout << " with index " << std::distance(str2.begin(), mid2) << '\n';
    }
}
