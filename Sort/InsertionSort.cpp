#include <iostream>
#ifndef INSERTION_SORT_CPP
#define INSERTION_SORT_CPP

using namespace std;

template<typename T>
class InsertionSort {
public:
    void sort(T arr[], int size);
};

// sortowanie przez wstawianie
template<typename T>
void InsertionSort<T>::sort(T arr[], int size) {
    // implementacja algorytmu sortowania przez wstawianie
    for (int i = 1; i < size; ++i) {
        T key = arr[i]; // na podstawie key zmieniamy kolejnosc liczb - jesli element jest wiekszy to przesuwamy go w prawo
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

#endif