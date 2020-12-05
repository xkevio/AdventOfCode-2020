#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_set>

int get_seat_id(std::string seat) {
    int rows = 0;
    int cols = 0;

    for (size_t i = 0; i < seat.length(); i++)
    {
        rows += seat[i] == 'B' ? 64 / (pow(2, i)) : 0;
        cols += seat[i] == 'R' ? 512 / (pow(2, i)) : 0;
    }
    
    return rows * 8 + cols;
}

int main(int, char**) {
    std::ifstream file;
    std::unordered_set<int> all_seats;
    std::string cur_seat;
    file.open("input.txt");

    while(getline(file, cur_seat)) {
        all_seats.insert(get_seat_id(cur_seat));
    }

    std::cout << "Part 1: " << *std::max_element(all_seats.begin(), all_seats.end()) << std::endl;
    for (size_t i = 46; i <= 915; i++)
    {
        if(all_seats.find(i) == all_seats.end()) {
            std::cout << "Part 2: " << i << std::endl;
            break;
        }
    }

    file.close();
    return EXIT_SUCCESS;
}