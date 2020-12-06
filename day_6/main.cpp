#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <sstream>

int get_group_sum(std::string answers) {
    std::unordered_set<char> exists;

    for (size_t i = 0; i < answers.length(); i++)
    {
        exists.insert(answers[i]);
    }
    
    return exists.size();
}

int get_real_group_sum(std::string answers) {
    std::vector<std::string> words;
    std::string w;
    std::stringstream a(answers);

    int val = 0;

    while(getline(a, w, ' ')) {
        words.push_back(w);
    }

    if(words.size() == 1) return get_group_sum(answers.erase(answers.find_last_not_of(' ')+1));
    
    for(int i = 'a'; i <= 'z'; i++) {
        bool every = true;
        for(auto const &word : words) {
            every &= word.find(i) != std::string::npos;
        }
        if(every) val++;
    }
    return val;
}

int main(int, char**) {
    std::ifstream file;
    std::vector<std::string> v;
    std::vector<std::string> v2;
    std::string line;

    int p1_sum = 0;
    int p2_sum = 0;

    file.open("input.txt");

    std::string cur = "";
    std::string cur2 = "";
    while(getline(file, line)) {
        if(line.empty()) {
            v.push_back(cur);
            v2.push_back(cur2);
            cur = "";
            cur2 = "";
        } else {
            cur += line;
            cur2 += line + " ";
        }
    }
    v.push_back(cur);
    v2.push_back(cur2);

    std::for_each(v.begin(), v.end(), [&p1_sum](std::string &n) {p1_sum += get_group_sum(n);});
    std::cout << "Part 1: " << p1_sum << std::endl;

    std::for_each(v2.begin(), v2.end(), [&p2_sum](std::string &n) {p2_sum += get_real_group_sum(n);});
    std::cout << "Part 2: " << p2_sum << std::endl;

    file.close();
    return EXIT_SUCCESS;
}