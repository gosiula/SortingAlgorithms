#include <iostream>
#ifndef SHELL_SORT_CPP
#define SHELL_SORT_CPP

using namespace std;

template<typename T>
class ShellSort {
public:
    // sortowanie shella - knuth
    void sortWithKnuth(T arr[], int n) {
        int h = 1;
        // wyznaczenie początkowego kroku
        while (h < n / 3) {
            h = 3 * h + 1;
        }
        // sortowanie wg kroku h
        while (h >= 1) {
            for (int i = h; i < n; i++) {
                // sortowanie przez wstawianie wg kroku h
                for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h) {
                    std::swap(arr[j], arr[j - h]);
                }
            }
            // zmniejszenie kroku
            h /= 3;
        }
    }

    // sortowanie shella - sedgewick
    void sortWithSedgewick(T arr[], int n) {
        // rozne wartosci krokow dla sortowania wg sedgewicka
        int gaps[] = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
        int gapsSize = sizeof(gaps) / sizeof(gaps[0]);

        // iteracja po roznych krokach
        for (int gapIndex = 0; gapIndex < gapsSize; gapIndex++) {
            int gap = gaps[gapIndex];
            // sortowanie wg aktualnego kroku
            for (int i = gap; i < n; i++) {
                T temp = arr[i];
                int j;
                // sortowanie przez wstawianie wg aktualnego kroku
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
    }
};

#endif
