#include <iostream>
#include "Sort\HeapSort.h"

void HeapSort::sort(int arr[], int size) {
    // Budowa kopca (Heapify)
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }

    // Usuwanie elementów z kopca i ponowne budowanie kopca
    for (int i = size - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void HeapSort::heapify(int arr[], int size, int i) {
    int largest = i; // Inicjalizacja największego elementu jako korzenia
    int left = 2 * i + 1; // Indeks lewego dziecka
    int right = 2 * i + 2; // Indeks prawego dziecka

    // Sprawdzenie, czy lewe dziecko jest większe niż korzeń
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    // Sprawdzenie, czy prawe dziecko jest większe niż największy element dotąd
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    // Jeśli największy element nie jest korzeniem
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Rekurencyjnie heapify poddrzewo
        heapify(arr, size, largest);
    }
}
