#ifndef SHELL_SORT_H
#define SHELL_SORT_H

class ShellSort {
public:
    // Sortowanie Shella używając wzoru Knutha
    void sortWithKnuth(int arr[], int n);

    // Sortowanie Shella używając ciągu Sedgewicka
    void sortWithSedgewick(int arr[], int n);
};

#endif // SHELL_SORT_H
