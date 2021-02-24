#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// no crt >:/ (kinda crt, "sieving-method", somewhat copy-pasted)
size_t find_earliest_timestamp(const std::vector<std::string>& ids) {
    size_t time = 0;
    size_t inc = 0;
    std::vector<size_t> bus_ids;
    std::vector<size_t> offsets;

    for (size_t i = 0; i < ids.size(); i++) {
        if (std::all_of(ids[i].begin(), ids[i].end(), isdigit)) {
            bus_ids.push_back(stoi(ids[i]));
            offsets.push_back(i);
        }
    }

    while (true) {
        bool found = true;
        inc = bus_ids[0];
        for (size_t j = 0; j < bus_ids.size(); j++) {
            if ((time + offsets[j]) % bus_ids[j] == 0) continue;

            for (size_t k = 1; k < j; k++) {
                inc *= bus_ids[k];
            }

            found = false;
            break;
        }

        if (found) return time;
        time += inc;
    }

    return time;
}

int get_earliest_bus(int id, const std::vector<int>& service) {
    std::unordered_map<int, int> possible_ids;
    std::vector<int> ids;
    for (const auto& i : service) {
        std::pair<int, int> p(((id / i) + 1) * i, i);
        possible_ids.insert(p);
    }
    for (const auto& k : possible_ids) {
        ids.push_back(k.first);
    }
    return (*std::min_element(ids.begin(), ids.end()) - id) *
           possible_ids.at(*std::min_element(ids.begin(), ids.end()));
}

int main(int, char**) {
    std::ifstream file;
    std::stringstream ss;
    std::string content;
    file.open("input.txt");

    ss << file.rdbuf();
    content = ss.str();

    int id = stoi(content.substr(0, content.find("\n")));
    std::vector<int> services;
    std::vector<std::string> services2;
    std::stringstream se(content.substr(content.find("\n") + 1));
    std::string cur;

    while (getline(se, cur, ',')) {
        services2.push_back(cur);
        if (std::all_of(cur.begin(), cur.end(), isdigit)) {
            services.push_back(stoi(cur));
        }
    }

    std::cout << "Part 1: " << get_earliest_bus(id, services) << std::endl;
    std::cout << "Part 2: " << find_earliest_timestamp(services2) << std::endl;

    file.close();
    return EXIT_SUCCESS;
}