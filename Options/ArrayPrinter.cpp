#include <iostream>
#include "Options\ArrayPrinter.h"

void ArrayPrinter::print(int arr[], int size) {
    std::cout << "Zawartosc tablicy:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}
