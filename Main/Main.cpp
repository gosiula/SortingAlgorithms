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
#include "Options/ResultSaver.cpp"

int main() {
    int repetition = 100;
    bool exitProgram = false;

    int size = 0;
    int dataTypeChoice = 0;

    std::string arrangement;

    Sorting<int> sortingInt;
    Sorting<float> sortingFloat;
    Sorting<double> sortingDouble;

    ResultSaver resultSaver;

    DataInput<int> dataInputInt;
    DataInput<float> dataInputFloat;
    DataInput<double> dataInputDouble;

    do {
        int* originalArrayInt = new int[size];
        float* originalArrayFloat = new float[size];
        double* originalArrayDouble = new double[size];

        std::cout << "wybierz typ danych (1 - int, 2 - float, 3 - double): ";
        std::cin >> dataTypeChoice;

        switch (dataTypeChoice) {
            case 1:
                dataInputInt.getElements(originalArrayInt, size, exitProgram, dataTypeChoice);
                if(exitProgram == true) return 0;
                sortingInt.setInputFilename(dataInputInt.getInputFilename());
                resultSaver.setOriginalFilename(dataInputInt.getInputFilename());
                arrangement = dataInputInt.getArrangement();
                sortingInt.performSorting(originalArrayInt, size, exitProgram, repetition, dataTypeChoice, arrangement);
                break;
            case 2:
                dataInputFloat.getElements(originalArrayFloat, size, exitProgram, dataTypeChoice);
                if(exitProgram == true) return 0;
                sortingFloat.setInputFilename(dataInputFloat.getInputFilename());
                resultSaver.setOriginalFilename(dataInputFloat.getInputFilename());
                arrangement = dataInputFloat.getArrangement();
                sortingFloat.performSorting(originalArrayFloat, size, exitProgram, repetition, dataTypeChoice, arrangement);
                break;
            case 3:
                dataInputDouble.getElements(originalArrayDouble, size, exitProgram, dataTypeChoice);
                if(exitProgram == true) return 0;
                sortingDouble.setInputFilename(dataInputDouble.getInputFilename());
                resultSaver.setOriginalFilename(dataInputDouble.getInputFilename());
                arrangement = dataInputDouble.getArrangement();
                sortingDouble.performSorting(originalArrayDouble, size, exitProgram, repetition, dataTypeChoice, arrangement);
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
