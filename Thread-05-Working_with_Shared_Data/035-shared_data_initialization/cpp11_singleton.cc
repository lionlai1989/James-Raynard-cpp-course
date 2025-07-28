// Singleton class implementation (Meyers Singleton)
// Uses C++11's guarantees about initializing static variables
#include "cpp11_singleton.h"

// Function to obtain the Singleton object
Singleton &get_Singleton() {
    /**
     * The static local variable initialization in C++11 is now well-defined.
     * Only one thread can initialize the variable. Any other thread that reaches the declaration is
     * blocked and they must wait until the first thread has finished initializing the variable.
     * There is NO DATA RACE in the initialization.
     * But the usual rules for shared data and data race still hold after initialization. Thus, we
     * must still use lock to protect the Singleton object "single" while reading/writing it.
     */

    // Initialized by the first thread that executes this code. Subsequent threads use the object
    // created by the first thread. The object "single" remains in existence until the program ends.
    // Notice that the object is returned by reference.
    // Question 1: will there be a dangling reference?
    // Question 2: if single is non-static. will there be a dangling reference?
    static Singleton single;
    return single;
}
