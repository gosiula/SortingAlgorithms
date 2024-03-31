#include <iostream>
#include <fstream>
#include <string>

#ifndef RESULT_SAVER_CPP
#define RESULT_SAVER_CPP

class ResultSaver {
private:
    std::string originalFilename;

public:
    ResultSaver() = default;

    ResultSaver(const std::string& originalFilename) : originalFilename(originalFilename) {}

    void setOriginalFilename(const std::string& filename) {
        originalFilename = filename;
    }

    void saveResults(int type, int size, int repetition, double averageTime, const std::string& arrangement, const std::string& filename) {      
        // Tworzenie nazwy pliku wynikowego z oryginalną nazwą pliku
        std::string result = "wyniki_";
        std::string resultFilename = result + filename;
        std::cout << filename;

        std::ofstream outputFile(resultFilename.c_str()); // Użyj c_str() aby uzyskać const char*

        if (!outputFile.is_open()) {
            std::cerr << "Nie można otworzyć pliku: " << resultFilename << std::endl;
            return;
        }

        std::string numberType;
        if (type == 1) {
            numberType = "int";
        } else if (type == 2) {
            numberType = "float";
        } else if (type == 3) {
            numberType = "double";
        }

        outputFile << "Typ danych: " << numberType << std::endl;
        outputFile << "Ilosc liczb: " << size << std::endl;
        outputFile << "Ilosc powtorzen: " << repetition << std::endl;
        outputFile << "Poziom losowosci liczb: " << arrangement << std::endl;
        outputFile << "Sredni czas sortowania: " << averageTime << " ms" << std::endl;

        outputFile.close();
    }
};

#endif
