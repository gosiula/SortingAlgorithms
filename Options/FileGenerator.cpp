#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

template<typename T>
class FileGenerator {
private:
    std::string filename;

public:
    FileGenerator(const std::string& filename) : filename(filename) {}

    void generateAndWriteToFile(int count) {
        std::ofstream outputFile(filename);

        if (!outputFile.is_open()) {
            std::cerr << "nie mozna otworzyc pliku: " << filename << std::endl;
            return;
        }

        srand(static_cast<unsigned int>(time(nullptr)));

        outputFile << count << std::endl; // Zapisz liczbę generowanych liczb jako pierwszą wartość w pliku

        for (int i = 0; i < count; ++i) {
            T randomNumber = static_cast<T>(rand()); // Losuj liczby typu T
            outputFile << randomNumber << std::endl; // Generuj liczby i zapisuj je do pliku w kolejnych liniach
        }

        outputFile.close();
        std::cout << "pomyslnie zapisano " << count << " liczb/y do pliku " << filename << std::endl;
    }

    void sortAndWriteDescending() {
        std::ifstream inputStream(filename);
        std::ofstream outputStream(filename); // Nadpisujemy plik

        if (!inputStream.is_open() || !outputStream.is_open()) {
            std::cerr << "nie mozna otworzyc pliku" << std::endl;
            return;
        }

        int count;
        inputStream >> count;

        T* numbers = new T[count];
        for (int i = 0; i < count; ++i) {
            inputStream >> numbers[i];
        }

        std::sort(numbers, numbers + count, std::greater<T>());

        outputStream << count << std::endl;
        for (int i = 0; i < count; ++i) {
            outputStream << numbers[i] << std::endl;
        }

        delete[] numbers;

        inputStream.close();
        outputStream.close();

        std::cout << "pomyslnie zapisano " << count << " liczb/y do pliku " << filename << " w kolejnosci malejacej" << std::endl;
    }

    void sortAndWritePercent(double percent) {
    std::ifstream inputStream(filename);
    std::ofstream outputStream("temp.txt"); // Tymczasowy plik wyjściowy

    if (!inputStream.is_open() || !outputStream.is_open()) {
        std::cerr << "nie mozna otworzyc pliku" << std::endl;
        return;
    }

    int count;
    inputStream >> count;

    T* numbers = new T[count];
    for (int i = 0; i < count; ++i) {
        inputStream >> numbers[i];
    }

    int rangeCount = static_cast<int>(count * percent);
    int remainingCount = count - rangeCount;

    std::sort(numbers, numbers + rangeCount);

    outputStream << count << std::endl;
    for (int i = 0; i < rangeCount; ++i) {
        outputStream << numbers[i] << std::endl;
    }

    // Zapisujemy pozostałe liczby w oryginalnej kolejności
    for (int i = rangeCount; i < count; ++i) {
        outputStream << numbers[i] << std::endl;
    }

    delete[] numbers;

    inputStream.close();
    outputStream.close();

    // Zamiana plików
    std::remove(filename.c_str());
    std::rename("temp.txt", filename.c_str());

    std::cout << "pomyslnie zapisano " << rangeCount << " liczb/y do pliku " << filename << " w " << (percent * 100) << "% w kolejnosci rosnacej" << std::endl;
}

};
