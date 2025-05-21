#include <cassert>  // assert
#include <iostream> // cout
#include <string>   // string
#include <vector>   // vector

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 010-array_string_and_vector.cpp && ./a.out
int main() {
    // Array. Allocated on the stack.
    int arr[5] = {1, 2, 3, 4, 5};
    const int constArrSize = 5;
    int arr2[constArrSize] = {1, 2, 3, 4, 5};
    for (int i = 0; i < constArrSize; i++) {
        assert(arr[i] == arr2[i]);
    }

    // Dynamic array. Allocated on the heap.
    int *pArr = new int[5];
    delete[] pArr;

    // C-style string. Allocated on the stack.
    const char *s1 = "Hello";
    const char s2[] = {'H', 'e', 'l', 'l', 'o', '\0'};
    for (int i = 0; i <= 5; i++) {
        assert(s1[i] == s2[i]);
    }

    // std::string. Allocated on the heap.
    string str{"Hello"};
    for (size_t i = 0; i < str.size(); i++) {
        cout << str[i];
    }

    // std::vector. Allocated on the heap.
    vector<int> vec{1, 2, 3, 4, 5};
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
    }

    return 0;
}
