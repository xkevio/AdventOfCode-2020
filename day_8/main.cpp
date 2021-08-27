#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

enum class Instructions { NOP, JMP, ACC, INVALID };

constexpr Instructions resolve(const std::string& input) {
    if (input == "nop") return Instructions::NOP;
    if (input == "jmp") return Instructions::JMP;
    if (input == "acc") return Instructions::ACC;
    return Instructions::INVALID;
}

std::unordered_set<int> execute(const std::vector<std::string>& instructions, int& acc, bool loop) {
    acc = 0;
    int program_counter = 0;
    std::unordered_set<int> exec;
    while (program_counter < instructions.size()) {
        if (!loop) {
            if (exec.find(program_counter) != exec.end()) break;
            exec.insert(program_counter);
        }

        std::string ins = instructions[program_counter].substr(0, instructions[program_counter].find(' '));
        std::string snum = instructions[program_counter].substr(instructions[program_counter].find(' ') + 1);
        int num = snum[0] == '+' ? std::stoi(snum.substr(1)) : -(std::stoi(snum.substr(1)));

        switch (resolve(ins)) {
            case Instructions::NOP:
                program_counter++;
                break;
            case Instructions::JMP:
                program_counter += num;
                break;
            case Instructions::ACC:
                acc += num;
                program_counter++;
                break;
            default:
                program_counter++;
                break;
        }
    }
    return exec;
}

int find_flip_counter(const std::vector<std::string>& instructions) {
    for (size_t i = 0; i < instructions.size(); i++) {
        std::string ins = instructions[i].substr(0, instructions[i].find(' '));
        if (ins == "nop") {
            auto new_instructions = instructions;
            new_instructions[i] = "jmp " + instructions[i].substr(instructions[i].find_first_of(' ') + 1);
            int acc;
            auto exec = execute(new_instructions, acc, false);

            if (*std::max_element(exec.begin(), exec.end()) == instructions.size() - 1) {
                return i;
            }
            continue;
        }
        if (ins == "jmp") {
            auto new_instructions = instructions;
            new_instructions[i] = "nop " + instructions[i].substr(instructions[i].find_first_of(' ') + 1);
            int acc;

            auto exec = execute(new_instructions, acc, false);

            if (*std::max_element(exec.begin(), exec.end()) == instructions.size() - 1) {
                return i;
            }
            continue;
        }
    }

    return 0;
}

int main() {
    std::ifstream file("input.txt");
    std::vector<std::string> instructions;
    std::string cur;

    while (std::getline(file, cur)) {
        instructions.push_back(cur);
    }

    // part 1
    int acc = 0;
    auto exec = execute(instructions, acc, false);

    std::cout << "Part 1: " << acc << std::endl;

    // part 2
    int acc2 = 0;
    int i = find_flip_counter(instructions);
    instructions[i] = "nop " + instructions[i].substr(instructions[i].find_first_of(' ') + 1);

    auto exec2 = execute(instructions, acc2, true);
    std::cout << "Part 2: " << acc2 << std::endl;

    return EXIT_SUCCESS;
}