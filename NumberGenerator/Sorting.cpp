#ifndef SORTING_CPP
#define SORTING_CPP

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include "Sort/InsertionSort.cpp"
#include "Sort/HeapSort.cpp"
#include "Sort/ShellSort.cpp"
#include "Sort/QuickSort.cpp"
#include "Options/ArrayPrinter.cpp"
#include "Options/SortingChecker.cpp"
#include "Options/ResultSaver.cpp"
#include "NumberGenerator/DataInput.cpp"

using namespace std;

template<typename T>
class Sorting {
private:
    ArrayPrinter<T> arrayPrinter;
    SortingChecker<T> sortingChecker;
    InsertionSort<T> insertionSorter;
    HeapSort<T> heapSorter;
    ShellSort<T> shellSorter;
    QuickSort<T> quickSorter;
    std::string filename;
    DataInput<T> dataInput;
    ResultSaver resultSaver;
    int repetition;  // Nowo dodane pole repetition
    T* originalArray;  // Nowo dodane pole originalArray
    int size;  // Nowo dodane pole size
    int type;
    string arrangement;

public:
    void setInputFilename(const std::string& filename) {
        this->filename = filename;
    }

    std::string getInputFilename() const {
        return filename;
    }

template<typename SorterType, typename SortFunction>
void performSortingAndSaveResults(SorterType& sorter, SortFunction sortFunction, T* originalArray, int size, int repetition, int type, const std::string& arrangement, const std::string& filename) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    QueryPerformanceFrequency(&frequency);

    double totalTime = 0.0;

    if (repetition == 1) {
        // Usunięcie zawartości posortowanej tablicy
        T* dynamicArray = new T[size];
        for (int j = 0; j < size; ++j) {
            dynamicArray[j] = originalArray[j];
        }

        QueryPerformanceCounter(&start);
        (sorter.*sortFunction)(dynamicArray, size);
        QueryPerformanceCounter(&end);

        totalTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

        std::cout << "\n\ntablica zostala posortowana przez InsertionSort" << std::endl;
        arrayPrinter.print(dynamicArray, size);
        if (sortingChecker.isSorted(dynamicArray, size)) {
            std::cout << "liczby poprawnie posortowane" << std::endl;
        } else {
            std::cout << "liczby niepoprawnie posortowane" << std::endl;
        }

        std::cout << "czas sortowania: " << std::fixed << std::setprecision(4) << totalTime * 1000.0 << " ms" << std::endl;

        delete[] dynamicArray; // Zwolnienie pamięci
    } else {
        for(int i = 1; i <= repetition; ++i) {
            // Czyszczenie zawartości posortowanej tablicy
            T* dynamicArray = new T[size];
            for (int j = 0; j < size; ++j) {
                dynamicArray[j] = originalArray[j];
            }

            QueryPerformanceCounter(&start);
            (sorter.*sortFunction)(dynamicArray, size);
            QueryPerformanceCounter(&end);

            totalTime += static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

            if (sortingChecker.isSorted(dynamicArray, size)) {
                std::cout << i << ". liczby poprawnie posortowane : ";
            } else {
                std::cout << i << ". liczby niepoprawnie posortowane";
            }

            std::cout << "czas sortowania: " << std::fixed << std::setprecision(4) << (totalTime / i) * 1000.0 << " ms" << std::endl;

            delete[] dynamicArray; // Zwolnienie pamięci
        }
    }

    // Zapisz wyniki do pliku
    resultSaver.saveResults(type, size, repetition, totalTime / repetition * 1000.0, arrangement, filename);
}

template<typename SorterType, typename SortFunction>
void performSortingAndSaveResultsForQuickSort(int pivot, SorterType& sorter, SortFunction sortFunction, T* originalArray, int size, int repetition, int type, const std::string& arrangement, const std::string& filename) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    QueryPerformanceFrequency(&frequency);

    double totalTime = 0.0;

    if (repetition == 1) {
        // Usunięcie zawartości posortowanej tablicy
        T* dynamicArray = new T[size];
        for (int j = 0; j < size; ++j) {
            dynamicArray[j] = originalArray[j];
        }

        QueryPerformanceCounter(&start);
        (sorter.*sortFunction)(dynamicArray, size, pivot);
        QueryPerformanceCounter(&end);

        totalTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

        std::cout << "\n\ntablica zostala posortowana przez InsertionSort" << std::endl;
        arrayPrinter.print(dynamicArray, size);
        if (sortingChecker.isSorted(dynamicArray, size)) {
            std::cout << "liczby poprawnie posortowane" << std::endl;
        } else {
            std::cout << "liczby niepoprawnie posortowane" << std::endl;
        }

        std::cout << "czas sortowania: " << std::fixed << std::setprecision(4) << totalTime * 1000.0 << " ms" << std::endl;

        delete[] dynamicArray; // Zwolnienie pamięci
    } else {
        for(int i = 1; i <= repetition; ++i) {
            // Czyszczenie zawartości posortowanej tablicy
            T* dynamicArray = new T[size];
            for (int j = 0; j < size; ++j) {
                dynamicArray[j] = originalArray[j];
            }

            QueryPerformanceCounter(&start);
            (sorter.*sortFunction)(dynamicArray, size, pivot);
            QueryPerformanceCounter(&end);

            totalTime += static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

            if (sortingChecker.isSorted(dynamicArray, size)) {
                std::cout << i << ". liczby poprawnie posortowane : ";
            } else {
                std::cout << i << ". liczby niepoprawnie posortowane";
            }

            std::cout << "czas sortowania: " << std::fixed << std::setprecision(4) << (totalTime / i) * 1000.0 << " ms" << std::endl;

            delete[] dynamicArray; // Zwolnienie pamięci
        }
    }

    // Zapisz wyniki do pliku
    resultSaver.saveResults(type, size, repetition, totalTime / repetition * 1000.0, arrangement, filename);
}



    void performSorting(T* originalArray, int size, bool& exitProgram, int repetition, int type, const std::string& arrangement) {
        clock_t start, end;
        double elapsedTimeMillis;
        int choice;
        int innerChoice;
        bool innerLoop = false;
        double averageTime = 0.0;

        do {
            std::cout << "\n\nMENU GLOWNE" << std::endl;
            std::cout << "1. sortowanie przez wstawianie" << std::endl;
            std::cout << "2. sortowanie przez kopcowanie" << std::endl;
            std::cout << "3. sortowanie Shella" << std::endl;
            std::cout << "4. sortowanie szybkie" << std::endl;
            std::cout << "5. wczytaj ponownie dane" << std::endl;
            std::cout << "6. wyjscie z programu\n" << std::endl;
            std::cout << "wybierz opcje (1-6): ";
            std::cin >> choice;
            std::cout << std::endl;

            innerLoop = false;

            switch (choice) {
                case 1:
                    do {
                        std::ifstream inputFile(this->filename.c_str());
                        if (!inputFile.is_open()) {
                            std::cout << "Nie mozna otworzyc  " << this->filename << std::endl;
                            std::cout << this->filename << std::endl;
                            return;

                        }

                        inputFile >> size; // Wczytanie liczby elementów
                        delete[] originalArray;
                        originalArray = new T[size];

                        // Wczytanie liczb zmiennoprzecinkowych do tablicy
                        for (int i = 0; i < size; ++i) {
                            T value;
                            inputFile >> value;
                            originalArray[i] = value;
                        }
                        inputFile.close();

                        T* dynamicArray = new T[size];
                        for (int i = 0; i < size; ++i) {
                            dynamicArray[i] = originalArray[i];
                        }

                        std::cout << "\n\nMENU - sortowanie przez wstawianie" << std::endl;
                        std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                        std::cout << "2. posortuj" << std::endl;
                        std::cout << "3. cofnij do menu glownego" << std::endl;
                        std::cout << "4. wybierz ponownie dane wejsciowe" << std::endl;
                        std::cout << "5. wyjscie z programu" << std::endl;
                        std::cout << "wybierz opcje (1-5): ";
                        std::cin >> innerChoice;

                        double totalTime = 0.0;

                        switch (innerChoice) {
                            case 1:
                                arrayPrinter.print(originalArray, size);
                                break;
                            case 2:
                                performSortingAndSaveResults(insertionSorter, &InsertionSort<T>::sort, originalArray, size, repetition, type, arrangement, filename);                              
                                break;
                            case 3:
                                innerLoop = true;
                                break;
                            case 4:
                                delete[] dynamicArray;
                                return;
                            case 5:
                                exitProgram = true;
                                return;
                            default:
                                std::cout << "nieprawidlowa opcja - wybierz opcje od 1 do 5" << std::endl;
                                break;
                        }
                    } while (!innerLoop);
                    break;
                case 2:
                    do {
                        std::ifstream inputFile(filename.c_str());
                        if (!inputFile.is_open()) {
                            std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
                            return;
                        }

                        inputFile >> size; // Wczytanie liczby zmiennoprzecinkowej jako rozmiaru tablicy
                        delete[] originalArray;
                        originalArray = new T[size];

                        // Wczytanie liczb zmiennoprzecinkowych do tablicy
                        for (int i = 0; i < size; ++i) {
                            T value;
                            inputFile >> value;
                            originalArray[i] = value;
                        }
                        inputFile.close();

                        T* dynamicArray = new T[size];
                        for (int i = 0; i < size; ++i) {
                            dynamicArray[i] = originalArray[i];
                        }


                        std::cout << "\n\nMENU - sortowanie przez kopcowanie" << std::endl;
                        std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                        std::cout << "2. posortuj" << std::endl;
                        std::cout << "3. cofnij do menu glownego" << std::endl;
                        std::cout << "4. wybierz ponownie dane wejsciowe" << std::endl;
                        std::cout << "5. wyjscie z programu" << std::endl;
                        std::cout << "wybierz opcje (1-5): ";
                        std::cin >> innerChoice;

                        switch (innerChoice) {
                            case 1:
                                arrayPrinter.print(originalArray, size);
                                break;
                            case 2:
                                performSortingAndSaveResults(heapSorter, &HeapSort<T>::sort, dynamicArray, size, repetition, type, arrangement, filename);
                                break;
                            case 3:
                                innerLoop = true;
                                break;
                            case 4:
                                delete[] dynamicArray; // Zwolnienie pamięci
                                return;
                            case 5:
                                exitProgram = true;
                                return;
                            default:
                                std::cout << "nieprawidlowa opcja - wybierz opcje od 1 do 5" << std::endl;
                                break;
                        }
                    } while (!innerLoop);
                    break;
                case 3:
                    do {
                        std::ifstream inputFile(filename.c_str());
                        if (!inputFile.is_open()) {
                            std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
                            return;
                        }

                        inputFile >> size;
                        delete[] originalArray;
                        originalArray = new T[size];
                        for (int i = 0; i < size; ++i) {
                            inputFile >> originalArray[i];
                        }
                        inputFile.close();

                        T* dynamicArray = new T[size];
                        for (int i = 0; i < size; ++i) {
                            dynamicArray[i] = originalArray[i];
                        }


                        std::cout << "\n\nMENU - sortowanie Shella" << std::endl;
                        std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                        std::cout << "2. posortuj (Knuth)" << std::endl;
                        std::cout << "3. posortuj (Sedgewick)" << std::endl;
                        std::cout << "4. cofnij do menu glownego" << std::endl;
                        std::cout << "5. wybierz ponownie dane wejsciowe" << std::endl;
                        std::cout << "6. wyjscie z programu" << std::endl;
                        std::cout << "wybierz opcje (1-6): ";
                        std::cin >> innerChoice;

                        switch (innerChoice) {
                            case 1:
                                arrayPrinter.print(originalArray, size);
                                break;
                            case 2:
                                performSortingAndSaveResults(shellSorter, &ShellSort<T>::sortWithKnuth, dynamicArray, size, repetition, type, arrangement, filename);
                                break;
                            case 3:
                                performSortingAndSaveResults(shellSorter, &ShellSort<T>::sortWithSedgewick, dynamicArray, size, repetition, type, arrangement, filename);
                                break;
                            case 4:
                                innerLoop = true;
                                break;
                            case 5:
                                delete[] dynamicArray; // Zwolnienie pamięci
                                return;
                            case 6:
                                exitProgram = true;
                                return;
                            default:
                                std::cout << "nieprawidlowa opcja - wybierz opcje od 1 do 6" << std::endl;
                                break;
                        }
                    } while (!innerLoop);
                    break;
                case 4:
                    do {
                        std::ifstream inputFile(filename.c_str());
                        if (!inputFile.is_open()) {
                            std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
                            return;
                        }

                        inputFile >> size;
                        delete[] originalArray;
                        originalArray = new T[size];
                        for (int i = 0; i < size; ++i) {
                            inputFile >> originalArray[i];
                        }
                        inputFile.close();

                        T* dynamicArray = new T[size];
                        for (int i = 0; i < size; ++i) {
                            dynamicArray[i] = originalArray[i];
                        }


                        std::cout << "\n\nMENU - sortowanie szybkie" << std::endl;
                        std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                        std::cout << "2. posortuj (skrajny lewy pivot)" << std::endl;
                        std::cout << "3. posortuj (skrajny prawy pivot)" << std::endl;
                        std::cout << "4. posortuj (srodkowy pivot)" << std::endl;
                        std::cout << "5. posortuj (losowy pivot)" << std::endl;
                        std::cout << "6. cofnij do menu glownego" << std::endl;
                        std::cout << "7. wybierz ponownie dane wejsciowe" << std::endl;
                        std::cout << "8. wyjscie z programu" << std::endl;
                        std::cout << "wybierz opcje (1-8): ";
                        std::cin >> innerChoice;

                        switch (innerChoice) {
                            case 1:
                                arrayPrinter.print(originalArray, size);
                                break;
                            case 2:
                                // skrajny lewy
                                performSortingAndSaveResultsForQuickSort(1, quickSorter, &QuickSort<T>::sort, dynamicArray, size, repetition, type, arrangement, filename);
                                break;
                            case 3:
                                // skrajny prawy
                                performSortingAndSaveResultsForQuickSort(2, quickSorter, &QuickSort<T>::sort, dynamicArray, size, repetition, type, arrangement, filename);
                                break;
                            case 4:
                                // srodkowy 
                                performSortingAndSaveResultsForQuickSort(3, quickSorter, &QuickSort<T>::sort, dynamicArray, size, repetition, type, arrangement, filename);
                                break;
                            case 5:
                                // losowy
                                performSortingAndSaveResultsForQuickSort(4, quickSorter, &QuickSort<T>::sort, dynamicArray, size, repetition, type, arrangement, filename);
                                break;
                            case 6:
                                innerLoop = true;
                                break;
                            case 7:
                                delete[] dynamicArray; // Zwolnienie pamięci
                                return;
                            case 8:
                                exitProgram = true;
                                return;
                            default:
                                std::cout << "nieprawidlowa opcja - wybierz opcje od 1 do 8" << std::endl;
                                break;
                        }
                    } while (!innerLoop);
                    break;
                case 5:
                    return;
                case 6:
                    exitProgram = true;
                    return;
                default:
                    std::cout << "nieprawidlowa opcja - wybierz opcje od 1 do 6" << std::endl;
                    break;
            }
        } while (choice != 6);
    }

    
};

#endif