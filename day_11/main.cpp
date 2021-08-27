#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int get_vision_neighbours(int row, int col, const std::vector<std::vector<char>>& grid) {
    int n = 0;
    int width = grid[0].size();
    int height = grid.size();

    int i = 1;
    int j = 1;
    while (row - i >= 0) {
        if (grid[row - i][col] == '#') {
            n++;
            break;
        }
        if (grid[row - i][col] == 'L') {
            break;
        }
        i++;
    }
    i = 1;
    j = 1;
    while (row - i >= 0 && col - i >= 0) {
        if (grid[row - i][col - i] == '#') {
            n++;
            break;
        }
        if (grid[row - i][col - i] == 'L') {
            break;
        }
        i++;
    }
    i = 1;
    j = 1;
    while (row - i >= 0 && col + j < width) {
        if (grid[row - i][col + j] == '#') {
            n++;
            break;
        }
        if (grid[row - i][col + j] == 'L') {
            break;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while (col - i >= 0) {
        if (grid[row][col - i] == '#') {
            n++;
            break;
        }
        if (grid[row][col - i] == 'L') {
            break;
        }
        i++;
    }
    i = 1;
    j = 1;
    while (col - i >= 0 && row + j < height) {
        if (grid[row + j][col - i] == '#') {
            n++;
            break;
        }
        if (grid[row + j][col - i] == 'L') {
            break;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while (row + i < height) {
        if (grid[row + i][col] == '#') {
            n++;
            break;
        }
        if (grid[row + i][col] == 'L') {
            break;
        }
        i++;
    }
    i = 1;
    j = 1;
    while (row + i < height && col + j < width) {
        if (grid[row + i][col + j] == '#') {
            n++;
            break;
        }
        if (grid[row + i][col + j] == 'L') {
            break;
        }
        i++;
        j++;
    }
    i = 1;
    j = 1;
    while (col + i < width) {
        if (grid[row][col + i] == '#') {
            n++;
            break;
        }
        if (grid[row][col + i] == 'L') {
            break;
        }
        i++;
    }

    return n;
}

int get_neighbours(int row, int col, const std::vector<std::vector<char>>& grid) {
    int n = 0;
    int width = grid[0].size();
    int height = grid.size();

    if (row - 1 >= 0 && grid[row - 1][col] == '#') n++;
    if (row - 1 >= 0 && col - 1 >= 0 && grid[row - 1][col - 1] == '#') n++;
    if (row - 1 >= 0 && col + 1 < width && grid[row - 1][col + 1] == '#') n++;
    if (col - 1 >= 0 && grid[row][col - 1] == '#') n++;
    if (col - 1 >= 0 && row + 1 < height && grid[row + 1][col - 1] == '#') n++;
    if (row + 1 < height && grid[row + 1][col] == '#') n++;
    if (row + 1 < height && col + 1 < width && grid[row + 1][col + 1] == '#') n++;
    if (col + 1 < width && grid[row][col + 1] == '#') n++;

    return n;
}

void cycle(const std::vector<std::vector<char>>& grid, std::vector<std::vector<char>>& new_grid, bool part2) {
    for (std::size_t i = 0; i < grid.size(); i++) {
        for (std::size_t j = 0; j < grid[i].size(); j++) {
            if (!part2) {
                if (grid[i][j] == 'L' && get_neighbours(i, j, grid) == 0) {
                    new_grid[i][j] = '#';
                }
                if (grid[i][j] == '#' && get_neighbours(i, j, grid) >= 4) {
                    new_grid[i][j] = 'L';
                }
            } else {
                if (grid[i][j] == 'L' && get_vision_neighbours(i, j, grid) == 0) {
                    new_grid[i][j] = '#';
                }
                if (grid[i][j] == '#' && get_vision_neighbours(i, j, grid) >= 5) {
                    new_grid[i][j] = 'L';
                }
            }
        }
    }
}

// jesus...
int get_occupied_seats(std::vector<std::vector<char>> grid, bool part2) {
    int seats = 0;

    auto grid2 = grid;
    auto& new_grid = grid;
    auto& new_grid2 = grid2;

    cycle(grid2, new_grid, part2);
    cycle(new_grid, new_grid2, part2);

    while (new_grid != new_grid2) {
        new_grid = new_grid2;
        cycle(new_grid, new_grid2, part2);
    }
    for (const auto& k : new_grid) {
        for (const auto& v : k) {
            if (v == '#') seats++;
        }
    }

    return seats;
}

int main() {
    std::ifstream file("input.txt");
    std::vector<std::vector<char>> grid;
    std::string cur;

    while (std::getline(file, cur)) {
        std::vector<char> row;
        for (std::size_t i = 0; i < cur.length(); i++) {
            row.push_back(cur[i]);
        }
        grid.push_back(row);
    }

    std::cout << "Part 1: " << get_occupied_seats(grid, false) << std::endl;
    std::cout << "Part 2: " << get_occupied_seats(grid, true) << std::endl;

    return EXIT_SUCCESS;
}