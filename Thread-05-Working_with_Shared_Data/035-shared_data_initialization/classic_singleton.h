/**
 * A Singleton class has only a single instance. E.g., a logger class that maintains an audit trail.
 * - The constructor is private.
 * - The copy and move operators are deleted.
 * - A static member function returns the unique instance. If the instance does not already exist,
 *   it is created and initialized. Otherwise, the existing object is returned.
 */

#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

// Singleton class definition
class Singleton {
  private:
    // Pointer to unique instance. There is only ONE instance of this pointer "single".
    static Singleton *single;

    // The constructor is private to prevent being constructed multiple times.
    Singleton() { std::cout << "Initializing Singleton" << std::endl; }

  public:
    // The copy and move operators are deleted.
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;

    // Static member function to obtain the Singleton object. This static member function is not
    // associated to any Singleton objects so we can call this function even without the existence
    // of any Singleton instances.
    static Singleton *get_Singleton();
};

#endif // Singleton_H