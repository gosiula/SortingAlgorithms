#include <iostream>
#include <fstream>
#include <string>

template<typename T>
class DataInput {
private:
    T* originalArray;
    int size;
    bool exitProgram;

public:
    void getElements(T*& originalArray, int& size, bool& exitProgram) {
        delete[] originalArray; // Zwolnienie pamięci, jeśli tablica już istnieje

        int choice;

        do {
            std::cout << "\nMENU WYBORU DANYCH" << std::endl;
            std::cout << "1. Dane wpisywane recznie" << std::endl;
            std::cout << "2. Dane z gotowego pliku" << std::endl;
            std::cout << "3. Dane z nowego pliku" << std::endl;
            std::cout << "4. Wyjscie z programu\n" << std::endl;
            std::cout << "Wybierz opcje (1-4): ";
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::cout << "podaj ilosc elementow: ";
                    std::cin >> size;

                    originalArray = new T[size];

                    std::cout << "podaj elementy tablicy:" << std::endl;
                    for (int i = 0; i < size; ++i) {
                        std::cin >> originalArray[i];
                    }

                    return;
                }
                case 2: {
                    /*
                    std::string filename;
                    std::cout << "podaj nazwe pliku z danymi: ";
                    std::cin >> filename;

                    FileGenerator<T> fileGen(filename);

                    // Odczytaj dane z pliku
                    std::ifstream inputFile(filename.c_str()); // For input file
                    if (!inputFile.is_open()) {
                        std::cerr << "Blad otwierania pliku." << std::endl;
                        return;
                    }

                    inputFile >> size;
                    originalArray = new T[size];

                    for (int i = 0; i < size; ++i) {
                        inputFile >> originalArray[i];
                    }

                    inputFile.close();
                    */
                    return;
                }
                case 3: {
                    /*
                    int count;
                    std::string outputFilename;

                    std::cout << "podaj ilosc liczb: ";
                    std::cin >> count;
                    std::cout << "podaj nazwe pliku do zapisu: ";
                    std::cin >> outputFilename;

                    FileGenerator<T> fileGen(outputFilename);
                    fileGen.generateAndWriteToFile(count);

                    // Wczytaj dane z nowego pliku
                    std::ifstream inputFile(outputFilename.c_str()); // For input file
                    if (!inputFile.is_open()) {
                        std::cerr << "Blad otwierania pliku." << std::endl;
                        return;
                    }

                    inputFile >> size;
                    originalArray = new T[size];

                    for (int i = 0; i < size; ++i) {
                        inputFile >> originalArray[i];
                    }

                    inputFile.close();
                    */
                    return;
                }
                case 4: {
                    exitProgram = true;
                    return;
                }
                default: {
                    std::cout << "nieprawidlowy wybor opcji" << std::endl;
                    break;
                }
            }
        } while (choice != 4);
    }
};