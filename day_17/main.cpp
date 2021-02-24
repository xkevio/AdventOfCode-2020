#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int size = 25;

int get_neighbours(int x, int y, int z, char (&grid)[size][size][size]) {
    int n = 0;

    for (int i = -1; i < 2; i++) {
        if (z + i >= 0 && z + i < size) {
            if (x - 1 >= 0 && grid[x - 1][y][z + i] == '#') n++;
            if (x - 1 >= 0 && y - 1 >= 0 && grid[x - 1][y - 1][z + i] == '#') n++;
            if (x - 1 >= 0 && y + 1 < size && grid[x - 1][y + 1][z + i] == '#') n++;
            if (y - 1 >= 0 && grid[x][y - 1][z + i] == '#') n++;
            if (y - 1 >= 0 && x + 1 < size && grid[x + 1][y - 1][z + i] == '#') n++;
            if (x + 1 < size && grid[x + 1][y][z + i] == '#') n++;
            if (x + 1 < size && y + 1 < size && grid[x + 1][y + 1][z + i] == '#') n++;
            if (y + 1 < size && grid[x][y + 1][z + i] == '#') n++;
            if (grid[x][y][z + i] == '#' && i != 0) n++;
        }
    }

    return n;
}

int get_fneighbours(int x, int y, int z, int w, char (&f_grid)[size][size][size][size]) {
    int n = 0;

    for (int i = -1; i < 2; i++) {
        if (w + i >= 0 && w + i < size) {
            n += get_neighbours(x, y, z, f_grid[w + i]);  // in 3d space
            if (f_grid[w + i][x][y][z] == '#' && i != 0) n++;
        }
    }

    return n;
}

void cycle(char (&grid)[size][size][size], char (&f_grid)[size][size][size][size]) {
    char old_grid[size][size][size];
    char old_fgrid[size][size][size][size];
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < size; k++) {
                old_grid[i][j][k] = grid[i][j][k];
                for (size_t w = 0; w < size; w++) {
                    old_fgrid[w][i][j][k] = f_grid[w][i][j][k];
                }
            }
        }
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < size; k++) {
                auto cur = old_grid[i][j][k];
                if (cur == '#' && (get_neighbours(i, j, k, old_grid) < 2 ||
                                   get_neighbours(i, j, k, old_grid) > 3)) {
                    grid[i][j][k] = '.';
                }
                if (cur == '.' && get_neighbours(i, j, k, old_grid) == 3) {
                    grid[i][j][k] = '#';
                }
                for (size_t w = 0; w < size; w++) {
                    auto cur_ = old_fgrid[w][i][j][k];
                    if (cur_ == '#' && (get_fneighbours(i, j, k, w, old_fgrid) < 2 ||
                                        get_fneighbours(i, j, k, w, old_fgrid) > 3)) {
                        f_grid[w][i][j][k] = '.';
                    }
                    if (cur_ == '.' && get_fneighbours(i, j, k, w, old_fgrid) == 3) {
                        f_grid[w][i][j][k] = '#';
                    }
                }
            }
        }
    }
}

int main(int, char**) {
    std::ifstream file;
    std::string cur;
    file.open("input.txt");

    char grid[size][size][size];
    char f_grid[size][size][size][size];
    std::fill_n(&grid[0][0][0], size * size * size, '.');
    std::fill_n(&f_grid[0][0][0][0], size * size * size * size, '.');

    int j = 0;
    while (getline(file, cur)) {
        for (size_t i = 0; i < cur.length(); i++) {
            grid[j + 8][i + 8][8] = cur[i];
            f_grid[8][j + 8][i + 8][8] = cur[i];
        }
        j++;
    }

    for (size_t i = 0; i < 6; i++) {
        cycle(grid, f_grid);
    }

    int p1 = 0;
    int p2 = 0;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            for (size_t k = 0; k < size; k++) {
                if (grid[i][j][k] == '#') p1++;
                for (size_t w = 0; w < size; w++) {
                    if (f_grid[w][i][j][k] == '#') p2++;
                }
            }
        }
    }

    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;

    file.close();
    return EXIT_SUCCESS;
}