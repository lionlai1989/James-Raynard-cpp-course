
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

// Singleton class definition
class Singleton {
  private:
    // there is no static data member as opposed to static data member in "classic_singleton.h".

  public:
    // The copy and move operators are deleted
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;

    // Notice that Constructor is now public as opposed to private in "classic_singleton.h"
    Singleton() { std::cout << "Initializing Singleton\n"; }
};

// Function to obtain the Singleton object. Notice that it's now outside the class.
Singleton &get_Singleton();

#endif // SINGLETON_H