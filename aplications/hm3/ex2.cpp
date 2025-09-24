#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

std::string canFormPalindrome(const std::string& str) {
    std::unordered_map<char, int> charCount;

    for (char c : str) {
        charCount[c]++;
    }

    int oddCount = 0;
    for (const auto& pair : charCount) {
        if (pair.second % 2 != 0) {
            oddCount++;
        }
    }

    if (oddCount > 1) {
        return "nu se poate face";
    }

    std::string palindrome;
    char middleChar = '\0';
    for (const auto& pair : charCount) {
        if (pair.second % 2 != 0) {
            middleChar = pair.first; 
        }
        palindrome += std::string(pair.second / 2, pair.first); // jumatate din caractere
    }

    std::string reversePart = palindrome; 
    std::reverse(reversePart.begin(), reversePart.end());


    if (middleChar != '\0') {
        palindrome += middleChar;
    }
    palindrome += reversePart;

    return palindrome;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string inputString;

    if (inputFile.is_open()) {
        std::getline(inputFile, inputString);
        inputFile.close();
    }
    else {
        std::cout << "Nu se poate deschide fisierul";
        return 1;
    }

    std::string result = canFormPalindrome(inputString);
    std::cout << "Palindrome: " << result << std::endl;
    return 0;
}