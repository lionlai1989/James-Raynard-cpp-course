/**
 * In object-oriented programming, we aim to separate the interface from the implementation.
 * 1. Clients do not need to know internal details of the class.
 * 2. Clients do not need to modify their code if the implementation changes.
 *
 * Typically in C++, we put the class definition in a header file and the member function
 * definitions in a source file where as public, private and protected specifiers are used to
 * control access to the members. However, some implementation details are still visible to clients,
 * including names of private data members, prototypes of private/protected member functions, and
 * definitions of inline member functions. All clients which use the class must include the header
 * file, which also means that any implementation changes will require recompilation of all clients.
 *
 * The Handle-Body Pattern is introduced to address the above issues. The basic idea is to split the
 * class into two parts:
 * The first part is the "Handle" class, which is an outer class the provides the interface to
 * clients. The second part is the "Body" class, which is an inner class that provides the
 * implementation.
 * When a client creates a Handle object, the Handle creates a Body object. When a client calls a
 * member function on the Handle object, the call is forwarded to the Body object.
 * 1. "Handle.h" defines the Handle class and it contains public member functions only.
 * 2. "Body.h" defines the Body class and it contains the full class definition.
 * 3. Clients #include "Handle.h", but not "Body.h".
 * 4. If the implementation details change, it only affects "Body.h" and not "Handle.h".
 * 5. Clients do not need to be recompiled.
 *
 * Static vs Dynamic linking:
 * 1. Static linking: The compiler links the code at compile time.
 * 2. Dynamic linking: The compiler links the code at run time.
 *
 * There are multiple ways of implementing the Handle-Body Pattern. The "pImpl Idiom" is one of
 * them.
 * In the "pImpl Idiom", the Handle class has a private member which is a pointer to a Body object.
 * Thus, "Pointer to Implementation", pImpl. This is also known as "compiler firewall"
 *
 */

#include "Date.h"
#include <iostream>

// g++ -std=c++20 -Wall -Wextra -pedantic Client.cpp Date.cpp && ./a.out
int main() {
    // The following line will not compile due to
    // Date_impl date(16, 11, 2019);

    Date date(16, 11, 2019);
    date.print();
    std::cout << "\n";
    date.set_day(17);
    date.print();
    std::cout << "\n";
}
