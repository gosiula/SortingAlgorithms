#include <iostream>
#include "ShellSort.h"

void ShellSort::sortWithKnuth(int arr[], int n) {
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h) {
                std::swap(arr[j], arr[j - h]);
            }
        }
        h /= 3;
    }
}

void ShellSort::sortWithSedgewick(int arr[], int n) {
    int gaps[] = {1750, 701, 301, 132, 57, 23, 10, 4, 1};
    int gapsSize = sizeof(gaps) / sizeof(gaps[0]);

    for (int gapIndex = 0; gapIndex < gapsSize; gapIndex++) {
        int gap = gaps[gapIndex];
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
