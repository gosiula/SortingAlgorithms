#include <iostream>
#include "QuickSort.h"
#include <cstdlib> // Dla funkcji rand()

void QuickSort::sort(int arr[], int n, int pivotChoice) {
    quickSort(arr, 0, n - 1, pivotChoice);
}

void QuickSort::quickSort(int arr[], int low, int high, int pivotChoice) {
    if (low < high) {
        int pivotIndex = choosePivot(arr, low, high, pivotChoice);
        int pivotValue = arr[pivotIndex];

        // Przenoszenie elementów mniejszych od pivota do lewej strony i większych do prawej strony
        int i = low;
        int j = high;
        while (i <= j) {
            while (arr[i] < pivotValue) {
                i++;
            }
            while (arr[j] > pivotValue) {
                j--;
            }
            if (i <= j) {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }

        // Rekurencyjne sortowanie dwóch podziałów
        quickSort(arr, low, j, pivotChoice);
        quickSort(arr, i, high, pivotChoice);
    }
}

int QuickSort::choosePivot(int arr[], int low, int high, int pivotChoice) {
    // Wybór pivota zgodnie z wybraną metodą
    switch (pivotChoice) {
        case 1: // Skrajny lewy
            return low;
        case 2: // Skrajny prawy
            return high;
        case 3: // Środkowy
            return low + (high - low) / 2;
        case 4: // Losowy
            return low + rand() % (high - low + 1);
        default:
            return low; // Domyślnie wybieramy skrajny lewy
    }
}
