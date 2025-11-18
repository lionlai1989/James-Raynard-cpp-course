#include <algorithm>
#include <iostream>
#include <string>

// g++ -std=c++20 -Wall -Wextra -pedantic -pthread 070-standard_algorithms.cpp && ./a.out
int main() {
    std::string str("HellO world");
    std::cout << "String to search: " << str << '\n';

    // Search string for first occurrence of 'o'
    std::cout << "Searching for first occurrence of \'o\'\n";
    /**
     * std::find() takes three arguments:
     * first: An input iterator pointing to the beginning of the range to search.
     * last: An input iterator pointing to the end of the range (one past the last element).
     * val: The value to search for.
     *
     * Return Value:
     * std::find returns an iterator pointing to the first element in the range [first, last) that
     * compares equal to val. If no such element is found, it returns the last iterator, indicating
     * that the value was not present in the range.
     */
    auto res = std::find(str.cbegin(), str.cend(), 'o');

    if (res != str.cend()) { // found
        std::cout << "Found a matching element at index: " << res - str.cbegin() << '\n';

        std::cout << "At this point in the string: ";
        for (auto it = res; it != str.cend(); ++it)
            std::cout << *it;
        std::cout << '\n';
    } else { // not found
        std::cout << "No matching element\n";
    }

    /**
     * The main issue with std::find() is that it does not support "predicate".
     * A "predicate" is a function which returns bool. std::find() uses the "==" operator to
     * compares each element to the target value. The == operator for char is case-sensitive.
     * Namely, 'o' is not regarded as equal to 'O'.
     *
     * std::find_if() supports using our own predicate.
     */
    // Use a predicate function which ignores case
    auto res2 =
        std::find_if(str.cbegin(), str.cend(), [](const char c) { return ::toupper(c) == 'O'; });

    if (res2 != str.cend()) { // found
        std::cout << "Found a matching element at index: " << res2 - str.cbegin() << '\n';

        std::cout << "At this point in the string: ";
        for (auto it = res2; it != str.cend(); ++it)
            std::cout << *it;
        std::cout << '\n';
    } else { // not found
        std::cout << "No matching element\n";
    }
}
