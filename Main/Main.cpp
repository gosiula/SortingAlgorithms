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

using namespace std;

int main() {
    int repetition = 100; // ilosc powtorzen sortowania
    bool exitProgram = false; // zmienna mowiaca o przerwaniu programu

    int size = 0; // wielkosc tablicy do sortowania
    int dataTypeChoice = 0; // zmienna informujaca o wyborze zmiennej

    string arrangement; // zmienna mowiaca jakie jest ulozenie liczb do sortowania

    Sorting<int> sortingInt; // obiekt klasy Sorting typu int do sortowania
    Sorting<float> sortingFloat; // obiekt klasy Sorting typu float do sortowania
    Sorting<double> sortingDouble; // obiekt klasy Sorting typu double do sortowania

    ResultSaver resultSaver; // obiekt klasy ResultSaver do zapisywania wynikow do pliku

    DataInput<int> dataInputInt; // obiekt klasy DataInput typu int do wczytywania danych wejsciowych do sortowania
    DataInput<float> dataInputFloat; // obiekt klasy DataInput typu float do wczytywania danych wejsciowych do sortowania
    DataInput<double> dataInputDouble; // obiekt klasy DataInput typu double do wczytywania danych wejsciowych do sortowania

    // procedura wyboru danych do posortowania i sortowania na podstawie typu danych wejsciowych 
    do {
        int* originalArrayInt = new int[size]; // tablica dla liczb typu int
        float* originalArrayFloat = new float[size]; // tablica dla liczb typu float
        double* originalArrayDouble = new double[size]; // tablica dla liczb typu double
 
        // wybor typu danych 
        do {
            cout << "wybierz typ danych (1 - int, 2 - float, 3 - double): ";

            // sprawdzanie czy wprowadzona wartosc jest liczba
            if (!(cin >> dataTypeChoice)) {
                cout << "Niepoprawny wybor - wprowadz ponownie\n"; // komunikat o zlym wyborze
                cin.clear(); // czyszczenie bledu w strumieniu wejscia
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // usuniecie niepoprawnej linii wejscia
                continue; // petla rozpoczyna sie od nowa
            }
            break;
        } while (true);

        // w zaleznosci od wyboru - wybor danych wejsciowych i sortowanie
        switch (dataTypeChoice) {
            case 1:
                dataInputInt.getElements(originalArrayInt, size, exitProgram, dataTypeChoice); // wybor danych wejsciowych
                if(exitProgram == true) return 0; // sprawdzenie czy uzytkownik nie chcial wyjsc z programu 
                sortingInt.setInputFilename(dataInputInt.getInputFilename()); // ustawienie nazwy pliku
                resultSaver.setOriginalFilename(dataInputInt.getInputFilename()); // ustawienie nazwy pliku
                arrangement = dataInputInt.getArrangement(); // ustawienie typu ulozenia liczb do sortowania
                sortingInt.performSorting(originalArrayInt, size, exitProgram, repetition, dataTypeChoice, arrangement); // sortowanie
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
                break;
        }

        // zwolnienie pamieci
        delete[] originalArrayInt;
        delete[] originalArrayFloat;
        delete[] originalArrayDouble;
    } while (!exitProgram);

    return 0;
}
