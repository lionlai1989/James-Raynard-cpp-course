#include <iostream> // cout

using namespace std;

class String {
  private:
    int size;
    char *data;

  public:
    String(int size) : size(size), data(new char[size]) {}

    String(const String &arg) : size(arg.size) {
        cout << "Copy constructor called" << endl;

        data = new char[size]; // Allocate the heap memory for arg's data

        for (int i = 0; i < size; ++i) // Populate the memory with arg's data
            data[i] = arg.data[i];
    }

    String &operator=(const String &arg) {
        cout << "Copy assignment operator called" << endl;

        if (&arg != this) { // Check for self-assignment
            cout << "Reallocating memory" << endl;
            delete[] data;             // Release the original memory
            data = new char[arg.size]; // Allocate the data member

            size = arg.size; // Assign to the size member

            for (int i = 0; i < size; ++i) // Populate the data
                data[i] = arg.data[i];
        }

        return *this; // Return the assigned-to object
    }

    String(String &&arg) noexcept {
        cout << "Move constructor called" << endl;

        size = arg.size;
        arg.size = 0;

        /**
         * This only copys the pointer to the data, not the data itself. This is also know as
         * shallow copy. We end up with two objects pointing to the same data. This is a problem
         * because when the destructor is called, the data will be deleted twice.
         */
        data = arg.data;

        /**
         * arg.data is now a nullptr. And deleting nullptr has no effect.
         */
        arg.data = nullptr;
    }

    String &operator=(String &&arg) noexcept {
        cout << "Move assignment operator called" << endl;

        if (this != &arg) {
            delete[] data;
            data = arg.data;
            size = arg.size;

            arg.data = nullptr;
            arg.size = 0;
        }
        return *this;

        /**
         * move-and-swap idiom
         * Another option is to use a temporary object to swap the data as follows:
         *
         * // Call move constructor. After arg is moved, it points to nullptr.
         * String temp(std::move(arg));
         *
         * // Exchange *this and temp.
         * myswap(*this, temp);
         * return *this;
         */
    }

    ~String() {
        cout << "Calling destructor: " << static_cast<void *>(data) << endl;

        delete[] data; // Release the heap memory for the data
    }

    friend void myswap(String &l, String &r) noexcept;

    void print() {
        cout << "String with size = " << size;
        cout << ", data address " << static_cast<void *>(data) << endl;
    }
};

inline void myswap(String &l, String &r) noexcept {
    using std::swap; // Important!
    swap(l.size, r.size);
    swap(l.data, r.data);
}

// g++ -std=c++20 -Wall -Wextra -pedantic 159-raii_class_with_move_operators.cpp && ./a.out
int main() {
    String a{5};
    cout << "a: ";
    a.print();

    { // Scope for b, c, and d
        String b{6};
        cout << "b: ";
        b.print();
        cout << endl;
        cout << "Copy construction of c from b\n";
        String c{b};
        cout << "b: ";
        b.print();
        cout << "c: ";
        c.print();
        cout << endl;
        cout << "Move construction of d from b\n";
        String d{std::move(b)};
        cout << "b: ";
        b.print();
        cout << "d: ";
        d.print();
        cout << endl;
    }

    cout << "\n--------------------------------\n" << endl;

    {
        String b{6};
        cout << "b: ";
        b.print();
        cout << endl;
        cout << "Copy assignment of b from a\n";
        b = a;
        cout << "b: ";
        b.print();
        cout << "a: ";
        a.print();
        cout << endl;
        cout << "Copy construction of c from b\n";
        String c{b};
        cout << "b: ";
        b.print();
        cout << "c: ";
        c.print();
        cout << endl;
        cout << "Move assignment of c from a\n";
        c = std::move(a);
        cout << "a: ";
        a.print();
        cout << "c: ";
        c.print();
        cout << endl;
    }

    return 0;
}
