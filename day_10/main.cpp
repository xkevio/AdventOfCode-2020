#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

std::unordered_map<int, std::vector<int>> graph;
std::unordered_map<int, size_t> mem;

int joltage_diff(const std::vector<int>& adapters) {
    int one_diff = 0;
    int three_diff = 0;

    if (adapters[0] - 0 == 1) one_diff++;
    if (adapters[0] - 0 == 3) three_diff++;

    for (std::size_t i = 0; i < adapters.size() - 1; i++) {
        if (adapters[i + 1] - adapters[i] == 1) one_diff++;
        if (adapters[i + 1] - adapters[i] == 3) three_diff++;
    }
    three_diff++;

    return one_diff * three_diff;
}

void construct_adjacency_list(const std::vector<int>& adapters) {
    for (std::size_t i = 0; i < adapters.size(); i++) {
        std::vector<int> list;
        if (std::find(adapters.begin(), adapters.end(), adapters[i] + 1) != adapters.end()) {
            list.push_back(adapters[i] + 1);
        }
        if (std::find(adapters.begin(), adapters.end(), adapters[i] + 2) != adapters.end()) {
            list.push_back(adapters[i] + 2);
        }
        if (std::find(adapters.begin(), adapters.end(), adapters[i] + 3) != adapters.end()) {
            list.push_back(adapters[i] + 3);
        }

        std::pair<int, std::vector<int>> p(adapters[i], list);
        graph.insert(p);
    }
}

std::size_t get_arrangements(int start) {
    std::size_t arr = 0;

    if (graph.at(start).empty()) {
        return ++arr;
    }
    if (mem.find(start) != mem.end()) {
        return mem.at(start);
    }
    for (auto t : graph.at(start)) {
        arr += get_arrangements(t);

        std::pair<int, size_t> p(t, arr);
        mem.insert(p);
    }

    return arr;
}

int main() {
    std::ifstream file("input.txt");
    std::vector<int> adapters;
    std::string cur;

    while (std::getline(file, cur)) {
        adapters.push_back(std::stoi(cur));
    }
    adapters.push_back(0);

    std::sort(adapters.begin(), adapters.end());
    construct_adjacency_list(adapters);

    std::cout << "Part 1: " << joltage_diff(adapters) << std::endl;
    std::cout << "Part 2: " << get_arrangements(adapters[0]) << std::endl;

    return EXIT_SUCCESS;
}