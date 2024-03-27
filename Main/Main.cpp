#include <iostream>
#include "Sort/InsertionSort.h"
#include "Sort/HeapSort.h"
#include "Sort/ShellSort.h"
#include "Sort/QuickSort.h"
#include "Options/ArrayPrinter.h"

int main() {
    const int size = 5;
    int originalArray[size] = {10, 5, 7, 3, 8};

    InsertionSort insertionSorter;
    HeapSort heapSorter;
    ShellSort shellSorter;
    QuickSort quickSorter;

    int choice;
    int innerChoice; // Dodane
    bool innerLoop = false; // Dodane
    do {
        std::cout << "\n\nMENU" << std::endl;
        std::cout << "1. sortowanie przez wstawianie" << std::endl;
        std::cout << "2. sortowanie przez kopcowanie" << std::endl;
        std::cout << "3. sortowanie Shella" << std::endl;
        std::cout << "4. sortowanie szybkie" << std::endl;
        std::cout << "5. wyjscie z programu\n" << std::endl;
        std::cout << "Wybierz opcje (1-5): ";
        std::cin >> choice;
        std::cout << std::endl;

        innerLoop = false;

        switch (choice) {
            case 1:
                do {
                    // Tworzymy nową tablicę dla sortowania
                    int dynamicArray[size];
                    for (int i = 0; i < size; ++i) {
                        dynamicArray[i] = originalArray[i];
                    }

                    std::cout << "\n\nMENU - sortowanie przez wstawianie" << std::endl;
                    std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                    std::cout << "2. wypisz tablice po sortowaniu" << std::endl;
                    std::cout << "3. cofnij do menu glownego" << std::endl;
                    std::cout << "4. wyjscie z programu\n" << std::endl;
                    std::cout << "Wybierz opcje (1-4): ";
                    std::cin >> innerChoice;

                    switch (innerChoice) {
                        case 1:
                            ArrayPrinter::print(originalArray, size);
                            break;
                        case 2:
                            insertionSorter.sort(dynamicArray, size);
                            std::cout << "\n\nTablica zostala posortowana przez InsertionSort." << std::endl;
                            ArrayPrinter::print(dynamicArray, size);
                            break;
                        case 3:
                            innerLoop = true;
                            break;
                        case 4:
                            return 0;
                        default:
                            std::cout << "Nieprawidlowa opcja. Wybierz opcje od 1 do 4." << std::endl;
                            break;
                    }
                } while (!innerLoop);
                break;
            case 2:
                do {
                    // Tworzymy nową tablicę dla sortowania przez kopcowanie
                    int heapArray[size];
                    for (int i = 0; i < size; ++i) {
                        heapArray[i] = originalArray[i];
                    }

                    std::cout << "\n\nMENU - sortowanie przez kopcowanie" << std::endl;
                    std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                    std::cout << "2. wypisz tablice po sortowaniu" << std::endl;
                    std::cout << "3. cofnij do menu glownego" << std::endl;
                    std::cout << "4. wyjscie z programu\n" << std::endl;
                    std::cout << "Wybierz opcje (1-4): ";
                    std::cin >> innerChoice;

                    switch (innerChoice) {
                        case 1:
                            ArrayPrinter::print(originalArray, size);
                            break;
                        case 2:
                            heapSorter.sort(heapArray, size);
                            std::cout << "\n\nTablica zostala posortowana przez HeapSort." << std::endl;
                            ArrayPrinter::print(heapArray, size);
                            break;
                        case 3:
                            innerLoop = true;
                            break;
                        case 4:
                            return 0;
                        default:
                            std::cout << "Nieprawidlowa opcja. Wybierz opcje od 1 do 4." << std::endl;
                            break;
                    }
                } while (!innerLoop);
                break;
            case 3:
                do {
                    // Tworzymy nową tablicę dla sortowania
                    int shellArray[size];
                    for (int i = 0; i < size; ++i) {
                        shellArray[i] = originalArray[i];
                    }

                    std::cout << "\n\nMENU - sortowanie Shella" << std::endl;
                    std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                    std::cout << "2. wypisz tablice po sortowaniu (Knuth)" << std::endl;
                    std::cout << "3. wypisz tablice po sortowaniu (Sedgewick)" << std::endl;
                    std::cout << "4. cofnij do menu glownego" << std::endl;
                    std::cout << "5. wyjscie z programu\n" << std::endl;
                    std::cout << "Wybierz opcje (1-5): ";
                    std::cin >> innerChoice;

                    switch (innerChoice) {
                        case 1:
                            ArrayPrinter::print(originalArray, size);
                            break;
                        case 2:
                            shellSorter.sortWithKnuth(shellArray, size);
                            std::cout << "\n\nTablica zostala posortowana przez ShellSort (Knuth)." << std::endl;
                            ArrayPrinter::print(shellArray, size);
                            break;
                        case 3:
                            shellSorter.sortWithSedgewick(shellArray, size);
                            std::cout << "\n\nTablica zostala posortowana przez ShellSort (Sedgewick)." << std::endl;
                            ArrayPrinter::print(shellArray, size);
                            break;
                        case 4:
                            innerLoop = true;
                            break;
                        case 5:
                            return 0;
                        default:
                            std::cout << "Nieprawidlowa opcja. Wybierz opcje od 1 do 5." << std::endl;
                            break;
                    }
                } while (!innerLoop);
                break;
            case 4:
                do {
                    // Tworzymy nową tablicę dla sortowania
                    int quickArray[size];
                    for (int i = 0; i < size; ++i) {
                        quickArray[i] = originalArray[i];
                    }

                    std::cout << "\n\nMENU - sortowanie szybkie" << std::endl;
                    std::cout << "1. wypisz tablice przed sortowaniem" << std::endl;
                    std::cout << "2. sortowanie szybkie (skrajny lewy pivot)" << std::endl;
                    std::cout << "3. sortowanie szybkie (skrajny prawy pivot)" << std::endl;
                    std::cout << "4. sortowanie szybkie (srodkowy pivot)" << std::endl;
                    std::cout << "5. sortowanie szybkie (losowy pivot)" << std::endl;
                    std::cout << "6. cofnij do menu glownego" << std::endl;
                    std::cout << "7. wyjście z programu\n" << std::endl;
                    std::cout << "Wybierz opcje (1-7): ";
                    std::cin >> innerChoice;

                    switch (innerChoice) {
                        case 1:
                            ArrayPrinter::print(originalArray, size);
                            break;
                        case 2:
                            quickSorter.sort(quickArray, size, 1); // Skrajny lewy pivot
                            std::cout << "\n\nTablica zostala posortowana przez QuickSort (skrajny lewy pivot)." << std::endl;
                            ArrayPrinter::print(quickArray, size);
                            break;
                        case 3:
                            quickSorter.sort(quickArray, size, 2); // Skrajny prawy pivot
                            std::cout << "\n\nTablica zostala posortowana przez QuickSort (skrajny prawy pivot)." << std::endl;
                            ArrayPrinter::print(quickArray, size);
                            break;
                        case 4:
                            quickSorter.sort(quickArray, size, 3); // Środkowy pivot
                            std::cout << "\n\nTablica zostala posortowana przez QuickSort (srodkowy pivot)." << std::endl;
                            ArrayPrinter::print(quickArray, size);
                            break;
                        case 5:
                            quickSorter.sort(quickArray, size, 4); // Losowy pivot
                            std::cout << "\n\nTablica zostala posortowana przez QuickSort (losowy pivot)." << std::endl;
                            ArrayPrinter::print(quickArray, size);
                            break;
                        case 6:
                            innerLoop = true;
                            break;
                        case 7:
                            return 0;
                        default:
                            std::cout << "Nieprawidlowa opcja. Wybierz opcje od 1 do 7." << std::endl;
                            break;
                    }
                } while (!innerLoop);
                break;
            case 5:
                return 0;
            default:
                std::cout << "Nieprawidlowa opcja. Wybierz opcje od 1 do 5." << std::endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
