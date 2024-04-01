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
#include <functional>

using namespace std;

enum {
    typeInt = 1,
    typeFloat = 2,
    typeDouble = 3
};

template<typename T>
class FileGenerator {
private:
    string filename; // nazwa pliku

public:
    FileGenerator() : filename("default.txt") {}

    FileGenerator(const string& filename) : filename(filename) {}

    // funkcja generujaca liczby losowe i zapisujaca je do pliku
    void generateAndWriteToFile(int count, int type) {
        ofstream outputFile(filename.c_str()); // otworzenie pliku

        if (!outputFile.is_open()) {
            cout << "nie mozna otworzyc pliku: " << filename << std::endl;
            return;
        }

        outputFile << count << std::endl; // pierwsza linia to liczba elementow

        // losowanie liczb wedlug podanego typu w main i zapisanie ich do pliku 
        if (type == typeInt) {
            int intMinValue = -10000;
            int intMaxValue = 10000;
            for (int i = 0; i < count; ++i) {
                T randomNumber = static_cast<T>(intMinValue + (rand() % (intMaxValue - intMinValue + 1))); // Losuj w zakresie od -10000 do 10000
                outputFile << randomNumber << std::endl; 
            }
        }
        else if (type == typeFloat) {
            const float floatMinValue = -10000.0f;
            const float floatMaxValue = 10000.0f;
            for (int i = 0; i < count; ++i) {
                float randomNumber = static_cast<float>(floatMinValue + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (floatMaxValue - floatMinValue))));
                outputFile << randomNumber << std::endl; 
            }
        }
        else if (type == typeDouble) {
            const double doubleMinValue = -10000.0;
            const double doubleMaxValue = 10000.0;
            for (int i = 0; i < count; ++i) {
                double randomNumber = doubleMinValue + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (doubleMaxValue - doubleMinValue)));
                outputFile << randomNumber << std::endl; 
            }
        }

        outputFile.close(); // zamkniecie pliku
        cout << "pomyslnie zapisano " << count << " losowych liczb typu " << typeid(T).name() << " do pliku " << filename << endl;
    }

    // funkcja ktora ustawia liczby z pliku w sposob malejacy
    void sortDescending(const string& filename) {
        ifstream inputFile(filename.c_str()); // otworzenie pliku
        if (!inputFile.is_open()) {
            std::cerr << "nie mozna otworzyc pliku: " << filename << endl;
            return;
        }

        int count; // wielkosc tablicy 
        inputFile >> count; // wczytanie wielkosci tablicy z pliku

        // wczytanie liczb z pliku
        T* numbers = new T[count];
        for (int i = 0; i < count; ++i) {
            inputFile >> numbers[i];
        }

        // sortowanie liczb malejaco
        sort(numbers, numbers + count, greater<T>());

        inputFile.close(); // zamkniecie pliku

        // ponowne otworzenie pliku i usuniecie liczb
        ofstream outputFile(filename.c_str());
        if (!outputFile.is_open()) {
            cout << "Nie mozna otworzyc pliku do zapisu: " << filename << endl;
            delete[] numbers;
            return;
        }

        // wczytanie wielkosci tablicy i liczb posortowanych malejaco
        outputFile << count << endl;
        for (int i = 0; i < count; ++i) {
            outputFile << numbers[i] << std::endl;
        }

        outputFile.close(); // zamkniecie pliku
        delete[] numbers; // zwolnienie pamieci

        cout << "liczby z pliku " << filename << " zostaly posortowane malejaco i zapisane z powrotem do tego samego pliku" << endl;
    }

    // funkcja ktora sortuje liczby rosnaco w zadanym procencie i zapisuje do pliku
    void sortAscendingWithPercentage(int percentage, const string& filename) {
        if (percentage <= 0 || percentage >= 100) {
            cout << "nieprawidlowy procent - nalezy podac wartosc pomiedzy 1 a 99" << endl;
            return;
        }

        ifstream inputFile(filename.c_str()); // otwarcie pliku
        if (!inputFile.is_open()) {
            cout << "nie mozna otworzyc pliku: " << filename << endl;
            return;
        }

        int count; // wielkosc tablciy
        inputFile >> count; // wczytanie wielkosci tablicy z pliku

        // wczytanie liczb z pliku
        T* numbers = new T[count];
        for (int i = 0; i < count; ++i) {
            inputFile >> numbers[i];
        }

        inputFile.close(); // zamkniecie pliku

        // posortowanie liczb wedlug danego procentu
        int sortedCount = count * percentage / 100;
        sort(numbers, numbers + sortedCount);

        // ponowne otwarcie pliku i usunecie liczb
        ofstream outputFile(filename.c_str());
        if (!outputFile.is_open()) {
            cout << "Nie mozna otworzyc pliku do zapisu: " << filename << endl;
            delete[] numbers;
            return;
        }

        // wczytanie wielkosci tablicy i posortowananych liczb do pliku
        outputFile << count << endl;
        for (int i = 0; i < count; ++i) {
            outputFile << numbers[i] << endl;
        }

        outputFile.close(); // zamkniecie pliku
        delete[] numbers; // zwolnienie pamieci
 
        cout << "liczby z pliku " << filename << " zostaly posortowane rosnaco (z uwzglednieniem " << percentage << "%) i zapisane z powrotem do tego samego pliku" << endl;
    }

    // funkcja ktora sortuje liczby rosnaco i zapisuje do pliku
    void sortAscendingAll(const string& filename) {
        ifstream inputFile(filename.c_str()); // otwarcie pliku
        if (!inputFile.is_open()) {
            cout << "nie mozna otworzyc pliku: " << filename << endl;
            return;
        }

        int count; // wielkosc tablicy
        inputFile >> count; // wczytanie wielkosci tablicy z pliku

        // wczytanie liczb z pliku
        T* numbers = new T[count];
        for (int i = 0; i < count; ++i) {
            inputFile >> numbers[i];
        }

        inputFile.close(); // zamkniecie pliku

        sort(numbers, numbers + count); // posortowanie liczb rosnaco

        // ponowne otwarcie pliku
        ofstream outputFile(filename.c_str());
        if (!outputFile.is_open()) {
            cout << "nie mozna otworzyc pliku do zapisu: " << filename << endl;
            delete[] numbers;
            return;
        }

        // wpisanie ilosc liczb i liczb do pliku
        outputFile << count << endl;
        for (int i = 0; i < count; ++i) {
            outputFile << numbers[i] << endl;
        }

        outputFile.close(); // zamkniecie pliku
        delete[] numbers; // zwolnienie pamieci

        cout << "liczby z pliku " << filename << " zostaly posortowane rosnaco i zapisane z powrotem do tego samego pliku" << endl;
    }
};

#endif
