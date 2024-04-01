#include <iostream>
#ifndef SORTING_CHECKER_CPP
#define SORTING_CHECKER_CPP

template<typename T>
class SortingChecker {
public:

    // funkcja sprawdzajaca czy tablica jest posortowana rosnaco
    bool isSorted(const T* array, int size) {
        for (int i = 0; i < size - 1; ++i) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
        return true;
    }
};

#endif