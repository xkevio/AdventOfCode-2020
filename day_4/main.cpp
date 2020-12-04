#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>

int valid_passports(std::string passports, std::regex re) {
    int valid = 0;
    std::string cur_passport;
    std::string p = "";
    std::stringstream st(passports);
    std::vector<std::string> v;
    
    while(getline(st, cur_passport)) {
        if(cur_passport.empty()) {
            v.push_back(p);
            p = "";
        } else {
            p += cur_passport + " ";
        }
    }
    v.push_back(p);

    for (size_t i = 0; i < v.size(); i++)
    {
        if(std::regex_match(v[i], re)) {
            valid++;
        }
    }
    
    return valid;
}

int main(int, char**) {
    std::ifstream file;
    std::string passports;
    std::stringstream p_stream;

    file.open("input.txt");
    p_stream << file.rdbuf();

    std::regex re("(?=.*ecl:.+)(?=.*eyr:.+)(?=.*pid:.+)(?=.*hcl:.+)(?=.*iyr:.+)(?=.*byr:.+)(?=.*hgt:.+).*");
    std::regex re2("(?=.*ecl:\\b(amb|blu|brn|gry|grn|hzl|oth)\\b)(?=.*eyr:\\b(202\\d|2030)\\b)(?=.*pid:\\b\\d{9}\\b)(?=.*hcl:#\\b[0-9a-f]{6}\\b)(?=.*iyr:\\b(201\\d|2020)\\b)(?=.*byr:\\b(19[2-9]\\d|200[0-2])\\b)(?=.*hgt:((\\b(1[5-8]\\d|19[0-3])cm\\b)|(\\b(59|6\\d|7[0-6])in\\b))).*");

    std::cout << "Part 1: " << valid_passports(p_stream.str(), re) << std::endl;
    std::cout << "Part 2: " << valid_passports(p_stream.str(), re2) << std::endl;

    file.close();
    return EXIT_SUCCESS;
}