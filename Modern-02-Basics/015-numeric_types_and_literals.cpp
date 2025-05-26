#include <cstdint>  // int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t
#include <iostream> // cout

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 015-numeric_types_and_literals.cpp && ./a.out
int main() {
    cout << "char: " << sizeof(char) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "long: " << sizeof(long) << endl;
    cout << "long long: " << sizeof(long long) << endl;
    cout << endl;

    cout << "int8_t: " << sizeof(int8_t) << endl;
    cout << "int16_t: " << sizeof(int16_t) << endl;
    cout << "int32_t: " << sizeof(int32_t) << endl;
    cout << "int64_t: " << sizeof(int64_t) << endl;
    cout << endl;

    cout << "uint8_t: " << sizeof(uint8_t) << endl;
    cout << "uint16_t: " << sizeof(uint16_t) << endl;
    cout << "uint32_t: " << sizeof(uint32_t) << endl;
    cout << "uint64_t: " << sizeof(uint64_t) << endl;
    cout << endl;

    // Numeric literals are decimal by default
    int decimal = 42; // 4*10 + 2*1 = 42
    cout << "Decimal: " << decimal << endl;

    // Hexadecimal numbers have 0x or 0X in front
    int hexadecimal = 0x2a; // 2*16 + 10*1 = 42
    cout << "Hexadecimal: " << hexadecimal << endl;

    // Octal numbers have 0 in front
    int octal = 052; // 5*8 + 2*1 = 42
    cout << "Octal: " << octal << endl;

    // Binary numbers have 0b or 0B in front (C++14 onwards)
    int binary = 0b101010; // 1*32 + 1*8 + 1*2 = 42
    cout << "Binary: " << binary << endl;

    cout << endl;

    const int one_million = 1'000'000;
    const int one_lakh = 1'00'000;
    double pi = 3.141'596;

    cout << "One million: " << one_million << endl;
    cout << "One lakh: " << one_lakh << endl;
    cout << "pi: " << pi << " " << sizeof(pi) << endl;

    cout << endl;

    // floating-point literals are double by default
    cout << 3.141596 << " " << sizeof(3.141596) << endl;
    cout << 3.141596f << " " << sizeof(3.141596f) << endl; // Suffix f for float
}
