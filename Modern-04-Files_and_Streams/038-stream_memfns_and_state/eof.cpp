/**
 * Stream State Member Functions
 * C++ streams have member functions to check the state of the stream.
 * eof() - it doesn't look ahead to see if the end of the file is coming; it only returns true after
 * a read operation has already attempted to go past the end of the file and failed.
 */

#include <fstream>  // ifstream
#include <iostream> // cout

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic eof.cpp && ./a.out
int main() {
    ifstream ifile;
    ifile.open("input.txt");

    int x{0};

    // Wrong. Explain the output
    while (!ifile.eof()) {
        ifile >> x;
        cout << x << ", ";
    }

    // Correct
    while (ifile >> x) { // return the stream itself, which can be evaluated as a boolean
        cout << x << ", ";
    }
    cout << endl;
}
