#include <iostream>
#ifndef ARRAY_PRINTER_CPP
#define ARRAY_PRINTER_CPP

template<typename T>
class ArrayPrinter {
public:
    void print(T arr[], int size) {
        std::cout << "Zawartosc tablicy:" << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i];
            if (i != size - 1) // Dodaj przecinek poza ostatnim elementem
                std::cout << ", ";
        }
        std::cout << std::endl << std::endl;
    }
};

#endif // ARRAY_PRINTER_CPP
