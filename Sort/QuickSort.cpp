#include <iostream>
#include <cstdlib> // Dodaj ten nagłówek

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

template<typename T>
void QuickSort<T>::quickSort(T arr[], int low, int high, int pivotChoice) {
    if (low < high) {
        int pivotIndex = choosePivot(arr, low, high, pivotChoice);
        T pivotValue = arr[pivotIndex];

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

template<typename T>
int QuickSort<T>::choosePivot(T arr[], int low, int high, int pivotChoice) {
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