/*
  Reverse Array Program
  This program populates an array with values, displays the original array,
  then calls a function that dynamically creates a new array containing the
  original values in reverse order. The dynamically allocated memory is
  deallocated before the program terminates.
*/

#include <iostream>
using namespace std;


int* ReverseArray(int const arr[], int size);


void print(int const arr[], int size);

int main() {
    const int SIZE = 10;
    int arr[SIZE];

    // Populate the original array with values 1..10
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    cout << "Original array:\n\n";
    print(arr, SIZE);

    int* reversed = ReverseArray(arr, SIZE);

    cout << "\n\nReversed array:\n\n";
    print(reversed, SIZE);

    // Deallocate dynamic memory before terminating
    delete[] reversed;
    reversed = nullptr;

    return 0;
}

int* ReverseArray(int const arr[], int size) {
    int* rev = new int[size];

    // Copy from arr into rev in reverse order
    for (int i = 0; i < size; i++) {
        rev[i] = arr[size - 1 - i];
    }

    return rev;
}

void print(int const arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << (i == size - 1 ? "" : " ");
    }
}
