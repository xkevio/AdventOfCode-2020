#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int get_seat_id(const std::string& seat) {
    int rows = 0;
    int cols = 0;

    for (std::size_t i = 0; i < seat.length(); i++) {
        rows += seat[i] == 'B' ? 64 / (pow(2, i)) : 0;
        cols += seat[i] == 'R' ? 512 / (pow(2, i)) : 0;
    }

    return rows * 8 + cols;
}

int main() {
    std::ifstream file("input.txt");
    std::vector<int> all_seats;
    std::string cur_seat;

    while (std::getline(file, cur_seat)) {
        all_seats.push_back(get_seat_id(cur_seat));
    }

    std::cout << "Part 1: " << *std::max_element(all_seats.begin(), all_seats.end()) << std::endl;

    std::sort(all_seats.begin(), all_seats.end());

    for (std::size_t i = all_seats[0]; i < all_seats[all_seats.size() - 1]; i++) {
        if (all_seats[i] != all_seats[0] + i) {
            std::cout << "Part 2: " << all_seats[0] + i << std::endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}