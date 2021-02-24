#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// should have just done it with a Bag class, oh well
std::unordered_map<std::string, std::vector<std::string>> graph;
std::unordered_map<std::string, std::vector<std::string>> graph2;

bool get_paths(std::string key, const std::string& what) {
    key.erase(key.find_last_not_of(' ') + 1);
    bool t = false;

    auto values = graph.at(key);

    if (values.empty()) return false;
    for (const auto& v : values) {
        if (v.find(what) != std::string::npos) {
            return true;
        } else {
            t = t || get_paths(v, what);
        }
    }

    return t;
}

int get_bags(const std::string& start) {
    int b = 0;
    auto bags = graph2.at(start);

    if (bags.empty()) return 0;
    for (auto bb : bags) {
        bb.erase(0, bb.find_first_not_of(' '));
        bb.erase(bb.find_last_not_of(' ') + 1);

        int mult = bb[0] - '0';
        b += mult + mult * get_bags(bb.substr(2));
    }

    return b;
}

int main(int, char**) {
    std::ifstream file;
    std::string line;
    int p1 = 0;

    file.open("input.txt");

    while (getline(file, line)) {
        std::string key;
        std::string bag;
        std::vector<std::string> adjacent;
        std::vector<std::string> adjacent2;

        key = line.substr(0, line.find("bags") - 1);
        bag = line.substr(line.find("contain") + 8, line.length());

        if (bag[0] != 'n') {
            if (bag.find(",") == std::string::npos) {
                adjacent2.push_back(bag.substr(0, bag.find("bag") - 1));

                bag = bag.substr(2, bag.length());
                adjacent.push_back(bag.substr(0, bag.find("bag") - 1));
            } else {
                std::stringstream st(bag.substr(0, bag.length() - 5));
                std::string cur;
                while (getline(st, cur, ',')) {
                    adjacent2.push_back(cur.substr(0, cur.find("bag") - 1));

                    cur.erase(0, cur.find_first_not_of(' '));
                    cur.erase(std::remove_if(cur.begin(), cur.end(), isdigit), cur.end());
                    cur.erase(0, cur.find_first_not_of(' '));

                    adjacent.push_back(cur.substr(0, cur.find("bag") - 1));
                }
            }
            auto p = std::make_pair(key, adjacent);
            graph.insert(p);

            auto p2 = std::make_pair(key, adjacent2);
            graph2.insert(p2);
        } else {
            std::vector<std::string> empty;
            auto p = std::make_pair(key, empty);
            graph.insert(p);

            auto p2 = std::make_pair(key, empty);
            graph2.insert(p2);
        }
    }

    for (const auto& p : graph) {
        if (get_paths(p.first, "shiny gold")) {
            p1++;
        }
    }

    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << get_bags("shiny gold") << std::endl;

    file.close();
    return EXIT_SUCCESS;
}