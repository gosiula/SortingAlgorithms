#include <iostream>
#include <cstdlib> // Dodaj ten nagłówek
#ifndef QUICK_SORT_CPP
#define QUICK_SORT_CPP

using namespace std;

template<typename T>
class QuickSort {
public:
    void sort(T arr[], int n, int pivotChoice);
private:
    void quickSort(T arr[], int low, int high, int pivotChoice);
    int choosePivot(T arr[], int low, int high, int pivotChoice);
};

template<typename T>
void QuickSort<T>::sort(T arr[], int n, int pivotChoice) {
    quickSort(arr, 0, n - 1, pivotChoice);
}

// sortowanie szybkie
template<typename T>
void QuickSort<T>::quickSort(T arr[], int low, int high, int pivotChoice) {
    if (low < high) {
        int pivotIndex = choosePivot(arr, low, high, pivotChoice); // pivot
        T pivotValue = arr[pivotIndex];

        // przenoszenie elementow mniejszych od pivota do lewej strony i wiekszych do prawej strony
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

        // rekurencyjne sortowanie dwoch podzialow
        quickSort(arr, low, j, pivotChoice);
        quickSort(arr, i, high, pivotChoice);
    }
}

template<typename T>
int QuickSort<T>::choosePivot(T arr[], int low, int high, int pivotChoice) {
    // wybór pivota zgodnie z wybrana metoda
    switch (pivotChoice) {
        case 1: // skrajny lewy
            return low;
        case 2: // skrajny prawy
            return high;
        case 3: // srodkowy
            return low + (high - low) / 2;
        case 4: // losowy
            return low + rand() % (high - low + 1);
        default:
            return low; // domyslnie wybieramy skrajny lewy
    }
}

#endif 