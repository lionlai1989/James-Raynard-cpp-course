// Classic Singleton class implementation
#include "classic_singleton.h"

// Static member function to obtain the Singleton object
Singleton *Singleton::get_Singleton() {
    /**
     * In a single-threaded program, this function works perfectly. But in a multi-threaded program,
     * it has a DATA RACE. Multiple threads can execute this progrom concurrently, which will result
     * to multiple Singleton instances being created.
     */

    if (single == nullptr)
        // Only one constructor shall be called.
        single = new Singleton;
    return single;
}
