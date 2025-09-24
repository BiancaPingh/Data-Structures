#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

void findSubarraysWithSum(const std::vector<int>& numbers, int k) {
    std::unordered_map<int, std::vector<int>> sumMap;
    int currentSum = 0;
    bool found = false;

    
    sumMap[0].push_back(-1);

    for (int i = 0; i < numbers.size(); ++i) {
        currentSum += numbers[i];
  
        if (sumMap.find(currentSum - k) != sumMap.end()) {
            for (int start : sumMap[currentSum - k]) {
                found = true;
                std::cout << "Subarray de la indexul " << start + 1 << " la " << i << std::endl;
            }
        }

        sumMap[currentSum].push_back(i);
    }
    if (found == false)
        std::cout << "Nu se poate forma suma. \n";
}

int main() {
    std::ifstream inputFile("numbers.txt");

    int Nr;
    inputFile >> Nr;

    std::vector<int> numbers(Nr);
    for (int i = 0; i < Nr; ++i) {
        inputFile >> numbers[i];
    }

    inputFile.close();

    int k;
    char choice;
    do {
        std::cout << "Introdu k: ";
        std::cin >> k;

        findSubarraysWithSum(numbers, k);

        std::cout << "Vrei sa mai dai valori? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}