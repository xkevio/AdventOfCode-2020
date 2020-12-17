#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct Range {
    int first_min;
    int first_max;

    int second_min;
    int second_max;
};

bool is_in_range(int num, const Range &r) {
    return (num >= r.first_min && num <= r.first_max) || (num >= r.second_min && num <= r.second_max); 
}

int get_wrong_number(const std::string &line, const std::vector<Range> &range) {
    std::stringstream se(line);
    std::string cur;
    
    while(getline(se, cur, ',')) {
        int num = stoi(cur);
        bool exists = false;

        for(auto &r : range) {
            if(is_in_range(num, r)) {
                exists = true;
                break;
            }
        }
        if(!exists) {
            return num;
        }
    }
    return 0;
}

int main(int, char**) {
    std::ifstream file;
    std::string cur;
    std::vector<Range> ranges;
    file.open("input.txt");

    int part1 = 0;

    bool range_done = false;
    bool analyze = false;
    while(getline(file, cur)) {
        if(!cur.empty() && !range_done) {
            Range r;

            std::string values = cur.substr(cur.find_first_of(":") + 2);
            std::cout << values << std::endl;
            r.first_min = stoi(values.substr(0, values.find("-")));
            r.first_max = stoi(values.substr(values.find("-")+1, values.find("or") - 3));

            std::string nv = values.substr(values.find_last_of(" ") + 1, values.find_last_of("-"));
            r.second_min = stoi(nv.substr(0, nv.find("-")));
            r.second_max = stoi(nv.substr(nv.find("-")+1));

            ranges.push_back(r);
        }
        if(cur.empty() && !range_done) {
            range_done = true;
        }
        if(cur == "nearby tickets:") {
            analyze = true;
            continue;
        }
        if(analyze) {
            part1 += get_wrong_number(cur, ranges);
        }
    }


    std::cout << "Part 1: " << part1 << std::endl;





    file.close();
    return EXIT_SUCCESS;
}