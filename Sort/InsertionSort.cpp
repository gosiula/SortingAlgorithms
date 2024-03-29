#include <iostream>

template<typename T>
class InsertionSort {
public:
    void sort(T arr[], int size);
};

template<typename T>
void InsertionSort<T>::sort(T arr[], int size) {
    // Implementacja algorytmu sortowania przez wstawianie
    for (int i = 1; i < size; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

