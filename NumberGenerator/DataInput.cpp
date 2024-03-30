#ifndef DATA_INPUT_CPP
#define DATA_INPUT_CPP

#include <iostream>
#include <fstream>
#include <string>
#include "FileGenerator.cpp"

template<typename T>
class DataInput {
private:
    std::string filename;

public:
    std::string getInputFilename() const {
        return filename;
    }

    void setInputFilename(const std::string& filename) {
        this->filename = filename;
    }
    
    void getElements(T*& originalArray, int& size, bool& exitProgram, int type) {
        FileGenerator<T> fileGen;

        int choice;
        int innerChoice;

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
                    std::cout << "Podaj ilosc elementow: ";
                    std::cin >> size;

                    originalArray = new T[size];

                    std::cout << "Podaj elementy tablicy:" << std::endl;
                    for (int i = 0; i < size; ++i) {
                        std::cin >> originalArray[i];
                    }

                    return;
                }
                case 2: {
                    std::string inputFilename;
                    std::cout << "Podaj nazwe pliku z danymi: ";
                    std::cin >> inputFilename;

                    std::ifstream inputFile(inputFilename.c_str());
                    if (!inputFile.is_open()) {
                        std::cerr << "Blad otwierania pliku" << std::endl;
                        return;
                    }

                    inputFile >> size;
                    originalArray = new T[size];

                    for (int i = 0; i < size; ++i) {
                        inputFile >> originalArray[i];
                    }

                    inputFile.close();
                    setInputFilename(inputFilename); // Ustawienie nazwy pliku
                    return;
                }


                case 3: {
                    int count;
                    std::string outputFilename;

                    std::cout << "Podaj ilosc liczb: ";
                    std::cin >> count;
                    std::cout << "Podaj nazwe pliku do zapisu: ";
                    std::cin >> outputFilename;

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

                    filename = outputFilename; // Ustawienie nazwy pliku

                    return;
                }
                case 4: {
                    exitProgram = true;
                    return;
                }
                default: {
                    std::cout << "Nieprawidlowy wybor opcji" << std::endl;
                    break;
                }
            }
        } while (choice != 4);
    }
};

#endif
