#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "NumberGenerator/DataInput.cpp"
#include "NumberGenerator/Sorting.cpp"
#include "Sort/InsertionSort.cpp"
#include "Sort/HeapSort.cpp"
#include "Sort/ShellSort.cpp"
#include "Sort/QuickSort.cpp"
#include "Options/ArrayPrinter.cpp"
#include "Options/SortingChecker.cpp"

int main() {
    bool exitProgram = false;

    int size = 0;
    int dataTypeChoice = 0;

    DataInput<int> dataInputInt;
    DataInput<float> dataInputFloat;
    DataInput<double> dataInputDouble;

    Sorting<int> sortingInt;
    Sorting<float> sortingFloat;
    Sorting<double> sortingDouble;

    do {
        int* originalArrayInt = new int[size];
        float* originalArrayFloat = new float[size];
        double* originalArrayDouble = new double[size];

        std::cout << "wybierz typ danych (1 - int, 2 - float, 3 - double): ";
        std::cin >> dataTypeChoice;

        switch (dataTypeChoice) {
            case 1:
                dataInputInt.getElements(originalArrayInt, size, exitProgram);
                if(exitProgram == true) return 0;
                sortingInt.performSorting(originalArrayInt, size, exitProgram);
                break;
            case 2:
                dataInputFloat.getElements(originalArrayFloat, size, exitProgram);
                if(exitProgram == true) return 0;
                sortingFloat.performSorting(originalArrayFloat, size, exitProgram);
                break;
            case 3:
                dataInputDouble.getElements(originalArrayDouble, size, exitProgram);
                if(exitProgram == true) return 0;
                sortingDouble.performSorting(originalArrayDouble, size, exitProgram);
                break;
            default:
                std::cout << "nieprawidlowy wybor typu danych" << std::endl;
                return 1;
        }

        delete[] originalArrayInt;
        delete[] originalArrayFloat;
        delete[] originalArrayDouble;
    } while (!exitProgram);

    return 0;
}
