#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <cstdlib> // Dla funkcji rand()

class QuickSort {
public:
    // Funkcja sortująca szybka z wyborem pivota
    void sort(int arr[], int n, int pivotChoice);

private:
    // Funkcja pomocnicza do sortowania szybkiego
    void quickSort(int arr[], int low, int high, int pivotChoice);

    // Funkcja pomocnicza do wyboru pivota
    int choosePivot(int arr[], int low, int high, int pivotChoice);
};

#endif // QUICK_SORT_H
