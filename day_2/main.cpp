#include <iostream>
#include <fstream>
#include <string>

bool check_if_password(std::string word, char letter, int min, int max, bool part2) {
    if(part2) return word[min-1] == letter ^ word[max-1] == letter;

    int a = 0;
    for (size_t i = 0; i < word.length(); i++)
    {
        if(word[i] == letter) {
            a++;
        }
    }
    return a >= min && a <= max;
}

int main(int, char**) {
    std::ifstream file;
    std::string text;

    int p1 = 0;
    int p2 = 0;

    file.open("input.txt");

    if(file.is_open()) {
        while(std::getline(file, text)) {
            int min = std::stoi(text.substr(0, text.find("-")));
            int max = std::stoi(text.substr(text.find("-") + 1, text.find(" ")));
            int a = 0;
            int b = 0;

            char letter = text.at(text.find(":") - 1);
            std::string word = text.substr(text.find(":") + 2);

            if(check_if_password(word, letter, min, max, false)) p1++;
            if(check_if_password(word, letter, min, max, true)) p2++;            
        }
    }

    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;

    file.close();
    return EXIT_SUCCESS;
}