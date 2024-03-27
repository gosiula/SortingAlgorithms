#ifndef HEAP_SORT_H
#define HEAP_SORT_H

class HeapSort {
public:
    void sort(int arr[], int size);
private:
    void heapify(int arr[], int size, int i);
};

#endif // HEAP_SORT_H
