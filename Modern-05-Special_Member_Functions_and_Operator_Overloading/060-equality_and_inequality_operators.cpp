#include <iostream>

using namespace std;

class Student {
  private:
    std::string name; // Student's name - not necessarily unique
    int id;           // Student's ID number - unique to each student

  public:
    Student(std::string name, int id) : name(name), id(id) {}

    // Declare as non-member friend to allow access to private members
    friend bool operator==(const Student &lhs, const Student &rhs);
    friend bool operator!=(const Student &lhs, const Student &rhs);

    void print();
};

bool operator==(const Student &lhs, const Student &rhs) { return lhs.id == rhs.id; }
bool operator!=(const Student &lhs, const Student &rhs) { return !(lhs == rhs); }

void Student::print() { cout << "Name: " << name << ", id: " << id << endl; }

////////////////////////////////////////////////////////////

class Student2 {
  private:
    std::string name; // Student's name - not necessarily unique
    int id;           // Student's ID number - unique to each student

  public:
    Student2(std::string name, int id) : name(name), id(id) {}

    // Declare as member functions
    bool operator==(const Student2 &rhs);
    bool operator!=(const Student2 &rhs);

    void print();
};

bool Student2::operator==(const Student2 &rhs) { return id == rhs.id; }
bool Student2::operator!=(const Student2 &rhs) { return !(*this == rhs); }

void Student2::print() { std::cout << "Name: " << name << ", id: " << id << std::endl; }

// g++ -std=c++20 -Wall -Wextra -pedantic 060-equality_and_inequality_operators.cpp && ./a.out
int main() {
    Student stu1("John Smith", 561234);
    Student stu2("John Smith", 453811);

    cout << "stu1: ";
    stu1.print();
    cout << "stu2: ";
    stu2.print();

    cout << boolalpha << endl; // Set output stream format
    cout << "stu1 == stu2: " << (stu1 == stu2) << endl;
    cout << "stu1 != stu2: " << (stu1 != stu2) << endl << endl;

    cout << "--------------------------------" << endl;

    Student2 stu3("Jack Jones", 692837);
    Student2 stu4("Adam Jones", 248939);

    cout << "stu3: ";
    stu3.print();
    cout << "stu4: ";
    stu4.print();

    cout << boolalpha << endl; // Set output stream format
    cout << "stu3 == stu4: " << (stu3 == stu4) << endl;
    cout << "stu3 != stu4: " << (stu3 != stu4) << endl << endl;
}