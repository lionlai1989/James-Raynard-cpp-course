/**
 * C++ Streams and Output Buffering
 * C++ streams use "buffering" to minimize the number of system calls to the operating system.
 * During write operations, data is temporarily stored in a memory buffer before being written to
 * the file. The size of this buffer is chosen to match the maximum amount of data that can be
 * written in a single system call. When this buffer is full, the stream will remove the data from
 * the buffer and send it to the operating system. This is known as "flushing" the buffer.
 *
 * When are Stream Buffers Flushed?
 * - For ostream, it depends on the terminal configuration.
 *   - Usually this is at the end of every line.
 *   - cout is always flushed before the program reads from cin.
 * - For ofstream, it is only flushed when the buffer is full or when the file is closed.
 * - There is no direct way to flush input streams.
 *
 * std::flush
 * std::flush allows us to control when the stream buffer is flushed. E.g.,
 * ```
 * std::cout << "Hello" << std::flush; // "Hello" will appear immediately on the screen
 * ```
 * All the data in the buffer is immediately sent to its destination. This significantly
 * decreases the performance of the program. So, it should only be used if the data really needs to
 * be up to date. E.g., log file to find out why a program crashed.
 */

#include <fstream>
#include <iostream>

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 035-streams_and_buffering.cpp && ./a.out
int main() {
    ofstream ofile{"log.txt"};

    if (!ofile) {
        cout << "Could not open file\n";
        return -1;
    }

    for (int i = 0; i < 1'000'000; ++i) {
        cout << i << "\n";
        ofile << i << "\n";

        // Uncomment to observe the behaviour
        // cout << i << "\n" << flush;
        // ofile << i << "\n" << flush;

        // Uncomment to observe the behaviour. endl = \n + flush
        // cout << i << endl;
        // ofile << i << endl;

        /**
         * cout is line buffered, so it will flush the buffer after every line. Thus, we can see
         * '66666' is printed immediately on the screen.
         * ofile is block buffered, so it will flush the buffer when the buffer is full. Thus, we
         * probably cannot see '66666' in `log.txt`. It should be less than `66666`.
         */
        if (i == 66666)
            throw std::exception();
    }

    ofile.close();
}
