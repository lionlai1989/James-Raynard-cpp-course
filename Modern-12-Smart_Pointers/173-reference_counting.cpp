#include <iostream>

using namespace std;

class String {
  private:
    int size;
    char *data; // The shared memory, allocated on the heap

    /**
     * The reference counter, allocated on the heap. It must be visible to all the objects which
     * bind to the shared memory.
     */
    int *counter;

  public:
    String(int size) : size(size) {
        counter = new int{0}; // Allocate the counter - no bound objects initially
        data = new char[size];

        ++*counter; // "this" has been bound - increment the counter
    }

    ~String() noexcept {
        if (counter) {
            cout << "Destructor: data = " << static_cast<void *>(data)
                 << ", counter = " << static_cast<void *>(counter) << ", count = " << *counter
                 << endl;

            --*counter;
            if (*counter == 0) {
                cout << "Deleting shared memory at " << static_cast<void *>(data) << endl;
                delete counter;
                delete[] data;
            }
        } else {
            cout << "Destructor: moved-from object, nothing to delete.\n";
        }
    }

    // Declare overloaded swap() as a friend of this class
    friend void swap(String &l, String &r) noexcept;

    String(const String &arg) {
        cout << "Copy constructor" << endl;

        // Make a shallow copy of the argument
        size = arg.size;
        data = arg.data;
        counter = arg.counter;

        // Any other code needed to configure the new object
        ++*counter; // "this" has been bound - increment the counter
    }

    String &operator=(const String &arg) {
        cout << "Copy assignment operator" << endl;

        cout << "Assigned-to object: data = " << (void *)data << ", counter = " << counter
             << ", count = " << *counter << endl;

        // Option 1:
        if (data != arg.data) {  // If arg is bound to different shared memory
            --*counter;          // Unbind from our current shared memory
            if (*counter == 0) { // If we are the last bound object, release the memory
                cout << "Deleting shared memory at " << static_cast<void *>(data) << endl;
                cout << "Deleting counter at " << static_cast<void *>(counter) << endl;
                delete counter;
                delete[] data;
            }

            // Make a shallow copy of the argument
            size = arg.size;
            data = arg.data;
            counter = arg.counter;

            ++*counter; // "this" has been bound - increment the counter
        }

        // Option 2: copy and swap
        // String temp(arg);
        // swap(*this, temp);

        return *this; // Return the assigned-to object
    }

    String(String &&arg) noexcept {
        cout << "Move constructor" << endl;

        data = arg.data;
        size = arg.size;
        counter = arg.counter; // Shallow copy of counter pointer

        // Prevent double deletion
        arg.data = nullptr;
        arg.counter = nullptr;
    }

    String &operator=(String &&arg) noexcept {
        cout << "Move assignment operator" << endl;

        String temp(std::move(arg)); // Call move constructor
        swap(*this, temp);           // Exchange our data with temp's data

        return *this;
    }

    int length() { return size; }
    int count() { return *counter; }

    friend void swap(String &l, String &r) noexcept;

    void print() {
        cout << "size = " << size;
        cout << ", data address " << static_cast<void *>(data);
        cout << ", counter " << static_cast<void *>(counter);
        if (counter)
            cout << ", count = " << *counter;
        cout << endl;
    }
};

inline void swap(String &l, String &r) noexcept {
    using std::swap;
    swap(l.size, r.size);
    swap(l.data, r.data);
    swap(l.counter, r.counter);
}

// g++ -std=c++20 -Wall -Wextra -pedantic 173-reference_counting.cpp && ./a.out
int main() {
    String a{5};
    cout << "a: ";
    a.print();

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
    cout << "Assigning a from c\n";
    a = c;

    cout << "a: ";
    a.print();
    cout << "c: ";
    c.print();
    cout << endl;

    String a2{5};
    cout << "a2: ";
    a2.print();

    String b2{6};
    cout << "b2: ";
    b2.print();
    cout << endl;
    cout << "Move construction of c2 from b2\n";
    String c2{std::move(b2)};

    cout << "b2: ";
    b2.print();
    cout << "c2: ";
    c2.print();
    cout << endl;
    cout << "Move assigning a2 from c2\n";
    a2 = std::move(c2);

    cout << "a2: ";
    a2.print();
    cout << "c2: ";
    c2.print();
    cout << endl;

    cout << "Exiting program...\n";
}
