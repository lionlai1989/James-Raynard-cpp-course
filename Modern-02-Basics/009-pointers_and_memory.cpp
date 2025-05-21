#include <cstring>  // strlen
#include <iostream> // cout

using namespace std;

void goodfunc() {
    int *p4 = new int{42}; // Allocate memory in function
    cout << "p4 = " << p4 << endl;
    delete p4; // Release memory
    // *p4 = 1; p4 can't be used after delete
    return;
} // No memory leak

void badfunc() {
    int *p4 = new int{42}; // Allocate memory in function
    cout << "p4 = " << p4 << endl;
    return; // Return without releasing memory
} // Memory leak!

void print_arr(int *arr) {
    // arr decays to a pointer to the first element of the array
    cout << "In print_arr, ";
    cout << "size of arr: " << sizeof(arr) << " bytes" << endl;
}

// g++ -std=c++17 -Wall -Wextra -pedantic 009-pointers_and_memory.cpp && ./a.out
int main() {
    int i{1};                        // i is a stack variable
    int *p1 = &i;                    // p1 is a pointer to int. Its value is the address of i
    cout << "p1 = " << p1 << endl;   // Displays the address of i
    cout << "*p1 = " << *p1 << endl; // Displays the value of i

    int *p2 = new int;     // p2 points to memory allocated from the heap
    int *p3 = new int{36}; // p3 points to int with initial value 36 (C++11)
    // int *p3 = new int(36);                    // older versions of C++
    cout << "p2 = " << p2 << endl;
    cout << "p3 = " << p3 << endl;
    cout << "*p2 = " << *p2 << endl;
    cout << "*p3 = " << *p3 << endl;
    free(p2);
    free(p3);

    badfunc();
    goodfunc();

    const char *s = "Hello";
    cout << "size of s: " << sizeof(s) << " bytes (pointer size)" << endl;
    cout << "length of s: " << strlen(s) << " characters" << endl;

    int arr[5] = {1, 2, 3, 4, 5};
    print_arr(arr);
    cout << "size of arr: " << sizeof(arr) << " bytes" << endl;
    cout << "number of elements in arr: " << sizeof(arr) / sizeof(arr[0]) << endl;

    cout << "Allocating array for array\n";
    const int array_size = 10;
    int *pa = new int[array_size];
    cout << "size of pa: " << sizeof(pa) << " bytes (pointer size)" << endl;
    cout << "number of elements in pa: " << array_size << endl;

    cout << "Populating array\n";
    for (int i = 0; i < array_size; ++i) {
        pa[i] = i;
    }

    cout << "Array elements:\n";
    for (int i = 0; i < array_size; ++i) {
        cout << pa[i] << ", ";
    }

    cout << endl;

    cout << "Releasing array's memory\n";
    delete[] pa;

    cout << "Finished!\n";

    return 0;
}
