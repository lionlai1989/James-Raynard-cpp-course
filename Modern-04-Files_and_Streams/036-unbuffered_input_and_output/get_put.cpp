/**
 * Unbuffered input and output
 * There are some applications where stream buffering is not desired. E.g., a network application
 * where data must be transmitted in "packets" of a specified size.
 *
 * Input and Output of a Single Character
 * - get() fetches the next character from an input stream.
 * - put() sends its argument to an output stream.
 *
 * Notes on cin.get(c):
 * 1. It reads every character, including whitespace. Pressing 'Enter' adds a newline ('\n')
 *    to the buffer and flushes it, making the input available for cin.get() to read.
 * 2. It returns false (breaking the loop) only when it encounters End-of-File (EOF) or a read
 *    error. Linux/macOS: Press Ctrl+D to send EOF.
 */

#include <iostream>

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic get_put.cpp && ./a.out
int main() {
    cout << "Enter some text: " << endl;

    char c;
    while (cin.get(c)) { // Read a character until we get end-of-input (CTRL+D on Linux)
        cout.put(c);     // Display the character
        cout << "-";
    }
    cout << "Goodbye!" << endl;
}
