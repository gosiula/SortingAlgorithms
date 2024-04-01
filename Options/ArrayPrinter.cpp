#include <iostream>
#ifndef ARRAY_PRINTER_CPP
#define ARRAY_PRINTER_CPP

using namespace std;

template<typename T>
class ArrayPrinter {
public:
    // funkcja ktora wypisuje zawartosc tablicy 
    void print(T arr[], int size) {
        cout << "Zawartosc tablicy:" << endl;
        for (int i = 0; i < size; ++i) {
            cout << arr[i];
            if (i != size - 1)
                cout << ", ";
        }
        cout << endl << endl;
    }
};

#endif
