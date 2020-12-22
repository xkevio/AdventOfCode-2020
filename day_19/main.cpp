#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <regex>

std::string generate_regex(const std::unordered_map<int, std::string> &rules, int start) {
    std::string r;
    int current_rule = start;

    std::string cur = rules.at(current_rule);
    std::stringstream st(cur);
    if(cur[0] == '"') {
        r += cur[1];
    } else {
        std::string s;
        while(getline(st, s, ' ')) {
            if(s == "|") {
                r += s;
            } else {
                r += "(" + generate_regex(rules, stoi(s)) + ")";
            }
        }
    }
        
    return r;
}

int main(int, char**) {
    std::ifstream file;
    file.open("input.txt");

    std::string cur;
    bool check = false;

    std::string regex;
    std::string regex2;

    int p1 = 0;
    int p2 = 0;

    std::unordered_map<int, std::string> rules;
    while(getline(file, cur)) {
        if(cur.empty()) {
            check = true;
            regex = generate_regex(rules, 0);

            //somewhat "hardcoded" recursive rules, look into tree and node solution instead of regex
            rules[8] = "42 | 42 42 | 42 42 42 | 42 42 42 42 | 42 42 42 42 42";
            rules[11] = "42 31 | 42 42 31 31 | 42 42 42 31 31 31 | 42 42 42 42 31 31 31 31";

            regex2 = generate_regex(rules, 0);
            continue;
        }
        if(!check) {
            int rule = stoi(cur.substr(0, cur.find(":")));
            std::string rules_ = cur.substr(cur.find(":") + 2);
            rules.insert({rule, rules_});
        } else {
            if(std::regex_search(cur, std::regex("^" + regex + "$"))) {
                p1++;
            }
            if(std::regex_search(cur, std::regex("^" + regex2 + "$"))) {
                p2++;
            }
        }
    }

    std::cout << "Part 1: " << p1 << std::endl;
    std::cout << "Part 2: " << p2 << std::endl;
    
    file.close();
    return EXIT_SUCCESS;
}