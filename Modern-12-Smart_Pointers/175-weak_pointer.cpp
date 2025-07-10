/**
 * Weak Pointer:
 * Weak pointers provide a safe way to alias a shared pointer. This avoids the problems with
 * traditional pointers which can "dangle".
 *
 * A weak_ptr is bound to a shared_ptr object. It does not affect the reference counter of the
 * shared_ptr object.
 *
 * A weak_ptr cannot access the shared memory directly. It has to be converted back to a shared_ptr
 * and this is only allowed if the shared_ptr object is still valid. E.g.,
 *
 * auto ptr{make_shared<int>(36)}; // create shared_ptr object - `pts` reference counter is 1
 * weak_ptr<int> wptr{ptr}; // create weak_ptr alias to ptr - `ptr` reference counter is still 1
 * ptr = nullptr; // release ptr's memory - `ptr` reference counter is 0
 *
 */

#include <iostream> // cout, endl
#include <memory>   // shared_ptr, make_shared, weak_ptr
#include <vector>   // vector

using namespace std;

void print(vector<shared_ptr<int>> vec) {
    cout << "Vector elements: ";

    for (shared_ptr<int> p : vec) {
        cout << *p << ", ";
    }

    cout << endl;
}

void safe_print(vector<shared_ptr<int>> vec) {
    cout << "Vector elements: ";

    // Notice that we are using weak_ptr<int> instead of shared_ptr<int>
    for (weak_ptr<int> p : vec) {
        auto ptr = p.lock(); // Convert weak_ptr to shared_ptr

        // Check if the shared_ptr is still valid
        if (ptr)
            cout << *ptr << ", ";
        else
            cout << "Deleted element, ";
    }

    cout << endl;
}

// g++ -std=c++20 -Wall -Wextra -pedantic 175-weak_pointer.cpp && ./a.out
int main() {
    int *ptr = new int(36); // Create pointer
    cout << "ptr's data is " << *ptr << endl;

    int *ptr2 = ptr; // Create pointer which is an alias to ptr

    delete ptr; // Release ptr's memory

    // How do we know if ptr2 is still valid? We can't.
    cout << "ptr2's data is " << *ptr2 << endl; // This is undefined behavior.

    cout << "--------------------------------" << endl;

    shared_ptr<int> sptr{make_shared<int>(36)}; // reference count is 1
    cout << "shared_ptr's data is " << *sptr << endl;

    // Create weak_ptr alias to sptr
    weak_ptr<int> wptr = sptr; // reference count is still 1

    // Release sptr's shared memory
    sptr = nullptr; // sptr's reference count is 0

    // wptr is an alias to sptr - is it still valid?

    // lock() returns shared_ptr if the weak_ptr is still valid, otherwise it returns nullptr.
    // lock() is atomic operation to prevent race conditions. I.e., lock() is thread-safe.
    shared_ptr<int> sptr2 = wptr.lock();
    if (sptr2) {
        cout << "shared_ptr's data is " << *sptr2 << endl;
    } else {
        cout << "shared_ptr not valid" << endl;
    }

    // Alternatively, we can copy-construct a shared_ptr from a weak_ptr. This will throw an
    // exception if the weak_ptr is not valid.
    try {
        shared_ptr<int> sptr2{wptr};
        cout << "shared_ptr's data is " << *sptr2 << endl;
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    cout << "--------------------------------" << endl;

    vector<shared_ptr<int>> vec{
        make_shared<int>(36),
        make_shared<int>(42),
        make_shared<int>(46),
        make_shared<int>(50),
    };
    print(vec);

    cout << "Deleting vec[2]\n";
    vec[2] = nullptr; // "46" is deleted. vec[2] is now a dangling pointer.

    // print(vec); // Segmentation fault (core dumped)

    cout << "--------------------------------" << endl;

    vector<shared_ptr<int>> vec2{
        make_shared<int>(36),
        make_shared<int>(42),
        make_shared<int>(46),
        make_shared<int>(50),
    };

    safe_print(vec2);

    cout << "Deleting vec[2]\n";
    vec2[2] = nullptr;

    safe_print(vec2);

    return 0;
}
