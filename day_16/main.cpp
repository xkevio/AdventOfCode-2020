#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

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

std::uint64_t mult_ticket(const std::string &your_ticket, const std::unordered_map<int, std::vector<std::string>> &order) {
    std::uint64_t i = 1;
    int j = 0;

    std::stringstream st(your_ticket);
    std::string c;
    std::string d = "departure";

    while(getline(st, c, ',')) {
        if(order.find(j) != order.end()) {
            if(order.at(j)[0].substr(0, d.length()) == d) {
                i *= stoull(c);
            }
        }
        j++;
    }
    return i;
}

void remove_multiple_ranges(std::unordered_map<int, std::vector<std::string>> &order) {
    std::string word;
    std::vector<int> treated;

    while(treated.size() < 20) {
        for(auto &p : order) {
            if(p.second.size() == 1 && std::find(treated.begin(), treated.end(), p.first) == treated.end()) {
                word = p.second[0];
                treated.push_back(p.first);
            }
        }
        for(auto &p : order) {
            if(p.second.size() > 1) {
                p.second.erase(std::remove(p.second.begin(), p.second.end(), word), p.second.end());
            }
        }
    }
}

std::uint64_t get_departures(const std::vector<std::string> &valid, std::unordered_map<std::string, Range> &ranges_, const std::string yt) {
    std::vector<std::vector<int>> all_values;
    std::unordered_map<int, std::vector<std::string>> order;

    for(auto &s : valid) {
        std::stringstream cur_line(s);
        std::string cur;
        std::vector<int> row;
        while(getline(cur_line, cur, ',')) {
            row.push_back(stoi(cur));
        }
        all_values.push_back(row);
    }

    for (size_t i = 0; i < all_values[0].size(); i++)
    {
        std::vector<std::string> pp;
        for(auto &p : ranges_) {
            bool in_range = true;
            for (size_t j = 0; j < all_values.size(); j++)
            {   
                if(!is_in_range(all_values[j][i], p.second)) {
                    
                    in_range = false;
                    break;
                }
            }
            if(in_range) {
                pp.push_back(p.first);
            }
        }
        order[i] = pp;
    }

    remove_multiple_ranges(order);
    return mult_ticket(yt, order);
}

int main(int, char**) {
    std::ifstream file;
    std::string cur;

    std::unordered_map<std::string, Range> ranges_;
    std::string your_ticket;
    bool yt = false;

    std::vector<Range> ranges;
    std::vector<std::string> valid;
    file.open("input.txt");

    int part1 = 0;

    bool range_done = false;
    bool analyze = false;
    while(getline(file, cur)) {
        if(!cur.empty() && !range_done) {
            Range r;

            std::string range_name = cur.substr(0, cur.find(":"));

            std::string values = cur.substr(cur.find_first_of(":") + 2);
            r.first_min = stoi(values.substr(0, values.find("-")));
            r.first_max = stoi(values.substr(values.find("-")+1, values.find("or") - 3));

            std::string nv = values.substr(values.find_last_of(" ") + 1, values.find_last_of("-"));
            r.second_min = stoi(nv.substr(0, nv.find("-")));
            r.second_max = stoi(nv.substr(nv.find("-")+1));

            ranges.push_back(r);
            ranges_.insert({range_name, r});
        }
        if(cur.empty() && !range_done) {
            range_done = true;
        }
        if(cur == "your ticket:") {
            yt = true;
            continue;
        }
        if(yt) {
            your_ticket = cur;
            yt = false;
        }
        if(cur == "nearby tickets:") {
            analyze = true;
            continue;
        }
        if(analyze) {
            if(get_wrong_number(cur, ranges) == 0) {
                valid.push_back(cur);
            }
            part1 += get_wrong_number(cur, ranges);
        }
    }

    std::cout << "Part 1: " << part1 << std::endl;

    auto p2 = get_departures(valid, ranges_, your_ticket);
    std::cout << "Part 2: " << p2 << std::endl;

    file.close();
    return EXIT_SUCCESS;
}