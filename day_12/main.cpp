#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

struct Waypoint {
    int ns;
    int we;
};

class Ship {
    public:
        int manhattan_distance();
        void move(char ins, int val);
        void move_relative(char ins, int val);
        Ship(char dir, int we_start, int ns_start) {
            cur_dir = dir;
            we = we_start;
            ns = ns_start;

            waypoint.ns = 1;
            waypoint.we = 10;
        };
    private:
        int we;
        int ns;
        char cur_dir;
        Waypoint waypoint;
        void change_direction(char dir, int angle);
};

int Ship::manhattan_distance() {
    return abs(ns) + abs(we);
}

void Ship::move_relative(char ins, int val) {
    switch (ins)
    {
        case 'N':
            waypoint.ns += val;
            break;
        case 'S':
            waypoint.ns -= val;
            break;
        case 'E':
            waypoint.we += val;
            break;
        case 'W':
            waypoint.we -= val;
            break;
        case 'F':
            if(waypoint.we > 0) {
                we += val * waypoint.we;
            } else {
                we -= val * abs(waypoint.we);
            }
            if(waypoint.ns > 0) {
                ns += val * waypoint.ns;
            } else {
                ns -= val * abs(waypoint.ns);
            }
            break;
        case 'L':
            for (size_t i = 0; i < val/90; i++)
            {
                int temp = waypoint.ns;
                waypoint.ns = waypoint.we;
                waypoint.we = -temp;
            }
            break;
        case 'R':
            for (size_t i = 0; i < val/90; i++)
            {
                int temp = waypoint.ns;
                waypoint.ns = - waypoint.we;
                waypoint.we = temp;
            }
            break;
        default:
            break;
    }
}

void Ship::move(char ins, int val) {
    switch (ins)
    {
        case 'N':
            ns += val;
            break;
        case 'S':
            ns -= val;
            break;
        case 'E':
            we += val;
            break;
        case 'W':
            we -= val;
            break;
        case 'F':
            move(Ship::cur_dir, val);
            break;
        case 'L':
            change_direction('L', val);
            break;
        case 'R':
            change_direction('R', val);
            break;
        default:
            break;
    }
}

void Ship::change_direction(char dir, int angle) {
    if(angle == 360) return;
    int ii = angle / 90;
    for (size_t i = 0; i < ii; i++)
    {
        if(dir == 'R') {
            switch (cur_dir)
            {
                case 'N':
                    cur_dir = 'E';
                    break;
                case 'E':
                    cur_dir = 'S';
                    break;
                case 'S':
                    cur_dir = 'W';
                    break;
                case 'W':
                    cur_dir = 'N';
                    break;
                default:
                    break;
            }
        }
        if(dir == 'L') {
            switch (cur_dir)
            {
                case 'N':
                    cur_dir = 'W';
                    break;
                case 'E':
                    cur_dir = 'N';
                    break;
                case 'S':
                    cur_dir = 'E';
                    break;
                case 'W':
                    cur_dir = 'S';
                    break;
                default:
                    break;
            }
        }
    }
}

int main(int, char**) {
    std::ifstream file;
    std::string cur;
    std::vector<std::string> ins;
    file.open("input.txt");

    while(getline(file, cur)) {
        ins.push_back(cur);
    }

    Ship ship('E', 0, 0);
    Ship ship2('E', 0, 0);
    for(auto &in : ins) {
        char a = in[0];
        int val = stoi(in.substr(1));

        ship.move(a, val);
        ship2.move_relative(a, val);
    }

    std::cout << "Part 1: " << ship.manhattan_distance() << std::endl;
    std::cout << "Part 2: " << ship2.manhattan_distance() << std::endl;

    file.close();
    return EXIT_SUCCESS;
}