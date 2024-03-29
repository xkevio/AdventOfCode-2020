#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

bool check_if_password(const std::string& word, char letter, int min, int max, bool part2) {
    return part2 ? (word[min - 1] == letter) ^ (word[max - 1] == letter)
                 : std::count(word.begin(), word.end(), letter) >= min && std::count(word.begin(), word.end(), letter) <= max;
}

int main() {
    std::ifstream file("input.txt");
    std::string text;

    int p1 = 0;
    int p2 = 0;

    if (file) {
        while (std::getline(file, text)) {
            int min = std::stoi(text.substr(0, text.find("-")));
            int max = std::stoi(text.substr(text.find("-") + 1, text.find(" ")));

            char letter = text.at(text.find(":") - 1);
            std::string word = text.substr(text.find(":") + 2);

            if (check_if_password(word, letter, min, max, false)) p1++;
            if (check_if_password(word, letter, min, max, true)) p2++;
        }
    }

    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;

    return EXIT_SUCCESS;
}