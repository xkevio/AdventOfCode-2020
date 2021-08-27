#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

constexpr char tree = '#';

std::size_t get_trees(const std::string& forest, int right, int down) {
    std::size_t trees = 0;
    int current_line = 0;
    int i = 0;
    int j = 0;

    std::string line;
    std::istringstream stream(forest);

    while (std::getline(stream, line)) {
        if (current_line == 0) {
            current_line += down;
            i++;
            continue;
        }
        if (i % down != 0) {
            i++;
            continue;
        }

        std::size_t index = down == 1 ? current_line * right : right + j;
        j += right;

        if (index >= line.length()) {
            index %= line.length();
        }

        if (line[index] == tree) {
            trees++;
        }
        current_line += down;
        i++;
    }

    return trees;
}

int main() {
    std::ifstream file("input.txt");
    std::stringstream forest;
    forest << file.rdbuf();

    std::size_t a = get_trees(forest.str(), 3, 1);
    std::size_t b = get_trees(forest.str(), 1, 1);
    std::size_t c = get_trees(forest.str(), 5, 1);
    std::size_t d = get_trees(forest.str(), 7, 1);
    std::size_t e = get_trees(forest.str(), 1, 2);

    std::cout << "Part 1: " << a << std::endl;
    std::cout << "Part 2: " << (a * b * c * d * e) << std::endl;

    return EXIT_SUCCESS;
}