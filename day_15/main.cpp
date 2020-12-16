#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <chrono>

const std::string &input = "2,15,0,9,1,20";

int get_spoken_number(int when) {
    int num = 0;

    std::vector<int> numbers;
    std::unordered_map<int, std::pair<int,int>> recent;
    std::unordered_map<int, int> occur;

    std::string cur;
    std::stringstream stream(input);
    int ij = 1;
    while(getline(stream, cur, ',')) {
        numbers.push_back(stoi(cur));
        recent.insert({stoi(cur), {ij, 0}});
        occur.insert({stoi(cur), 1});
        ij++;
    }

    num = numbers[numbers.size() - 1];
    for (size_t i = numbers.size(); i <= when-1; i++)
    {
        int occ = occur[num];

        if(occ <= 1) {
            num = 0;
            occur[num] = occur[num] + 1;
        } else {            
            auto p = recent[num];
            num = p.first - p.second;
            occur[num] = occur[num] + 1;
        }

        if(recent.find(num) != recent.end()) {
            recent[num] = {i+1, recent[num].first};
        } else {
            recent[num] = {i+1, 0};
        }
    }
    
    return num;
}

int main(int, char**) {

    std::cout << "Part 1: " << get_spoken_number(2020) << std::endl;
    std::cout << "Part 2: " << get_spoken_number(30000000) << std::endl;

    return EXIT_SUCCESS;
}