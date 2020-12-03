#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define TREE '#'

size_t get_trees(std::string forest, int right, int down) {
    size_t trees = 0;
    int current_line = 0;
    int i = 0;
    int j = 0;

    std::string line;
    std::istringstream stream(forest);

    while(std::getline(stream, line)) {
        if(current_line == 0) {
            current_line += down;
            i++;
            continue;
        }
        if(i % down != 0) {
            i++;
            continue;
        }

        int index = down == 1 ? current_line * right : right + j;
        j += right;

        if(index >= line.length()) {
            index %= line.length();
        } 

        if(line[index] == TREE) {
            trees++;
        }
        current_line += down;
        i++;
    }
    
    return trees;
}

int main(int, char**) {
    std::ifstream file;
    std::stringstream forest;
    file.open("input.txt");
    forest << file.rdbuf();

    size_t a = get_trees(forest.str(), 3, 1);
    size_t b = get_trees(forest.str(), 1, 1);
    size_t c = get_trees(forest.str(), 5, 1);
    size_t d = get_trees(forest.str(), 7, 1);
    size_t e = get_trees(forest.str(), 1, 2);

    std::cout << "Part 1: " << a << std::endl;
    std::cout << "Part 2: " << (a * b * c * d * e) << std::endl;

    file.close();
    return EXIT_SUCCESS;
}