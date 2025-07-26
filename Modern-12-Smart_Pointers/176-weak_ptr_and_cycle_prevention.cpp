#include <iostream>
#include <memory>

using namespace std;

// Declare Son before Father to avoid circular dependency
struct Son;

struct Father {
    ~Father() { cout << "Father destructor" << endl; }

    void setSon(const shared_ptr<Son> &s) {
        // son ref count + 1
        mySon = s;
    }

    shared_ptr<const Son> mySon;
};

struct Son {

    Son(const shared_ptr<Father> &m) {
        // father ref count + 1
        myFather = m;
    }

    ~Son() { cout << "Son destructor" << endl; }

    shared_ptr<const Father> myFather;
};

////////////////////////////////////////////////////////////

struct Son2;

struct Father2 {
    ~Father2() { cout << "Father2 destructor" << endl; }

    void setSon(const shared_ptr<Son2> &s) { mySon = s; }

    shared_ptr<const Son2> mySon;
};

struct Son2 {
    Son2(const shared_ptr<Father2> &m) {
        // This will not add ref count to father2 because myFather is a weak_ptr.
        myFather = m;
    }

    ~Son2() { cout << "Son2 destructor" << endl; }

    weak_ptr<const Father2> myFather;
};

// g++ -std=c++20 -Wall -Wextra -pedantic 176-weak_ptr_and_cycle_prevention.cpp && ./a.out
int main() {
    cout << endl;
    {
        shared_ptr<Father> father = make_shared<Father>();
        cout << "father ref count = " << father.use_count() << endl;

        shared_ptr<Son> son = make_shared<Son>(father);
        cout << "father ref count = " << father.use_count()
             << " son ref count = " << son.use_count() << endl;

        father->setSon(son);
        cout << "father ref count = " << father.use_count()
             << " son ref count = " << son.use_count() << endl;

        // At this point, the reference count of father is 2 and the reference count of son is 2.
        // When it goes out of scope, the reference count of father is 1 and the reference count of
        // son is 1.
    }
    // the reference count of father and son is never going down to 0. the shared momory is never
    // going to be released. the destructor of father and son is never going to be called.

    cout << "--------------------------------" << endl;

    {
        shared_ptr<Father2> father = make_shared<Father2>();
        cout << "father ref count = " << father.use_count() << endl;

        shared_ptr<Son2> son = make_shared<Son2>(father);
        cout << "father ref count = " << father.use_count()
             << " son ref count = " << son.use_count() << endl;

        father->setSon(son);
        cout << "father ref count = " << father.use_count()
             << " son ref count = " << son.use_count() << endl;

        // At this point, the reference count of father is 1 and the reference count of son is 2.
        // When it goes out of scope, the reference count of father is 0 and the reference count of
        // son is 1.
        // The destructor of father is called first which will decrement the son ref count to 0.
        // The destructor of son is called then.
    }

    cout << endl;
}
