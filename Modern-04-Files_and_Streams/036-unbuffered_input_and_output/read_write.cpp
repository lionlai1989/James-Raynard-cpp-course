/**
 * Input and Output of Blocks of Character
 * For reading and writing blocks of characters, we use the read() and write() member functions. As
 * we are not using a buffer managed by the stream, we need to provide a buffer ourselves.
 *
 * Often, we need to know how much data an input stream has sent us. For this, we use the gcount()
 * member function. The gcount() member function returns the number of characters that were actually
 * read.
 */

#include <fstream>  // ifstream
#include <iostream> // cout, endl
#include <string>   // string

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic read_write.cpp && ./a.out
int main() {
    const int filesize{10}; // The size of the memory buffer
    char filebuf[filesize]; // The memory buffer
    string filename{"input.txt"};

    ifstream ifile(filename);

    if (!ifile) {
        cout << "Could not open " << filename << endl;
        return -1;
    }

    ifile.read(filebuf, filesize); // Fetch data from the file into the memory buffer
    auto nread = ifile.gcount();   // How many bytes did we receive?
    ifile.close();

    cout << "Read " << nread << " bytes from " << filename << endl;
    cout << "File data: ";
    cout.write(filebuf, nread); // Send the data from the memory buffer to output
    cout << endl;
}
