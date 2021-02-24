#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int sum = 2020;

// part 2
int find_three_sum(const std::vector<int>& list) {
    int result = 0;

    for (size_t i = 0; i < list.size() - 2; i++) {
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

int main(int, char**) {
    std::ifstream file;
    std::string text;
    std::vector<int> list;

    file.open("input.txt");

    if (file.is_open()) {
        while (std::getline(file, text)) {
            list.push_back(stoi(text));
        }
    }
    std::sort(list.begin(), list.end());

    // part 1
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

    std::cout << "Part 1: " << result << std::endl;
    std::cout << "Part 2: " << find_three_sum(list) << std::endl;

    file.close();
    return EXIT_SUCCESS;
}