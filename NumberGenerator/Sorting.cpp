#ifndef SORTING_CPP
#define SORTING_CPP

#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "Sort/InsertionSort.cpp"
#include "Sort/HeapSort.cpp"
#include "Sort/ShellSort.cpp"
#include "Sort/QuickSort.cpp"
#include "Options/ArrayPrinter.cpp"
#include "Options/SortingChecker.cpp"

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

public:
    void setInputFilename(const std::string& filename) {
        this->filename = filename;
    }

    std::string getInputFilename() const {
        return filename;
    }

    void performSorting(T* originalArray, int size, bool& exitProgram) {
        clock_t start, end;
        double elapsedTimeMillis;
        int choice;
        int innerChoice;
        bool innerLoop = false;

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
                                start = clock();
                                insertionSorter.sort(dynamicArray, size);
                                end = clock();

                                std::cout << "\n\ntablica zostala posortowana przez InsertionSort" << std::endl;
                                arrayPrinter.print(dynamicArray, size);
                                if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                                else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                                elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC;
                                std::cout << "czas sortowania: " << elapsedTimeMillis << " ms" << std::endl;
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
                                start = clock(); // Początek pomiaru czasu
                                heapSorter.sort(dynamicArray, size);
                                end = clock(); // Koniec pomiaru czasu

                                std::cout << "\n\ntablica zostala posortowana przez HeapSort" << std::endl;
                                arrayPrinter.print(dynamicArray, size);
                                if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                                else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                                elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC; // Obliczenie czasu trwania sortowania w milisekundach
                                std::cout << "czas sortowania: " << elapsedTimeMillis << " ms" << std::endl; // Wypisanie czasu w milisekundach
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
                                start = clock(); // Początek pomiaru czasu
                                shellSorter.sortWithKnuth(dynamicArray, size);
                                end = clock(); // Koniec pomiaru czasu
                                
                                std::cout << "\n\ntablica zostala posortowana przez ShellSort (Knuth)" << std::endl;
                                arrayPrinter.print(dynamicArray, size);
                                if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                                else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                                elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC; // Obliczenie czasu trwania sortowania w milisekundach
                                std::cout << "czas sortowania: " << elapsedTimeMillis << " ms" << std::endl; // Wypisanie czasu w milisekundach
                                break;
                            case 3:
                                start = clock(); // Początek pomiaru czasu
                                shellSorter.sortWithSedgewick(dynamicArray, size);
                                end = clock(); // Koniec pomiaru czasu
                                
                                std::cout << "\n\ntablica zostala posortowana przez ShellSort (Sedgewick)" << std::endl;
                                arrayPrinter.print(dynamicArray, size);
                                if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                                else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                                elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC; // Obliczenie czasu trwania sortowania w milisekundach
                                std::cout << "czas sortowania: " << elapsedTimeMillis << " ms" << std::endl; // Wypisanie czasu w milisekundach
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
                                start = clock(); // Początek pomiaru czasu
                                quickSorter.sort(dynamicArray, size, 1); // Skrajny lewy pivot
                                end = clock(); // Koniec pomiaru czasu
                                
                                std::cout << "\n\ntablica zostala posortowana przez QuickSort (skrajny lewy pivot)" << std::endl;
                                arrayPrinter.print(dynamicArray, size);
                                if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                                else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                                elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC; // Obliczenie czasu trwania sortowania w milisekundach
                                std::cout << "czas sortowania: " << elapsedTimeMillis << " ms" << std::endl; // Wypisanie czasu w milisekundach
                                break;
                            case 3:
                                start = clock(); // Początek pomiaru czasu
                                quickSorter.sort(dynamicArray, size, 2); // Skrajny prawy pivot
                                end = clock(); // Koniec pomiaru czasu
                                
                                std::cout << "\n\ntablica zostala posortowana przez QuickSort (skrajny prawy pivot)" << std::endl;
                                arrayPrinter.print(dynamicArray, size);
                                if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                                else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                                elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC; // Obliczenie czasu trwania sortowania w milisekundach
                                std::cout << "czas sortowania: " << elapsedTimeMillis << " ms" << std::endl; // Wypisanie czasu w milisekundach
                                break;
                            case 4:
                                start = clock(); // Początek pomiaru czasu
                                quickSorter.sort(dynamicArray, size, 3); // Środkowy pivot
                                end = clock(); // Koniec pomiaru czasu
                                
                                std::cout << "\n\ntablica zostala posortowana przez QuickSort (srodkowy pivot)" << std::endl;
                                arrayPrinter.print(dynamicArray, size);
                                if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                                else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                                elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC; // Obliczenie czasu trwania sortowania w milisekundach
                                std::cout << "czas sortowania: " << elapsedTimeMillis << " ms" << std::endl; // Wypisanie czasu w milisekundach
                                break;
                            case 5:
                                start = clock(); // Początek pomiaru czasu
                                quickSorter.sort(dynamicArray, size, 4); // Losowy pivot
                                end = clock(); // Koniec pomiaru czasu
                                
                                std::cout << "\n\nTablica zostala posortowana przez QuickSort (losowy pivot)" << std::endl;
                                arrayPrinter.print(dynamicArray, size);
                                if(sortingChecker.isSorted(dynamicArray, size) == true) std::cout << "liczby poprawnie posortowane" << std::endl;
                                else std::cout << "liczby niepoprawnie posortowane" << std::endl;

                                elapsedTimeMillis = (end - start) * 1000.0 / CLOCKS_PER_SEC; // Obliczenie czasu trwania sortowania w milisekundach
                                std::cout << "czas sortowania: " << elapsedTimeMillis << " ms" << std::endl; // Wypisanie czasu w milisekundach
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