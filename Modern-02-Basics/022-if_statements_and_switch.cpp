#include <iostream>
#include <vector>

using namespace std;

// g++ -std=c++20 -Wall -Wextra -pedantic 022-if_statements_and_switch.cpp && ./a.out
int main() {
    vector<int> vec = {1, 2, 3};

    // Older C++. The scope of iter is in the whole main function.
    auto iter = begin(vec);
    if (iter != end(vec)) {
        // Safe to use the iterator here
        cout << "First element of vec (*iter) is: " << *iter << endl;
    }

    vector<int> vec2 = {};

    // C++17. The scope of iter is only in the if-else statement.
    if (auto iter = begin(vec2); iter != end(vec2)) {
        // Safe to use the iterator here
        cout << "First element of vec2 is: " << *iter << endl;
    } else {
        cout << "vec2 is empty (iter is at end position). iter == end(vec2): "
             << (iter == end(vec2)) << endl;
    }

    // iter is still pointing to the first element of vec
    cout << "First element of vec (*iter) is : " << *iter << endl;

    cout << "--------------------------------" << endl;

    int ws_count{0};

    const char *arr = "How much whitespace in\t here?\n";
    cout << "The text to process is \"" << arr << "\"" << endl;

    for (int i = 0; arr[i]; ++i) {
        switch (const char c = arr[i]; c) {
            // This is BAD practice. Just use break in each case.

        case ' ':            // c is space character
            [[fallthrough]]; // Fallthrough to the next case - Not a mistake
        case '\t':           // c is tab character
            [[fallthrough]]; // Fallthrough to the next case - Not a mistake
        case '\n':           // c is newline character
            ++ws_count;      // Increment whitespace counter
            break;
        default: // c is not a whitespace character
            break;
        }
    }

    cout << "The text contains " << ws_count << " whitespace characters\n";

    return 0;
}
