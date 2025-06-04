/**
 * There are two ways to create a unique_ptr object:
 * 1. Call the move constructor with the return value from make_unique(), which calls new()
 * internally.
 * 2. Call the constructor with a traditional pointer as an argument.
 *
 * unique_ptr's destructor calls delete() on the object it owns. If the pointer was not returned by
 * new, this will be disastrous.
 *
 * To avoid this, we can use a custom deleter.
 *
 */

#include <iostream>
#include <memory>

/// Code from C Networking API ///
struct destination { /* ... */
};
struct connection { /* ... */
};

// Function to open a connection
connection connect(destination dest) {
    std::cout << "Connecting\n";
    connection conn;
    return conn;
}

// Function to close a connection
void disconnect(connection conn) { std::cout << "Disconnecting\n"; }

/// End of code from C Networking API ///

void get_data(const destination &dest) {
    // conn is a local (stack) variable. The object conn is constructed on the function’s stack
    // frame. When get_data(...) returns, conn’s destructor is invoked automatically by the compiler
    // (because it was never `new`-ed).
    connection conn = connect(dest);

    // unique_ptr believes it “owns” a heap allocation. That is, you are telling unique_ptr to call
    // delete on the address of that stack variable.
    // The problem is that since &conn was never returned by new, `delete &conn;` is not valid: it
    // tries to free stack memory. That immediately invokes undefined behavior (and most likely
    // crashes at runtime, or corrupts the stack).
    std::unique_ptr<connection> ptr(&conn);

    std::cout << "Getting data from get_data...\n";

    // Upon returning from the function, the destructor of unique_ptr will be called, that is,
    // delete() will be called on the conn object.
}

// Custom deleter to close network connection
auto end_connection = [](connection *conn) { disconnect(*conn); };

void get_data2(const destination &dest) {

    connection conn = connect(dest);

    /**
     * A custom "deleter " is provided. It's a callable object. It will be invoked by the destructor
     * instead of delete.
     *
     * The managed pointer is passed to the deleter. The deleter then releases the resource as
     * appropriate. In this case, it calls disconnect() instead of "delete".
     *
     * The deleter's type is given as an optional template argument to unique_ptr. Here,
     * end_connection is a lambda expression whose type is known to the compiler with the
     * `decltype(end_connection)` syntax.
     */
    std::unique_ptr<connection, decltype(end_connection)> p(&conn, end_connection);

    std::cout << "Getting data from get_data2...\n";

    // The custom deleter is invoked successfully when going out of scope.
    throw std::runtime_error("Error");

    std::cout << "Exiting get_data2...\n"; // This line is never reached.
}

// g++ -std=c++20 -Wall -Wextra -pedantic 170-unique_pointers_and_custom_deleters.cpp && ./a.out
int main() {
    destination dest;

    // get_data(dest);

    try {
        get_data2(dest);
    } catch (const std::runtime_error &e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
