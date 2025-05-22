#include <iostream> // cout, endl, boolalpha

using namespace std;

class Internet {
  public:
    void connect() { cout << "Connected to internet\n"; }
    void login(const string &id, const string &pw) {
        cout << "Logged on with username " << id;
        cout << " and password " << pw << endl;
    }
};

class Refrigerator1 {
  private:
    int temperature{2};
    bool door_open{false};
    bool power_on{true};
    Internet internet;

  public:
    void init(const string &id, const string &pw) {
        // Don't Repeat Yourself (DRY)
        internet.connect();
        internet.login(id, pw);
    }

    // Default constructor
    Refrigerator1() { init("me", "secret"); }

    // Constructor using default login
    Refrigerator1(int temperature) : temperature(temperature) { init("me", "secret"); }

    // Constructor using default temperature
    Refrigerator1(const string &id, const string &pw) { init(id, pw); }

    // Constructor with no defaults
    Refrigerator1(int temperature, const string &id, const string &pw) : temperature(temperature) { init(id, pw); }

    void print() {
        cout << "temperature = " << temperature << endl;
        cout << boolalpha;
        cout << "door_open = " << door_open << endl;
        cout << "power_on = " << power_on << endl;
    }
};

class Refrigerator2 {
  private:
    int temperature{2};
    bool door_open{false};
    bool power_on{true};
    Internet internet;

  public:
    /**
     * Delegating constructor is a constructor that calls another constructor to initialize the object.
     * It is a way to avoid code duplication.
     */

    // Default constructor
    Refrigerator2() : Refrigerator2(2, "me", "secret") {}

    // Constructor using default login
    Refrigerator2(int temperature) : Refrigerator2(temperature, "me", "secret") {}

    // Constructor using default temperature
    Refrigerator2(const string &id, const string &pw) : Refrigerator2(2, id, pw) {}

    // Constructor with no defaults
    Refrigerator2(int temperature, const string &id, const string &pw) : temperature(temperature) {
        internet.connect();
        internet.login(id, pw);
    }

    void print() {
        cout << "temperature = " << temperature << endl;
        cout << boolalpha;
        cout << "door_open = " << door_open << endl;
        cout << "power_on = " << power_on << endl;
    }
};

// g++ -std=c++17 -Wall -Wextra -pedantic 047-constructors.cpp && ./a.out
int main() {
    Refrigerator1 fridge1{0};
    fridge1.print();
    Refrigerator2 fridge2{"hello", "world"};
    fridge2.print();
}
