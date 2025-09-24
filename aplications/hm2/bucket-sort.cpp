#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>

void bucketSort(std::vector<double>& arr) {
    
    std::vector<std::list<double>> buckets(5);

    for (double num : arr) {
        int bucketIndex = std::floor(5 * num); 
        buckets[bucketIndex].push_back(num);
    }
    
    for (auto& bucket : buckets) {
        bucket.sort(); 
    }

    arr.clear();
    for (const auto& bucket : buckets) {
        for (double num : bucket) {
            arr.push_back(num);
        }
    }
}

int main() {
    std::vector<double> numbers;
    std::ifstream inputFile("numbers.txt");

    if (!inputFile) {
        std::cout << "Eroare la deschiderea fisierului!" << std::endl;
        return 1;
    }

    double number;
    while (inputFile >> number) {
        if (number >= 0.0 && number <= 1.0) {
            numbers.push_back(number);
        }
    }
    inputFile.close();

    bucketSort(numbers);

    std::cout << "Vectorul sortat este: ";
    for (double num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}