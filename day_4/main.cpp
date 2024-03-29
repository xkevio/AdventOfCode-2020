#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

int valid_passports(const std::string& passports, const std::regex& re) {
    int valid = 0;

    std::string cur_passport;
    std::string p = "";

    std::stringstream st(passports);
    std::vector<std::string> v;

    while (std::getline(st, cur_passport)) {
        if (cur_passport.empty()) {
            v.push_back(p);
            p = "";
        } else {
            p += cur_passport + " ";
        }
    }
    v.push_back(p);

    for (const auto& l : v) {
        if (std::regex_match(l, re)) {
            valid++;
        }
    }

    return valid;
}

int main() {
    std::ifstream file("input.txt");
    std::string passports;
    std::stringstream p_stream;

    p_stream << file.rdbuf();

    std::regex re(
        "(?=.*ecl:.+)(?=.*eyr:.+)(?=.*pid:.+)(?=.*hcl:.+)(?=.*iyr:.+)(?=.*byr:."
        "+)(?=.*hgt:.+).*");
    std::regex re2(
        "(?=.*ecl:\\b(amb|blu|brn|gry|grn|hzl|oth)\\b)(?=.*eyr:\\b(202\\d|2030)"
        "\\b)(?=.*pid:\\b\\d{9}\\b)(?=.*hcl:#\\b[0-9a-f]{6}\\b)(?=.*iyr:\\b("
        "201\\d|2020)\\b)(?=.*byr:\\b(19[2-9]\\d|200[0-2])\\b)(?=.*hgt:((\\b(1["
        "5-8]\\d|19[0-3])cm\\b)|(\\b(59|6\\d|7[0-6])in\\b))).*");

    std::cout << "Part 1: " << valid_passports(p_stream.str(), re) << std::endl;
    std::cout << "Part 2: " << valid_passports(p_stream.str(), re2) << std::endl;

    return EXIT_SUCCESS;
}