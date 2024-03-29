#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "FileGenerator.cpp"
#include "Sort/InsertionSort.cpp"
#include "Sort/HeapSort.cpp"
#include "Sort/ShellSort.cpp"
#include "Sort/QuickSort.cpp"
#include "Options/ArrayPrinter.cpp"
#include "Options/SortingChecker.cpp"

template<typename T>
void getElements(T*& originalArray, int& size) {
    delete[] originalArray; // Zwolnienie pamięci, jeśli tablica już istnieje

    originalArray = new T[size]; // Zaalokowanie pamięci na nową tablicę

    std::cout << "podaj elementy tablicy:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cin >> originalArray[i];
    }
}

template<typename T>
void performSorting(T* originalArray, int size, bool& exitProgram) {
    ArrayPrinter<T> arrayPrinter;
    SortingChecker<T> sortingChecker;

    InsertionSort<T> insertionSorter;
    HeapSort<T> heapSorter;
    ShellSort<T> shellSorter;
    QuickSort<T> quickSorter;

    clock_t start, end; // Zmienne do pomiaru czasu
    double elapsedTimeMillis; // Zmienna do przechowywania czasu w milisekundach

    int choice;
    int innerChoice;
    bool innerLoop = false;
    do {
        std::cout << "\n\nMENU GLOWNE" << std::endl;
        std::cout << "1. sortowanie przez wstawianie" << std::endl;
        std::cout << "2. sortowanie przez kopcowanie" << std::endl;
        std::cout << "3. sortowanie Shella" << std::endl;
        std::cout << "4. sortowanie szybkie" << std::endl;
        std::cout << "5. wyjscie z programu\n" << std::endl;
        std::cout << "wybierz opcje (1-5): ";
        std::cin >> choice;
        std::cout << std::endl;

        innerLoop = false;

        switch (choice) {
            case 1:
                do {
                    // Tworzymy nową tablicę dla sortowania
                    T* dynamicArray = new T[size];
                    for (int i = 0; i < size; ++i) {
                        dynamicArray[i] = originalArray[i];
                    }

                    std::cout << "\n\nMENU - sortowanie przez wstawianie" << std::endl;
                    std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                    std::cout << "2. wypisz tablice po sortowaniu" << std::endl;
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
                            start = clock(); // Początek pomiaru czasu
                            insertionSorter.sort(dynamicArray, size);
                            end = clock(); // Koniec pomiaru czasu

                            std::cout << "\n\ntablica zostala posortowana przez InsertionSort" << std::endl;
                            arrayPrinter.print(dynamicArray, size);

                            if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                            else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                            elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC; // Obliczenie czasu trwania sortowania w milisekundach
                            std::cout << "Czas sortowania: " << elapsedTimeMillis << " ms" << std::endl; // Wypisanie czasu w milisekundach
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
            case 2:
                do {
                    // Tworzymy nową tablicę dla sortowania
                    T* dynamicArray = new T[size];
                    for (int i = 0; i < size; ++i) {
                        dynamicArray[i] = originalArray[i];
                    }

                    std::cout << "\n\nMENU - sortowanie przez kopcowanie" << std::endl;
                    std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                    std::cout << "2. wypisz tablice po sortowaniu" << std::endl;
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
                            heapSorter.sort(dynamicArray, size);
                            std::cout << "\n\ntablica zostala posortowana przez HeapSort" << std::endl;
                            arrayPrinter.print(dynamicArray, size);
                            if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                            else std::cout << "liczby niepoprawnie posortowane" << std::endl;
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
                    // Tworzymy nową tablicę dla sortowania
                    T* dynamicArray = new T[size];
                    for (int i = 0; i < size; ++i) {
                        dynamicArray[i] = originalArray[i];
                    }

                    std::cout << "\n\nMENU - sortowanie Shella" << std::endl;
                    std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                    std::cout << "2. wypisz tablice po sortowaniu (Knuth)" << std::endl;
                    std::cout << "3. wypisz tablice po sortowaniu (Sedgewick)" << std::endl;
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
                            shellSorter.sortWithKnuth(dynamicArray, size);
                            std::cout << "\n\ntablica zostala posortowana przez ShellSort (Knuth)" << std::endl;
                            arrayPrinter.print(dynamicArray, size);
                            if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                            else std::cout << "liczby niepoprawnie posortowane" << std::endl;
                            break;
                        case 3:
                            shellSorter.sortWithSedgewick(dynamicArray, size);
                            std::cout << "\n\ntablica zostala posortowana przez ShellSort (Sedgewick)" << std::endl;
                            arrayPrinter.print(dynamicArray, size);
                            if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                            else std::cout << "liczby niepoprawnie posortowane" << std::endl;
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
                    // Tworzymy nową tablicę dla sortowania
                    T* dynamicArray = new T[size];
                    for (int i = 0; i < size; ++i) {
                        dynamicArray[i] = originalArray[i];
                    }

                    std::cout << "\n\nMENU - sortowanie szybkie" << std::endl;
                    std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                    std::cout << "2. sortowanie szybkie (skrajny lewy pivot)" << std::endl;
                    std::cout << "3. sortowanie szybkie (skrajny prawy pivot)" << std::endl;
                    std::cout << "4. sortowanie szybkie (srodkowy pivot)" << std::endl;
                    std::cout << "5. sortowanie szybkie (losowy pivot)" << std::endl;
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
                            quickSorter.sort(dynamicArray, size, 1); // Skrajny lewy pivot
                            std::cout << "\n\ntablica zostala posortowana przez QuickSort (skrajny lewy pivot)" << std::endl;
                            arrayPrinter.print(dynamicArray, size);
                            if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                            else std::cout << "liczby niepoprawnie posortowane" << std::endl;
                            break;
                        case 3:
                            quickSorter.sort(dynamicArray, size, 2); // Skrajny prawy pivot
                            std::cout << "\n\ntablica zostala posortowana przez QuickSort (skrajny prawy pivot)" << std::endl;
                            arrayPrinter.print(dynamicArray, size);
                            if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                            else std::cout << "liczby niepoprawnie posortowane" << std::endl;
                            break;
                        case 4:
                            quickSorter.sort(dynamicArray, size, 3); // Środkowy pivot
                            std::cout << "\n\ntablica zostala posortowana przez QuickSort (srodkowy pivot)" << std::endl;
                            arrayPrinter.print(dynamicArray, size);
                            if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                            else std::cout << "liczby niepoprawnie posortowane" << std::endl;
                            break;
                        case 5:
                            quickSorter.sort(dynamicArray, size, 4); // Losowy pivot
                            std::cout << "\n\nTablica zostala posortowana przez QuickSort (losowy pivot)" << std::endl;
                            arrayPrinter.print(dynamicArray, size);
                            if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                            else std::cout << "liczby niepoprawnie posortowane" << std::endl;
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
                exitProgram = true;
                return;
            default:
                std::cout << "nieprawidlowa opcja - wybierz opcje od 1 do 5." << std::endl;
                break;
        }
    } while (choice != 5);
}

int main() {
    bool exitProgram = false;

    int size = 0;
    int dataTypeChoice = 0;

    do {
        std::cout << "podaj rozmiar tablicy: ";
        std::cin >> size;

        int* originalArrayInt = new int[size];
        float* originalArrayFloat = new float[size];
        double* originalArrayDouble = new double[size];

        std::cout << "wybierz typ danych (1 - int, 2 - float, 3 - double): ";
        std::cin >> dataTypeChoice;

        switch (dataTypeChoice) {
            case 1:
                getElements(originalArrayInt, size);
                performSorting(originalArrayInt, size, exitProgram);
                break;
            case 2:
                getElements(originalArrayFloat, size);
                performSorting(originalArrayFloat, size, exitProgram);
                break;
            case 3:
                getElements(originalArrayDouble, size);
                performSorting(originalArrayDouble, size, exitProgram);
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
