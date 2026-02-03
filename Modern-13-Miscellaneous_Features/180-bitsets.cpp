#include <bitset>   // bitset
#include <iostream> // cout, endl

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 180-bitsets.cpp && ./a.out
int main() {
    bitset<8> b1{"10101110"};  // Initialize from string literal - bitset with value 174
    bitset<8> b2{0xae};        // Initialize from integer (decimal or hexadecimal)
    bitset<8> b3{0b1010'1110}; // Initialize from binary constant (C++14)

    cout << "b1 is " << b1 << endl;                         // Displays 10101110
    cout << "b2 in decimal is " << b2.to_ulong() << endl;   // Displays 174
    cout << "b2 as a string is " << b2.to_string() << endl; // Displays 10101110
    cout << "b3 is " << b3 << endl;                         // Displays 10101010

    cout << "b1 has " << b1.size() << " bits\n"; // Displays 8

    // Display all the bits in b1. Note that the bits are displayed from right to left.
    // I.e., b1[0] is the least significant bit.
    cout << "The bits of b1 are: ";
    for (size_t i = 0; i < b1.size(); ++i)
        cout << b1[i] << ",";
    cout << endl;

    // Bit access with bounds checking
    cout << "Trying access to bit 8 of b1 with bounds checking\n";
    try {
        cout << "b1 bit " << 8 << " = " << b1.test(8) << endl;
    } catch (exception &e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "--------------------------------" << endl;

    bitset<8> b4{"10101110"}; // Bitset with value 174
    bitset<8> b5{0b010'1110}; // Bitset with value 42

    cout << "b4 is  " << b4 << endl;  // Displays 10101110
    cout << "~b4 is " << ~b4 << endl; // Displays 01010001
    cout << "b5 is  " << b5 << endl;  // Displays 00101110

    cout << "b4 & b5 is " << (b4 & b5) << endl; // Displays 00101110
    cout << "b4 | b5 is " << (b4 | b5) << endl; // Displays 10101110
    cout << "b4 ^ b5 is " << (b4 ^ b5) << endl; // Displays 10000000

    cout << "b4 << 4 is " << (b4 << 4) << endl; // Displays 11100000
    cout << "b5 >> 2 is " << (b5 >> 2) << endl; // Displays 00001011

    cout << "--------------------------------" << endl;

    bitset<8> b6{"10101110"}; // Bitset with value 174
    cout << "b6 = " << b6 << endl;

    cout << "Calling b6.flip()" << endl;
    b6.flip(); // Invert all bits
    cout << "b6 = " << b6 << endl;

    cout << "Calling b6.set(2)" << endl;
    b6.set(2); // Set bit 2 to true
    cout << "b6 = " << b6 << endl;

    cout << "Calling b6.reset(0)" << endl;
    b6.reset(0); // Reset bit 0 to false
    cout << "b6 = " << b6 << endl;

    cout << "--------------------------------" << endl;

    bitset<8> b7{"10101110"}; // Bitset with value 174

    cout << boolalpha << "Are all bits set?" << endl;
    cout << "b7: " << b7.all() << endl;

    cout << boolalpha << "Are any bits set?" << endl;
    cout << "b7: " << b7.any() << endl;

    cout << boolalpha << "Are no bits set?" << endl;
    cout << "b7: " << b7.none() << endl;

    cout << "Number of bits set" << endl;
    cout << "b7: " << b7.count() << endl;
}
