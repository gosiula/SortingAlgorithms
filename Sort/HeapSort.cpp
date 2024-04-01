#include <iostream>
#ifndef HEAP_SORT_CPP
#define HEAP_SORT_CPP

using namespace std;

template<typename T>
class HeapSort {
public:
    void sort(T arr[], int size);
private:
    void heapify(T arr[], int size, int i);
};

// sortowanie przez kopcowanie
template<typename T>
void HeapSort<T>::sort(T arr[], int size) {
    // budowa kopca (heapify)
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }

    // usuwanie elementow z kopca i ponowne budowanie kopca
    for (int i = size - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// budowanie kopca
template<typename T>
void HeapSort<T>::heapify(T arr[], int size, int i) {
    int largest = i; // inicjalizacja najwiekszego elementu jako korzenia
    int left = 2 * i + 1; // indeks lewego dziecka
    int right = 2 * i + 2; // indeks prawego dziecka

    // sprawdzenie czy lewe dziecko jest wieksze niz korzen
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    // sprawdzenie czy prawe dziecko jest wieksze niz najwiekszy element dotad
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    // jesli najwiekszy element nie jest korzeniem
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // rekurencyjnie heapify poddrzewo
        heapify(arr, size, largest);
    }
}

#endif
