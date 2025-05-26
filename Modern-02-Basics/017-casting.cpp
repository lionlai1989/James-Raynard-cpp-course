#include <iostream> // cout

using namespace std;

class Base {
  public:
    virtual ~Base() = default;
};

class Derived : public Base {
  public:
    ~Derived() override = default;
};

void print(char *str) { // Badly designed legacy function. Doesn't mutate str, but not declared const
    cout << str << endl;
}

// g++ -std=c++17 -Wall -Wextra -pedantic 017-casting.cpp && ./a.out
int main() {

    int c = 'A';
    cout << c << endl;
    cout << (char)c << endl;

    int b = 'A';
    cout << b << endl;
    cout << static_cast<char>(b) << endl;

    cout << "--------------------------------" << endl;

    /**
     * const_cast is used to convert a const expression to the non-const equivalent.
     */
    const char *msg = "Hello, world!";
    // print(msg);               // Error - invalid conversion
    print(const_cast<char *>(msg)); // Cast msg to non-const

    cout << "--------------------------------" << endl;

    // reinterpret_cast is used to convert data to untyped binary data.
    int x = 512; // 0x200. 4 bytes.
    int *ptr = &x;
    // Convert int pointer to char pointer to view individual bytes
    char *char_ptr = reinterpret_cast<char *>(ptr);
    cout << "char_ptr[0]: " << (int)*char_ptr << endl;
    cout << "char_ptr[1]: " << (int)*(char_ptr + 1) << endl;
    cout << "char_ptr[2]: " << (int)*(char_ptr + 2) << endl;
    cout << "char_ptr[3]: " << (int)*(char_ptr + 3) << endl;

    cout << "--------------------------------" << endl;

    // dynamic_cast is used to convert a pointer or reference to a Base class to a pointer or reference to a Derived
    // class. dynamic_cast is done at runtime.
    // NOTE: it does not work if "Base *base_ptr = new Base()" is used.
    Base *base_ptr = new Derived();
    Derived *derived_ptr = dynamic_cast<Derived *>(base_ptr);
    if (derived_ptr) {
        cout << "Derived pointer: " << derived_ptr << endl;
    }

    delete base_ptr;
}
