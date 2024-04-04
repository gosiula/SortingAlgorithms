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
#include "NumberGenerator/FileGenerator.cpp"

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
    string filename;
    DataInput<T> dataInput;
    ResultSaver resultSaver;
    int repetition; 
    T* originalArray; 
    int size; 
    int type;
    string arrangement;
    FileGenerator<T> fileGen;

public:
    void setInputFilename(const std::string& filename) {
        this->filename = filename;
    }

    std::string getInputFilename() const {
        return filename;
    }

// funkcja sortujaca i zapisujaca wyniki
template<typename SorterType, typename SortFunction>
void performSortingAndSaveResults(SorterType& sorter, SortFunction sortFunction, T* originalArray, int size, int repetition, int type, const string& arrangement, const string& filename) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    QueryPerformanceFrequency(&frequency);

    double totalTime = 0.0;

    // dla jednego powtorzenia
    if (repetition == 1) {
        // usuniecie zawartosci posortowanej tablicy
        T* dynamicArray = new T[size];
        for (int j = 0; j < size; ++j) {
            dynamicArray[j] = originalArray[j];
        }

        // sortowanie wraz z obliczeniem czasu
        QueryPerformanceCounter(&start);
        (sorter.*sortFunction)(dynamicArray, size);
        QueryPerformanceCounter(&end);

        totalTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart; // czas

        cout << "\n\ntablica zostala posortowana" << endl;
        arrayPrinter.print(dynamicArray, size); // wypisanie liczb po sortowaniu

        // sprawdzenie czy liczby zostaly poprawnie posortowane
        if (sortingChecker.isSorted(dynamicArray, size)) {
            cout << "liczby poprawnie posortowane" << endl;
        } else {
            cout << "liczby niepoprawnie posortowane" << endl;
        }

        cout << "czas sortowania: " << fixed << setprecision(6) << totalTime * 1000.0 << " ms" << endl;

        delete[] dynamicArray; // zwolnienie pamieci
    } else { // dla wiekszej ilosci powtorzen
        for(int i = 1; i <= repetition; ++i) {
            // jesli ponownie sortujemy to trzeba zmienic dane w pliku
            if(i > 1) {
                if(type == 1) {
                    FileGenerator<int> fileGen(filename);
                    fileGen.generateAndWriteToFile(size, type);
                }
                else if(type == 2) {
                    FileGenerator<float> fileGen(filename);
                    fileGen.generateAndWriteToFile(size, type);
                }
                else if(type == 3) {
                    FileGenerator<double> fileGen(filename);
                    fileGen.generateAndWriteToFile(size, type);
                }
            }

            // modyfikacja liczb w pliku
            if(arrangement == "liczby posortowane malejaco") {
                fileGen.sortDescending(filename);
            }
            else if(arrangement == "liczby posortowane rosnaco") {
                fileGen.sortAscendingAll(filename);
            }
            else if(arrangement == "liczby posortowane rosnaco w 66%") {
                fileGen.sortAscendingWithPercentage(66, filename);
            }
            else if(arrangement == "liczby posortowane rosnaco w 33%") {
                fileGen.sortAscendingWithPercentage(33, filename);
            }

            // czyszczenie zawartosci posortowanej tablicy
            T* dynamicArray = new T[size];
            // uzupelnianie tablicy
            for (int j = 0; j < size; ++j) {
                dynamicArray[j] = originalArray[j];
            }

            // sortowanie z obliczaniem czasu
            QueryPerformanceCounter(&start);
            (sorter.*sortFunction)(dynamicArray, size);
            QueryPerformanceCounter(&end);

            totalTime += static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart; // czas

            // sprawdzanie czy liczby zostaly poprawnie posortowane
            if (sortingChecker.isSorted(dynamicArray, size)) {
                cout << i << ". liczby poprawnie posortowane : ";
            } else {
                cout << i << ". liczby niepoprawnie posortowane";
            }

            cout << "czas sortowania: " << fixed << setprecision(6) << (totalTime / i) * 1000.0 << " ms" << endl;

            delete[] dynamicArray; // zwolnienie pamieci
        }
    }

    // zapisanie wynikow do pliku
    resultSaver.saveResults(type, size, repetition, totalTime / repetition * 1000.0, arrangement, filename);
}

// funkcja sortujaca i zapisujaca wyniki (dla quicksort)
template<typename SorterType, typename SortFunction>
void performSortingAndSaveResultsForQuickSort(int pivot, SorterType& sorter, SortFunction sortFunction, T* originalArray, int size, int repetition, int type, const string& arrangement, const string& filename) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    QueryPerformanceFrequency(&frequency);

    double totalTime = 0.0;

    if (repetition == 1) {
        T* dynamicArray = new T[size];
        for (int j = 0; j < size; ++j) {
            dynamicArray[j] = originalArray[j];
        }

        QueryPerformanceCounter(&start);
        (sorter.*sortFunction)(dynamicArray, size, pivot);
        QueryPerformanceCounter(&end);

        totalTime = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

        cout << "\n\ntablica zostala posortowana przez InsertionSort" << endl;
        arrayPrinter.print(dynamicArray, size);
        if (sortingChecker.isSorted(dynamicArray, size)) {
            cout << "liczby poprawnie posortowane" << endl;
        } else {
            cout << "liczby niepoprawnie posortowane" << endl;
        }

        cout << "czas sortowania: " << fixed << setprecision(6) << totalTime * 1000.0 << " ms" << endl;

        delete[] dynamicArray;
    } else {
        for(int i = 1; i <= repetition; ++i) {
            // jesli ponownie sortujemy to trzeba zmienic dane w pliku
            if(i > 1) {
                if(type == 1) {
                    FileGenerator<int> fileGen(filename);
                    fileGen.generateAndWriteToFile(size, type);
                }
                else if(type == 2) {
                    FileGenerator<float> fileGen(filename);
                    fileGen.generateAndWriteToFile(size, type);
                }
                else if(type == 3) {
                    FileGenerator<double> fileGen(filename);
                    fileGen.generateAndWriteToFile(size, type);
                }
            }

            // modyfikacja liczb w pliku
            if(arrangement == "liczby posortowane malejaco") {
                fileGen.sortDescending(filename);
            }
            else if(arrangement == "liczby posortowane rosnaco") {
                fileGen.sortAscendingAll(filename);
            }
            else if(arrangement == "liczby posortowane rosnaco w 66%") {
                fileGen.sortAscendingWithPercentage(66, filename);
            }
            else if(arrangement == "liczby posortowane rosnaco w 33%") {
                fileGen.sortAscendingWithPercentage(33, filename);
            }

            T* dynamicArray = new T[size];
            for (int j = 0; j < size; ++j) {
                dynamicArray[j] = originalArray[j];
            }

            QueryPerformanceCounter(&start);
            (sorter.*sortFunction)(dynamicArray, size, pivot);
            QueryPerformanceCounter(&end);

            totalTime += static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

            if (sortingChecker.isSorted(dynamicArray, size)) {
                cout << i << ". liczby poprawnie posortowane : ";
            } else {
                cout << i << ". liczby niepoprawnie posortowane";
            }

            cout << "czas sortowania: " << fixed << setprecision(6) << (totalTime / i) * 1000.0 << " ms" << endl;

            delete[] dynamicArray; 
        }
    }

    resultSaver.saveResults(type, size, repetition, totalTime / repetition * 1000.0, arrangement, filename);
}

    // funkcja do wywolania sortowania przez menu
    void performSorting(T* originalArray, int size, bool& exitProgram, int repetition, int type, const string& arrangement) {
        clock_t start, end;
        double elapsedTimeMillis;
        int choice;
        int innerChoice;
        bool innerLoop = false;
        double averageTime = 0.0;

        do {
            cout << "\n\nMENU GLOWNE" << endl;
            cout << "1. sortowanie przez wstawianie" << endl;
            cout << "2. sortowanie przez kopcowanie" << endl;
            cout << "3. sortowanie Shella" << endl;
            cout << "4. sortowanie szybkie" << endl;
            cout << "5. wczytaj ponownie dane" << endl;
            cout << "6. wyjscie z programu\n" << endl;
            cout << "wybierz opcje (1-6): ";

            // sprawdzanie czy wprowadzona wartosc jest liczba
            if (!(cin >> choice)) {
                cout << "niepoprawna liczba - wprowadz ponownie\n"; // komunikat o zlym wyborze
                cin.clear(); // czyszczenie bledu w strumieniu wejscia
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // usuniecie niepoprawnej linii wejscia
                continue; // petla rozpoczyna sie od nowa
            }
            cout << endl;

            innerLoop = false;

            switch (choice) {
                case 1:
                    do {
                        // otworzenie pliku
                        ifstream inputFile(this->filename.c_str());
                        if (!inputFile.is_open()) {
                            cout << "nie mozna otworzyc  " << this->filename << endl;
                            cout << this->filename << endl;
                            return;

                        }

                        inputFile >> size; // wczytanie liczby elementow
                        delete[] originalArray; // usuniecie
                        originalArray = new T[size]; // stworzenie nowej tablicy 

                        // wczytanie liczb z pliku
                        for (int i = 0; i < size; ++i) {
                            T value;
                            inputFile >> value;
                            originalArray[i] = value;
                        }
                        inputFile.close(); // zamkniecie pliku

                        // wczytanie liczb z oryginalnej tablicy to tablicy pomocniczej na ktorej bedziemy sortowac
                        T* dynamicArray = new T[size];
                        for (int i = 0; i < size; ++i) {
                            dynamicArray[i] = originalArray[i];
                        }

                        cout << "\n\nMENU - sortowanie przez wstawianie" << endl;
                        cout << "1. wypisz tablice przed sortowaniem" << endl;
                        cout << "2. posortuj" << endl;
                        cout << "3. cofnij do menu glownego" << endl;
                        cout << "4. wybierz ponownie dane wejsciowe" << endl;
                        cout << "5. wyjscie z programu" << endl;
                        cout << "wybierz opcje (1-5): ";

                        // sprawdzanie czy wprowadzona wartosc jest liczba
                        if (!(cin >> innerChoice)) {
                            cout << "niepoprawna liczba - wprowadz ponownie\n"; // komunikat o zlym wyborze
                            cin.clear(); // czyszczenie bledu w strumieniu wejscia
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Usuniecie niepoprawnej linii wejscia
                            continue; // petla rozpoczyna sie od nowa
                        }

                        switch (innerChoice) {
                            case 1:
                                arrayPrinter.print(originalArray, size); // wypisanie zawartosci tablicy przed sortowaniem
                                break;
                            case 2:
                                // posortowanie i zapisanie wynikow
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
                                cout << "nieprawidlowa opcja - wybierz opcje od 1 do 5" << endl;
                                break;
                        }
                    } while (!innerLoop);
                    break;
                case 2:
                    do {
                        ifstream inputFile(filename.c_str());
                        if (!inputFile.is_open()) {
                            cout << "nie mozna otworzyc pliku: " << filename << endl;
                            return;
                        }

                        inputFile >> size;
                        delete[] originalArray;
                        originalArray = new T[size];

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

                        cout << "\n\nMENU - sortowanie przez kopcowanie" << endl;
                        cout << "1. wypisz tablice przed sortowaniem" << endl;
                        cout << "2. posortuj" << endl;
                        cout << "3. cofnij do menu glownego" << endl;
                        cout << "4. wybierz ponownie dane wejsciowe" << endl;
                        cout << "5. wyjscie z programu" << endl;
                        cout << "wybierz opcje (1-5): ";

                        // sprawdzanie czy wprowadzona wartosc jest liczba
                        if (!(cin >> innerChoice)) {
                            cout << "niepoprawna liczba - wprowadz ponownie\n"; // komunikat o zlym wyborze
                            cin.clear(); // czyszczenie bledu w strumieniu wejscia
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // usuniecie niepoprawnej linii wejscia
                            continue; // petla rozpoczyna sie od nowa
                        }

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
                                delete[] dynamicArray;
                                return;
                            case 5:
                                exitProgram = true;
                                return;
                            default:
                                cout << "nieprawidlowa opcja - wybierz opcje od 1 do 5" << endl;
                                break;
                        }
                    } while (!innerLoop);
                    break;
                case 3:
                    do {
                        ifstream inputFile(filename.c_str());
                        if (!inputFile.is_open()) {
                            cout << "nie mozna otworzyc pliku: " << filename << endl;
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


                        cout << "\n\nMENU - sortowanie Shella" << endl;
                        cout << "1. wypisz tablice przed sortowaniem" << endl;
                        cout << "2. posortuj (Knuth)" << endl;
                        cout << "3. posortuj (Sedgewick)" << endl;
                        cout << "4. cofnij do menu glownego" << endl;
                        cout << "5. wybierz ponownie dane wejsciowe" << endl;
                        cout << "6. wyjscie z programu" << endl;
                        cout << "wybierz opcje (1-6): ";

                        // sprawdzanie czy wprowadzona wartosc jest liczba
                        if (!(cin >> innerChoice)) {
                            cout << "niepoprawna liczba - wprowadz ponownie\n"; // komunikat o zlym wyborze
                            cin.clear(); // czyszczenie bledu w strumieniu wejscia
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // usuniecie niepoprawnej linii wejscia
                            continue; // petla rozpoczyna się od nowa
                        }

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
                                delete[] dynamicArray;
                                return;
                            case 6:
                                exitProgram = true;
                                return;
                            default:
                                cout << "nieprawidlowa opcja - wybierz opcje od 1 do 6" << endl;
                                break;
                        }
                    } while (!innerLoop);
                    break;
                case 4:
                    do {
                        std::ifstream inputFile(filename.c_str());
                        if (!inputFile.is_open()) {
                            cout << "nie mozna otworzyc pliku: " << filename << endl;
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


                        cout << "\n\nMENU - sortowanie szybkie" << endl;
                        cout << "1. wypisz tablice przed sortowaniem" << endl;
                        cout << "2. posortuj (skrajny lewy pivot)" << endl;
                        cout << "3. posortuj (skrajny prawy pivot)" << endl;
                        cout << "4. posortuj (srodkowy pivot)" << endl;
                        cout << "5. posortuj (losowy pivot)" << endl;
                        cout << "6. cofnij do menu glownego" << endl;
                        cout << "7. wybierz ponownie dane wejsciowe" << endl;
                        cout << "8. wyjscie z programu" << endl;
                        cout << "wybierz opcje (1-8): ";

                        // sprawdzanie czy wprowadzona wartosc jest liczba
                        if (!(cin >> innerChoice)) {
                            cout << "niepoprawna liczba - wprowadz ponownie\n"; // komunikat o zlym wyborze
                            cin.clear(); // czyszczenie bledu w strumieniu wejscia
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // usuniecie niepoprawnej linii wejscia
                            continue; // petla rozpoczyna sie od nowa
                        }

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
                                delete[] dynamicArray;
                                return;
                            case 8:
                                exitProgram = true;
                                return;
                            default:
                                cout << "nieprawidlowa opcja - wybierz opcje od 1 do 8" << endl;
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
                    cout << "nieprawidlowa opcja - wybierz opcje od 1 do 6" << endl;
                    break;
            }
        } while (choice != 6);
    }
};

#endif