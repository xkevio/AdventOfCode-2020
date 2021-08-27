#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int sum = 2020;

// part 1
int part1(const std::vector<int>& list) {
    int result = 0;
    int l = 0, r = list.size() - 1;
    while (l < r) {
        if ((list[l] + list[r]) < sum) {
            l++;
        } else if ((list[l] + list[r]) > sum) {
            r--;
        } else {
            result = list[l] * list[r];
            break;
        }
    }
    return result;
}

// part 2
int find_three_sum(const std::vector<int>& list) {
    int result = 0;

    for (size_t i = 0; i < list.size() - 2; ++i) {
        int ind = list[i];
        int l = i + 1;
        int r = list.size() - 1;

        while (l < r) {
            if ((list[l] + list[r] + ind) < sum) {
                l++;
            } else if ((list[l] + list[r] + ind) > sum) {
                r--;
            } else {
                result = list[l] * list[r] * ind;
                break;
            }
        }
    }

    return result;
}

int main() {
    std::ifstream file("input.txt");
    std::string text;
    std::vector<int> list;

    if (file) {
        while (std::getline(file, text)) {
            list.push_back(std::stoi(text));
        }
    }

    std::sort(list.begin(), list.end());

    std::cout << "Part 1: " << part1(list) << std::endl;
    std::cout << "Part 2: " << find_three_sum(list) << std::endl;

    return EXIT_SUCCESS;
}