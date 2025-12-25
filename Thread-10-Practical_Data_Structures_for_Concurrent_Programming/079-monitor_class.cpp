#include <iostream>
#include <mutex>
#include <thread>

/**
 * A naive internally synchronized class
 * Has a data member which is a mutex
 * Each member function locks the mutex when called
 *
 * The drawbacks of NaiveBank:
 * - Member functions may need to call other member functions.
 *   - Using multiple locks risks deadlock
 * - Transactions may involve multiple member function calls
 * - Results in many locking and unlocking operations
 *   - Race conditions may occur
 *   - Potential data races
 * - Existing classes need to be modified
 */
class NaiveBank {
    // Mutex to protect the data
    std::mutex mut;

    // Shared data
    // ...
  public:
    void debit(const std::string &name, int amount) {
        std::lock_guard<std::mutex> lck(mut);
        std::cout << "Debiting " << amount << " from " << name << '\n';
    }
    void credit(const std::string &name, int amount) {
        std::lock_guard<std::mutex> lck(mut);
        std::cout << "Crediting " << amount << " to " << name << '\n';
    }
    void print(const std::string &name) {
        std::lock_guard<std::mutex> lck(mut);
        std::cout << "Displaying account for " << name << '\n';
    }
};

////////////////////////////////////////////////////////////

class Bank {
    // Shared data
    // ...
  public:
    void debit(const std::string &name, int amount) {
        std::cout << "Debiting " << amount << " from " << name << '\n';
    }
    void credit(const std::string &name, int amount) {
        std::cout << "Crediting " << amount << " to " << name << '\n';
    }
    void print(const std::string &name) { std::cout << "Displaying account for " << name << '\n'; }
};

/**
 * Monitor class
 * - Works with any class
 *   - Including classes (Bank) that were not designed for threaded code
 *   - No need to modify existing classes (Bank)
 *
 * However, it still has the following drawbacks as NaiveBank:
 * - Member functions may need to call other member functions.
 *   - Using multiple locks risks deadlock
 * - Transactions may involve multiple member function calls
 * - Results in many locking and unlocking operations
 *   - Race conditions may occur
 *   - Potential data races
 */
class BankMonitor {
    std::mutex mut;
    Bank bank;

  public:
    void debit(const std::string &name, int amount) {
        // Lock the mutex and forward the call
        std::lock_guard<std::mutex> lck(mut);
        bank.debit(name, amount);
    }
    void credit(const std::string &name, int amount) {
        // Lock the mutex and forward the call
        std::lock_guard<std::mutex> lck(mut);
        bank.credit(name, amount);
    }
    void print(const std::string &name) {
        // Lock the mutex and forward the call
        std::lock_guard<std::mutex> lck(mut);
        bank.print(name);
    }
};

// g++ -std=c++20 -Wall -Wextra -pedantic 079-monitor_class.cpp && ./a.out
int main() {
    // Transfer $1000 from Peter to Paul
    NaiveBank nb;

    // Call its member functions
    // Each member function locks separately
    std::thread thr([&nb]() {
        nb.debit("Peter", 1000);
        nb.credit("Paul", 1000);
        nb.print("Peter");
        nb.print("Paul");
    });

    thr.join();

    std::cout << "Done\n";

    std::cout << "--------------------------------" << std::endl;

    // Transfer $1000 from Peter to Paul
    BankMonitor bm;

    // Call its member functions
    // Each member function locks separately
    std::thread thr2([&bm] {
        bm.debit("Peter", 1000);
        bm.credit("Paul", 1000);
        bm.print("Peter");
        bm.print("Paul");
    });

    thr2.join();

    std::cout << "Done\n";
}
