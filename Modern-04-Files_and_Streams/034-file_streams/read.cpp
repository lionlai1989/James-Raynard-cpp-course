/**
 * Files and Streams
 * In C++, a file is represented by a sequence of bytes, identified by a filename.
 * C++ provides file streams to read from and write to files. It's similar to how we use iostreams
 * for console input and output.
 * fstream objects always access files "sequentially", meaning data is read or written in order from
 * the beginning to the end of the file. fstream objects does not know the structure of the data in
 * the file.
 *
 * C++ fstream Operations:
 * - Open: Binds a file stream object to a file.
 * - Read: Data is read from the file into program's memory.
 * - Write: Data is written from program's memory to the file.
 * - Close: Releases the binding between the file stream object and the file.
 * For each operation, the fstream object in a program will call a funtion in the operating system
 * API. The program will be blocked until the operating system completes the requested operation.
 * When a C++ program terminates, all file streams are automatically closed. However, it's a good
 * practice to explicitly close file streams when they are no longer needed.
 *
 * NOTE:
 * An important aspect of reading and writing files in C++ is how data is transferred between the
 * file and the program's memory. This is typically done using buffers. As data being transferred
 * between the program and the file, it may be temporarily stored in a memory buffer. The makes
 * large data transfers more efficient by reducing the number of calls to the operating system. But
 * it's also make the data transfer less timely predictable.
 * One common ISSUE is that if data transfer waits too long in the buffer, then the descrepancy
 * between the actual data in the file and what the program thinks is in the file may become
 * significant.
 */

/**
 * Stream Types:
 * - iostream
 *   - ostream (cout)
 *   - istream (cin)
 * - fstream
 *   - ofstream (file stream for writing)
 *   - ifstream (file stream for reading)
 *
 * When fstream's destructor is called, the file is automatically closed. The will cause any unsaved
 * data to be written to the file. Read the NOTE: above. Thus, it's a good practice to call
 * `close()`.
 */

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// g++ -std=c++20 -Wall -Wextra -pedantic read.cpp && ./a.out
int main() {
    // Reading word by word from a file. What is a "word"?
    ifstream ifile{"text.txt"}; // Define ifile as an ifstream variable bound to text.txt
    if (ifile) {
        string text{""};
        while (ifile >> text) { // Read a word from the file
            cout << text << '\n';
        }

        cout << endl;
        ifile.close(); // Release the binding between ifile and text.txt
    }

    // Reading line by line from a file.
    ifstream ifile2{"text.txt"};
    if (ifile2) {
        string text{""};
        while (getline(ifile2, text)) {
            cout << text << endl;
        }

        cout << endl;
        ifile2.close();
    }
}