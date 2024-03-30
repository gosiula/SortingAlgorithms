#ifndef FILE_GENERATOR_CPP
#define FILE_GENERATOR_CPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <limits>
#include <functional> // Dla std::greater

template<typename T>
class FileGenerator {
private:
    std::string filename;

public:
    // Default constructor
    FileGenerator() : filename("default.txt") {}

    // Constructor with filename parameter
    FileGenerator(const std::string& filename) : filename(filename) {}

    void generateAndWriteToFile(int count, int type) {
        std::ofstream outputFile(filename.c_str());

        if (!outputFile.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
            return;
        }

        srand(static_cast<unsigned int>(time(0)));

        T minValue = std::numeric_limits<T>::min();
        T maxValue = std::numeric_limits<T>::max();

        outputFile << count << std::endl; // Pierwsza linia to liczba elementów

        if (type == 1) {
            for (int i = 0; i < count; ++i) {
                int randomNumber = (rand()) % (1000 - 0 + 1) + 0; // Losuj w zakresie od minValue do maxValue
                outputFile << randomNumber << std::endl; // Zapisz liczbę do pliku w nowej linii
            }
        }
        else if (type == 2) {
            for (int i = 0; i < count; ++i) {
                float randomNumber = (rand()) % (1000 - 0 + 1) + 0; // Losuj w zakresie od minValue do maxValue
                outputFile << randomNumber << std::endl; // Zapisz liczbę do pliku w nowej linii
            }
        }
        else if (type == 3) {
            for (int i = 0; i < count; ++i) {
                double randomNumber = (rand()) % (1000 - 0 + 1) + 0; // Losuj w zakresie od minValue do maxValue
                outputFile << randomNumber << std::endl; // Zapisz liczbę do pliku w nowej linii
            }
        }

        outputFile.close();
        std::cout << "Pomyslnie zapisano " << count << " losowych liczb typu " << typeid(T).name() << " do pliku " << filename << std::endl;
    }

    void sortDescending(const std::string& filename) {
        std::ifstream inputFile(filename.c_str());
        if (!inputFile.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
            return;
        }

        int count;
        inputFile >> count;

        T* numbers = new T[count];
        for (int i = 0; i < count; ++i) {
            inputFile >> numbers[i];
        }

        std::sort(numbers, numbers + count, std::greater<T>());

        inputFile.close();

        std::ofstream outputFile(filename.c_str());
        if (!outputFile.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku do zapisu: " << filename << std::endl;
            delete[] numbers;
            return;
        }

        outputFile << count << std::endl;
        for (int i = 0; i < count; ++i) {
            outputFile << numbers[i] << std::endl;
        }

        outputFile.close();
        delete[] numbers;

        std::cout << "Liczby z pliku " << filename << " zostaly posortowane malejaco i zapisane z powrotem do tego samego pliku" << std::endl;
    }

    void sortAscendingWithPercentage(int percentage,const std::string& filename) {
        if (percentage <= 0 || percentage >= 100) {
            std::cerr << "Nieprawidlowy procent. Prosze podac wartosc pomiedzy 0 a 100" << std::endl;
            return;
        }

        std::ifstream inputFile(filename.c_str());
        if (!inputFile.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
            return;
        }

        int count;
        inputFile >> count;

        T* numbers = new T[count];
        for (int i = 0; i < count; ++i) {
            inputFile >> numbers[i];
        }

        inputFile.close();

        int sortedCount = count * percentage / 100;
        std::sort(numbers, numbers + sortedCount);

        std::ofstream outputFile(filename.c_str());
        if (!outputFile.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku do zapisu: " << filename << std::endl;
            delete[] numbers;
            return;
        }

        outputFile << count << std::endl;
        for (int i = 0; i < count; ++i) {
            outputFile << numbers[i] << std::endl;
        }

        outputFile.close();
        delete[] numbers;

        std::cout << "Liczby z pliku " << filename << " zostaly posortowane rosnaco (z uwzglednieniem " << percentage << "%) i zapisane z powrotem do tego samego pliku" << std::endl;
    }

    void sortAscendingAll(const std::string& filename) {
        std::ifstream inputFile(filename.c_str());
        if (!inputFile.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
            return;
        }

        int count;
        inputFile >> count;

        T* numbers = new T[count];
        for (int i = 0; i < count; ++i) {
            inputFile >> numbers[i];
        }

        inputFile.close();

        std::sort(numbers, numbers + count);

        std::ofstream outputFile(filename.c_str());
        if (!outputFile.is_open()) {
            std::cerr << "Nie mozna otworzyc pliku do zapisu: " << filename << std::endl;
            delete[] numbers;
            return;
        }

        outputFile << count << std::endl;
        for (int i = 0; i < count; ++i) {
            outputFile << numbers[i] << std::endl;
        }

        outputFile.close();
        delete[] numbers;

        std::cout << "Liczby z pliku " << filename << " zostaly posortowane rosnaco i zapisane z powrotem do tego samego pliku" << std::endl;
    }
};

#endif
