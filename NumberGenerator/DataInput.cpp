#ifndef DATA_INPUT_CPP
#define DATA_INPUT_CPP

#include <iostream>
#include <fstream>
#include <string>
#include "FileGenerator.cpp"

using namespace std;

template<typename T>
class DataInput {
private:
    string filename; // nazwa pliku
    string arrangement; // typ ulozenia danych 

public:
    // gettery i settery
    string getInputFilename() const {
        return this->filename;
    }

    void setInputFilename(const string& filename) {
        this->filename = filename;
    }

    string getArrangement() const {
        return arrangement;
    }   
    
    // funkcja do wyboru danych wejsciowych
    void getElements(T*& originalArray, int& size, bool& exitProgram, int type) {
        FileGenerator<T> fileGen; // obiekt typu FileGenerator ktory uzupelnia plik z danymi

        int choice; // wybor w menu
        int innerChoice; // wybor w menu wewnetrznym

        do {
            cout << "\nMENU WYBORU DANYCH" << endl;
            cout << "1. Dane z gotowego pliku" << endl;
            cout << "2. Dane z nowego pliku" << endl;
            cout << "3. Wyjscie z programu\n" << endl;
            cout << "Wybierz opcje (1-3): ";

            // sprawdzanie czy wprowadzona wartosc jest liczba
            if (!(cin >> choice)) {
                cout << "niepoprawna liczba - wprowadz ponownie\n"; // komunikat o zlym wyborze
                cin.clear(); // czyszczenie bledu w strumieniu wejscia
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // usuniecie niepoprawnej linii wejscia
                continue; // petla rozpoczyna sie od nowa
            }
            
            switch (choice) {
                case 1: {
                    string inputFilename; // nazwa pliku
                    cout << "podaj nazwe pliku z danymi: ";
                    cin >> inputFilename; // wczytanie nazwy pliku

                    // komunikat jesli plik nie zostal znaleziony
                    ifstream inputFile(inputFilename.c_str());
                    if (!inputFile.is_open()) {
                        cout << "blad otwierania pliku" << endl;
                        return;
                    }

                    inputFile >> size; // wczytanie wielkosci tablicy z pliku
                    originalArray = new T[size]; // stworzenie tablicy o danej wielkosci

                    // wczytanie tablicy z pliku
                    for (int i = 0; i < size; ++i) {
                        inputFile >> originalArray[i];
                    }

                    inputFile.close(); // zamkniecie pliku
                    setInputFilename(inputFilename); // ustawienie nazwy pliku
                    return;
                }

                case 2: {
                    int count; // wielkosc tablicy
                    string outputFilename; // nazwa pliku
                    
                    // wczytanie ilosci liczb 
                    do {
                        cout << "podaj ilosc liczb: ";

                        // sprawdzanie czy wprowadzona wartosc jest liczba
                        if (!(cin >> count) || count <= 0) {
                            cout << "niepoprawna liczba - wprowadz ponownie\n"; // komunikat o zlym wyborze
                            cin.clear(); // czyszczenie bledu w strumieniu wejscia
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // usuniecie niepoprawnej linii wejscia
                            continue; // petla rozpoczyna sie od nowa
                        }
                        break;
                    } while (true);

                    cout << "podaj nazwe pliku do zapisu: ";
                    cin >> outputFilename; // wczytanie nazwy pliku

                    // w zaleznosci od wczytanego typu w main losujemy i zapisujemy dana ilosc liczb do pliku
                    if (type == 1) {
                        FileGenerator<int> fileGen(outputFilename);
                        fileGen.generateAndWriteToFile(count, type);
                    }
                    else if (type == 2) {
                        FileGenerator<float> fileGen(outputFilename);
                        fileGen.generateAndWriteToFile(count, type);
                    }
                    else if (type == 3) {
                        FileGenerator<double> fileGen(outputFilename);
                        fileGen.generateAndWriteToFile(count, type);
                    }

                    setInputFilename(outputFilename); // aktualizacja nazwy pliku w obiekcie DataInput

                    // otwarcie pliku do odczytu
                    ifstream inputFile(outputFilename.c_str());
                    if (!inputFile.is_open()) {
                        cout << "nie mozna otworzyc pliku: " << outputFilename << endl;
                        return;
                    }
                    
                    inputFile >> size; // wczytanie wielkosci z pliku
                    originalArray = new T[size]; // stworzenie tablicy o danej wielkosci

                    // wczytanie tablicy z pliku
                    for (int i = 0; i < size; ++i) {
                        inputFile >> originalArray[i];
                    }

                    inputFile.close(); // zamkniecie pliku

                    // menu modyfikacji danych w pliku
                    do {
                        cout << "\nMENU MODYFIKACJI DANYCH W PLIKU" << endl;
                        cout << "1. Losowe ulozenie (brak zmian)" << endl;
                        cout << "2. Posortowane malejaco" << endl;
                        cout << "3. Posortowane rosnaco" << endl;
                        cout << "4. Posortowane rosnaco w 66%" << endl;
                        cout << "5. Posortowane rosnaco w 33%" << endl;
                        cout << "Wybierz opcje (1-5): ";

                        // sprawdzanie czy wprowadzona wartosc jest liczba
                        if (!(cin >> innerChoice)) {
                            cout << "niepoprawna liczba - wprowadz ponownie\n"; // komunikat o zlym wyborze 
                            cin.clear(); // czyszczenie bledu w strumieniu wejscia
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // usuniecie niepoprawnej linii wejscia
                            continue; // petla rozpoczyna sie od nowa
                        }

                        switch (innerChoice) {
                            case 1: // brak zmian
                                arrangement = "liczby losowe";
                                return;
                            case 2: // posortowane malejaco
                                fileGen.sortDescending(outputFilename);
                                arrangement = "liczby posortowane malejaco";
                                return;
                            case 3: // posortowane rosnaco
                                fileGen.sortAscendingAll(outputFilename);
                                arrangement = "liczby posortowane rosnaco";
                                return;
                            case 4: // posortowane rosnaco w 66%
                                fileGen.sortAscendingWithPercentage(66, outputFilename);
                                arrangement = "liczby posortowane rosnaco w 66%";
                                return;
                            case 5: // posortowane rosnaco w 33%
                                fileGen.sortAscendingWithPercentage(33, outputFilename);
                                arrangement = "liczby posortowane rosnaco w 33%";
                                return;
                            default:
                                cout << "nieprawidlowy wybor opcji modyfikacji" << endl;
                                break;
                        }
                    } while (true);

                    cout << "dane zostaly pomyslnie zmodyfikowane" << endl;

                    filename = outputFilename; // ustawienie nazwy pliku

                    return;
                }
                case 3: { // wyjscie z programu
                    exitProgram = true;
                    return;
                }
                default: {
                    cout << "nieprawidlowy wybor opcji" << endl;
                    break;
                }
            }
        } while (choice != 3);
    }
};

#endif
