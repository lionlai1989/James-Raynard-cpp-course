#include <fstream>  // ofstream, fstream
#include <iostream> // cout

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic append.cpp && ./a.out
int main() {
    ofstream ofile;
    ofile.open("important.txt", fstream::out | fstream::app); // Open for writing, append mode

    if (!ofile) {
        cout << "Could not open file\n";
        return -1;
    }

    ofile << "some more data";
    ofile.close();
}
