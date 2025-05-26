#include <iostream> // cout

using namespace std;

// g++ -std=c++17 -Wall -Wextra -pedantic 012-two_dimensional_arrays.cpp && ./a.out
int main() {
    string names1[] = {"Fred", "Wilma", "Pebbles", "Dino", "Barney", "Betty", "Bamm-Bamm", "Hoppy"};
    cout << "names[1][2] = " << names1[1 * 4 + 2] << endl;
    cout << "\nThe elements of names1 are:\n";
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 4; ++col) {
            cout << names1[row * 4 + col] << ", ";
        }
        cout << "\n";
    }

    cout << '\n';

    string names2[2][4] = {{"Fred", "Wilma", "Pebbles", "Dino"}, {"Barney", "Betty", "Bamm-Bamm", "Hoppy"}};
    cout << "names[1][2] = " << names2[1][2] << endl;
    cout << "\nThe elements of names2 are:\n";
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 4; ++col) {
            cout << names2[row][col] << ", ";
        }
        cout << "\n";
    }
}
