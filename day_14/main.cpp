#include <iostream>
#include <vector>
#include <numeric>
#include <bitset>
#include <fstream>
#include <cstdint>
#include <string>
#include <cmath>
#include <unordered_map>
#include <utility>

std::string mask;
std::vector<std::uint64_t> memory(100000);
std::unordered_map<std::uint64_t, std::uint64_t> memory2;

void add_value_to_memory2(std::unordered_map<std::uint64_t, std::uint64_t> &memory, int address, std::uint64_t value) {
    std::bitset<36> bits(address);
    std::string s_value = bits.to_string();

    std::vector<int> pv;

    for (size_t i = 0; i < mask.length(); i++)
    {
        if(mask[i] == 'X') {
            s_value[i] = 'X';
            pv.push_back(i);
        }
        if(mask[i] == '1') s_value[i] = '1';
    }

    for (size_t j = 0; j < pow(2, pv.size()); j++)
    {
        std::string cur_bits = std::bitset<36>(j).to_string();
        for (size_t k = 0; k < pv.size(); k++)
        {
            s_value[pv[k]] = cur_bits[cur_bits.size() - 1 - k];
        }
        memory[std::bitset<36>(s_value).to_ullong()] = value;
    }
}

void add_value_to_memory(std::vector<std::uint64_t> &memory, int address, int value) {
    std::bitset<36> bits(value);
    std::string s_value = bits.to_string();
    for (size_t i = 0; i < mask.length(); i++)
    {
        if(mask[i] == '0') s_value[i] = '0';
        if(mask[i] == '1') s_value[i] = '1';
    }

    auto n_value = (std::uint64_t) std::bitset<36>(s_value).to_ullong();
    memory[address] = n_value;
}

int main(int, char**) {
    std::ifstream file;
    std::string cur;
    file.open("input.txt");
    
    while(getline(file, cur)) {
        std::string instruction = cur.substr(0, cur.find_first_of(" "));
        std::string value = cur.substr(cur.find_last_of(" ") + 1);

        if(instruction == "mask") {
            mask = value;
        } else {
            std::string s_add = instruction.substr(instruction.find_first_of("[") + 1, instruction.find_first_of("]") - 4);
            add_value_to_memory(memory, stoi(s_add), stoi(value));
            add_value_to_memory2(memory2, stoi(s_add), stoull(value));
        }
    }

    std::cout << "Part 1: " << std::accumulate(memory.begin(), memory.end(), static_cast<uint64_t>(0)) << std::endl;
    std::cout << "Part 2: " << std::accumulate(memory2.begin(), memory2.end(), static_cast<uint64_t>(0), [](std::uint64_t acc, const std::pair<std::uint64_t, std::uint64_t> &p) {
        return acc + p.second;
    }) << std::endl;

    file.close();
    return EXIT_SUCCESS;
}