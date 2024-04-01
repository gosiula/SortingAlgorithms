#include <iostream>
#include <fstream>
#include <string>

#ifndef RESULT_SAVER_CPP
#define RESULT_SAVER_CPP

using namespace std;

class ResultSaver {
private:
    string originalFilename;

public:
    ResultSaver() = default;

    ResultSaver(const string& originalFilename) : originalFilename(originalFilename) {}

    void setOriginalFilename(const string& filename) {
        originalFilename = filename;
    }

    // funkcja ktora zapisuje wyniki do nowego pliku
    void saveResults(int type, int size, int repetition, double averageTime, const string& arrangement, const string& filename) {      
        // tworzenie nazwy pliku wynikowego z oryginalna nazwa pliku
        string result = "wyniki_";
        string resultFilename = result + filename;

        ofstream outputFile(resultFilename.c_str()); // otwarcie pliku 

        if (!outputFile.is_open()) {
            cout << "Nie można otworzyć pliku: " << resultFilename << endl;
            return;
        }

        string numberType;
        if (type == 1) {
            numberType = "int";
        } else if (type == 2) {
            numberType = "float";
        } else if (type == 3) {
            numberType = "double";
        }

        // dane do wpisania do pliku
        outputFile << "Typ danych: " << numberType << endl;
        outputFile << "Ilosc liczb: " << size << endl;
        outputFile << "Ilosc powtorzen: " << repetition << endl;
        outputFile << "Poziom losowosci liczb: " << arrangement << endl;
        outputFile << "Sredni czas sortowania: " << averageTime << " ms" << endl;

        outputFile.close(); // zamkniecie pliku
    }
};

#endif
