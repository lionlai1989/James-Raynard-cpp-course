/**
 * Stream State Member Functions
 * C++ streams have member functions to check the state of the stream.
 * - clear() - restore the stream to a good state
 * - ignore() - discard characters from the input buffer
 */

#include <iostream> // cin, cout, endl
#include <limits>   // numeric_limits

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic recover.cpp && ./a.out
int main() {
    int x{0};

    cout << "Please enter a number: ";
    cin >> x;

    bool success{false};

    // The following code will result in an infinite loop if the user enters a non-integer value.
    // Explain why.
    while (!success) {
        if (cin.good()) {
            cout << "You entered the number " << x << "\n";
            success = true;
        } else if (cin.fail()) {
            cout << "Please try again and enter a number\n";
            cin.clear();
            cin >> x;
        }
    }

    /**
     * When `cin >> x` fails because the user typed "Apple":
     * 1. The failbit is set.
     * 2. The characters 'A', 'p', 'p', 'l', 'e' are left sitting in the input buffer.
     * 3. Inside your loop, you call cin.clear(). The stream is now "good" again.
     * 4. The code hits cin >> x; again.
     * 5. cin looks at the buffer, sees 'A' still sitting there, realizes it's not a number, and
     *    immediately fails again.
     * 6. The loop repeats forever without ever stopping to ask the user for new input.
     *
     * To fix this, we need to clear the input buffer after clearing the failbit.
     */

    while (!success) {
        if (cin.good()) {
            cout << "You entered the number " << x << "\n";
            success = true;
        } else if (cin.fail()) {
            cout << "Please try again and enter a number\n";

            cin.clear();

            // Remove next 20 characters or everything up to next newline. But how many characters
            // are in the input buffer? We don't know.
            // cin.ignore(20, '\n');

            // Remove all characters from the input buffer or up to the next newline.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cin >> x;
        }
    }
}
