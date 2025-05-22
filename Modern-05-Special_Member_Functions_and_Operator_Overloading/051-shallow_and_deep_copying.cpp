#include <iostream>
#include <string>

using namespace std;

class ShallowString {
  private:
    char *data;
    int size;

  public:
    ShallowString(const string &s) : size(s.size()) {
        cout << "ShallowString Parameterized constructor" << endl;
        data = new char[size]; // Allocate the heap memory for the data

        for (int i = 0; i < size; ++i) // Populate the data
            data[i] = s[i];
    }

    // Synthesized member functions
    // String(const String& arg) : size(arg.size), data(arg.data) {}
    // String& operator =(const String& arg) { size = arg.size; data = arg.data; return *this; }

    ~ShallowString() {
        cout << "ShallowString Destructor" << endl;

        delete[] data; // Release the heap memory for the data
    }

    int length() { return size; }
};

class DeepString {
    /**
     * This String class stores the data in a heap-allocated array and uses the RAII (Resource Acquisition Is
     * Initialization) idiom.
     *
     * 1. The constructor allocates the heap memory for the data.
     * 2. The destructor releases the heap memory for the data.
     *
     * In the String class, the resource is the heap-allocated "data" array.
     *
     * Rule of Three:
     * If a class needs to implement one of:
     * - copy constructor
     * - assignment operator
     * - destructor
     * then it needs to implement all three.
     */

  private:
    char *data;
    int size;

  public:
    /**
     * If parameterized constructor is implemented, then the compiler won't generate the default constructor.
     * So, we need to implement the default constructor.
     */
    DeepString() : data(nullptr), size(0) {}

    DeepString(const string &s) : size(s.size()) {
        cout << "DeepString Parameterized constructor\n";
        data = new char[size]; // Allocate the heap memory for the data

        for (int i = 0; i < size; ++i) // Populate the data
            data[i] = s[i];
    }

    DeepString(const DeepString &other) : size(other.size) {
        cout << "DeepString Copy constructor\n";
        data = new char[size]; // Allocate the heap memory for arg's data

        for (int i = 0; i < size; ++i) // Populate the memory with arg's data
            data[i] = other.data[i];
    }

    DeepString &operator=(const DeepString &other) {
        cout << "DeepString Assignment operator\n";

        /**
         * If this and other are the same object, they use the same memory pointer.
         * So, if this and other are the same object, we don't do anything.
         */
        if (&other != this) { // Check for self-assignment
            cout << "Reallocating memory\n";
            delete[] data;               // IMPORTANT: Release the original memory
            data = new char[other.size]; // Allocate the data member

            size = other.size; // Assign to the size member

            for (int i = 0; i < size; ++i) // Populate the data
                data[i] = other.data[i];
        }

        return *this; // Return the assigned-to object
    }

    ~DeepString() {
        cout << "DeepString Destructor" << endl;
        delete[] data; // Release the heap memory for the data
    }

    int length() { return size; }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 051-shallow_and_deep_copying.cpp && ./a.out
int main() {
    ShallowString sstr("Hello"s);

    // The following code will cause segmentation fault because the data member is not properly handled by the
    // compiler-generated synthesized member functions. The data member is deleted thrice.
    // ShallowString sstr2(sstr);
    // cout << "sstr2 size: " << sstr2.length() << endl;
    // ShallowString sstr3("World"s);
    // sstr3 = sstr2;
    // cout << "sstr3 size: " << sstr3.length() << endl;

    DeepString dstr("deep string"s);
    DeepString dstr2(dstr);
    cout << "dstr2 size: " << dstr2.length() << endl;

    DeepString dstr3("another deep string"s);
    DeepString dstr4;
    dstr4 = dstr3;
    dstr3 = dstr2;

    cout << "dstr3 size: " << dstr3.length() << endl;
    cout << "dstr4 size: " << dstr4.length() << endl;
}
