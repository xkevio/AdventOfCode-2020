#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <numeric>

int get_group_sum(const std::string& answers) {
    std::unordered_set<char> exists;

    for (size_t i = 0; i < answers.length(); i++) {
        exists.insert(answers[i]);
    }

    return exists.size();
}

int get_real_group_sum(std::string& answers) {
    std::vector<std::string> words;
    std::string w;
    std::stringstream a(answers);

    int val = 0;

    while (getline(a, w, ' ')) {
        words.push_back(w);
    }

    if (words.size() == 1) {
        return get_group_sum(answers.erase(answers.find_last_not_of(' ') + 1));
    }

    for (char i = 'a'; i <= 'z'; i++) {
        bool every = true;
        for (auto const& word : words) {
            every &= word.find(i) != std::string::npos;
        }
        if (every) val++;
    }
    return val;
}

int main(int, char**) {
    std::ifstream file;
    std::vector<int> v;
    std::vector<int> v2;
    std::string line;

    file.open("input.txt");

    std::string cur = "";
    std::string cur2 = "";
    while (getline(file, line)) {
        if (line.empty()) {
            v.push_back(get_group_sum(cur));
            v2.push_back(get_real_group_sum(cur2));
            cur = "";
            cur2 = "";
        } else {
            cur += line;
            cur2 += line + " ";
        }
    }
    v.push_back(get_group_sum(cur));
    v2.push_back(get_real_group_sum(cur2));

    auto part1 = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "Part 1: " << part1 << std::endl;

    auto part2 = std::accumulate(v2.begin(), v2.end(), 0);
    std::cout << "Part 2: " << part2 << std::endl;

    file.close();
    return EXIT_SUCCESS;
}